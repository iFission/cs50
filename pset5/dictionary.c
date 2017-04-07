/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool eow; // boolean value indicating whether the node is the end of a word
    struct node* children[27]; // array of 27 nodes for 26 alphabets and 1 /
}
node;

node* root; // first node

int nwords = 0; // counter for number of words loaded

/**
 * Returns true if word is in dictionary else false.
 is only passed strings with alphabetical characters and/or apostrophes
 only return true if the word is in dictionary
 */
bool check(const char* word)
{
    node* current = root; // set current node pointer to root
    int n = strlen(word);
    int i = 0;

    while(i < n)
    {
        int letter = tolower(word[i]); //convert to lower case, case-insensitive

        //check letter against trie

        if((current->children[letter-'a']) != NULL)
        {
            current = current->children[letter-'a'];
            i++;

        }
        else
        {
            return false;
        }
    }
    if (current->eow == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // allocate memory
    root = calloc(27, sizeof(node)); // allocate memory to root, initialize to 0
    node* current = NULL;

    int c = 0;

    while((fgetc(dict)) != EOF) // check that is not at the end of the file, assign to c
    {
        current = root;

        while((c = fgetc(dict)) != '\n') // if c is not next line, store character
        {
            // point current node to the next node, if no next node is present, create new
            if(current->children[c-'a'] == NULL)
            {
                current->children[c-'a'] = calloc(1, sizeof(node));
            }
            current = current->children[c-'a'];
        }
        current->eow = true; // set end of word to true
        nwords ++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return nwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

void freeNode(node* current)
{
    for(int i = 0; i < 27; i++)
    {
        if(current->children[i] != NULL)
        {
            freeNode(current->children[i]);
        }
    }
    free(current);
}

bool unload(void)
{
    freeNode(root);
    return true;
}