/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 *
 *
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

int table_size = 700;

unsigned int size_counter = 0;

//hash function
int hash_gen(const char* string)
{
    if(string == '\0')
    {
        return 0;
    }
    //convert first character of string to upper case and then subtract A to convert to integer between 0 and 26
    int hash = toupper(string[0]) - 'A';
    return hash % table_size;
}

//define node structure
typedef struct node
   {
       char word[LENGTH + 1];
       struct node* next;
   }
   node;

//define hashtable
node* hashtable[700];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    //determine length of word to be checked
    int word_len = strlen(word);
    //define an array to take lower case value of word arguement
    char check_word[LENGTH + 1];
    //define a single char to take the value a converted char from arguement word
    char check_word_l;

    //loop through the word to be checked and change to lower case
    for(int i = 0; i < word_len; i++)
    {
        check_word_l= tolower(word[i]);
        check_word[i] = check_word_l;
    }
    //add the terminator character to the end of the array to make a string
    check_word[word_len] = '\0';

    //generate hash value for lower case word to be checked
    int word_index = hash_gen(check_word);

    node* cursor = hashtable[word_index];

    //if hashtable value is NULL, then no entry in the dictionary for that word
    if(hashtable[word_index] == NULL)
    {
        return false;
    }
    //traverse linked list
    while(cursor != NULL)
    {
        if(strcmp(cursor->word, check_word) == 0)
        {
            return true;
        }
        else
        {
            //go to next node
            cursor = cursor->next;
        }

    }
    return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool load(const char* dictionary)
{
    //loop through the hashtable to initialise it by setting each value to NULL
    for(int i = 0; i < table_size; i++)
    {
        hashtable[i] = NULL;
    }

    //open dictionary file
    FILE *d = fopen(dictionary,"r");
    //return false if the dictionary is empty
    if(d == NULL)
    {
        printf("Could not load %s\n",dictionary);
        return false;
    }

    //create a new node to hold the word being added to the dictionary

    //create buffer for fscanf
    char buffer[LENGTH + 1];

        //scan through the dictionary (d) adding the next word to new node
        while(fscanf(d,"%s", buffer) == 1)
        {
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, buffer);
        new_node->next = NULL;

        //calculate hash value for word to be added
        int index = hash_gen(new_node->word);

        if(hashtable[index] == NULL)
        {
            hashtable[index]= new_node;
        }

        //if the current node is not empty
        else
        {
            //add to the start of the linked list
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
        size_counter = size_counter + 1;
        }
    fclose(d);
    return true;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //return the size_counter
    return size_counter;

}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    //create a temporary pointer that goes along freeing the previous pointer
    node* temp = NULL;

    for(int i = 0; i <= (table_size - 1); i++)
    {
        node* curr = hashtable[i];

        //traverse through to end of list
        while(curr != NULL)
        {
            temp = curr->next;
            free(curr);
            curr = temp;
        }
    }
    return true;

}
