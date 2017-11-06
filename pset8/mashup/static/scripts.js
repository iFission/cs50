// global variables
// Google Map
var map; // create a now map object, actually a reference (pointer) to the map to be created later

// markers for map
var markers = []; // create a new marker object, array, references to any markers added later

// info window
var info = new google.maps.InfoWindow(); // create info window object, used to display links to articles

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [ // array of styles

        // hide Google's labels, an object
        {
            featureType: "all",
            elementType: "labels",
            stylers: [ // array
                {visibility: "off"}
            ]
        },

        // hide roads, an object
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options to configure map, keys and values
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 37.4236, lng: -122.1619}, // Stanford, California
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0); //get DOM node whose id is map-canvas, defined in HTML, returns actual DOM that jQuery is wrapping
    // use 'map-canvas' div as a container for the map
    // get reference to the element 'map-canvas' div using getElementById()/$("#") method

    // instantiate map as a global variable (without var in front)
    map = new google.maps.Map(canvas, options);
    // create a new map, inject it into the DOM node in canvas, configure using options
    // Map class, Map(mapDiv:Node,opts?:MapOptions )
    // create new variable map, instantiate map object at element (div) 'map''s location, using google.maps.Map class
    // can create multiple instances of the objects using same class
    // create new instances with the new operator

    // picks up where the anonymous function left off
    // called after the map is loaded
    // configure UI once Google Map is idle (i.e., loaded)
});

/**
 * Adds marker for place to map.
 */
// data received:
// [
//   {
//     "accurary": 4,
//     "admin_code1": "CO",
//     "admin_code2": "019",
//     "admin_code3": "",
//     "admin_name1": "Colorado",
//     "admin_name2": "Clear Creek",
//     "admin_name3": "",
//     "country_code": "US",
//     "latitude": 39.7402,
//     "longitude": -105.5983,
//     "place_name": "Idaho Springs",
//     "postal_code": "80452"
//   }
// ]
function addMarker(place)
{
    var marker = new google.maps.Marker({
        position: {lat: 37.4236, lng: -122.1619},
        // position: {lat: place.latitude, lng: place.longitude},
        map: map, // directly place map on map created earlier
        title: place.place_name
    });
}

/**
 * Configures application.
// configures a list of listeners
 */
function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() { // listen for end of dragging, then call function update()

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // configure typeahead
    $("#q").typeahead({
        highlight: false,
        minLength: 1
    },
    {
        display: function(suggestion) { return null; },
        limit: 10,
        source: search,
        templates: {
            suggestion: Handlebars.compile(
                "<div>" +
                "TODO" +
                "</div>"
            )
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // set map's center
        map.setCenter({lat: parseFloat(suggestion.latitude), lng: parseFloat(suggestion.longitude)});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        info.close();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    marker.setMap(null)
    // call setMap method that belongs to the markers
    // set to null to remove from map
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, syncResults, asyncResults)
{
    // get places matching query (asynchronously)
    var parameters = {
        q: query
    };
    $.getJSON(Flask.url_for("search"), parameters)
    .done(function(data, textStatus, jqXHR) {
    // call back function, passes data, textStatus, jqXHR

        // call typeahead's callback with search results (i.e., places)
        asyncResults(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());

        // call typeahead's callback with no results
        asyncResults([]);
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) == "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='/static/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update()
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON(Flask.url_for("update"), parameters)
    .done(function(data, textStatus, jqXHR) {
    // requests /update?=sw____&ne=____ to get places json
    // call back function, passes data, textStatus, jqXHR (object, superset of XMLHTTPRequest object)

       // remove old markers from map
       removeMarkers();

       // add new markers to map
       for (var i = 0; i < data.length; i++)
       {
           addMarker(data[i]);
           // passes  informations (in data) to addMarker()

       }

    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
};
