/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

// linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *node1 = malloc(sizeof(node)); // create a pointer to the first node and allocate its size
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // scan the dictionary word by word
    while(fscanf(dict, "%s", word) != EOF) // look for a string in dict, store in word
    {
        // malloc a node * for each new word
        node *node_new = malloc(sizeof(node)); // allocate memory for new node
        // check memory is allocated properly, else unload all
        if (node_new == NULL)
        {
            unload();
            return false;
        }

        strcpy(node_new->word, word); // copy word to the node

        // connect to linked list
        node_new->next = head; // point new node to first element
        head = node_new; // point head to new node
    }
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
