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
    struct node *children[27]; // array of 27 nodes for 26 alphabets and 1 \'
}
node;

node *root; // first node

int nwords = 0; // counter for number of words loaded

/**
 * Returns true if word is in dictionary else false.
 is only passed strings with alphabetical characters and/or apostrophes
 only return true if the word is in dictionary
 */
bool check(const char *word)
{
    node *current = root; // set current node pointer to root
    int n = strlen(word);
    int i = 0;

    while(i < n) // loop n times for n chars
    {
        int letter = tolower(word[i]); //convert to lower case, case-insensitive
        if (letter == '\'')
        {
            letter = 'z' + 1;
        }
        //check letter against trie
        if(current->children[letter-'a'] != NULL)
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
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // allocate memory
    root = malloc(sizeof(node)); // allocate memory to root
    node *current = NULL; // currrent node, point to NULL

    int c = 0; // integer for current position in children array

    // scan the dictionary char by char
    // while(EOF!= (c = fgetc(dict))) // check that is not at the end of the file, assign char to c
    while(fgetc(dict) != EOF) // check that is not at the end of the file, assign char to c
    {
        current = root; // set current node pointer to root

        // iterate through the char, add each letter to children until \n
        // for(; c != '\n'; c = fgetc(dict)) // if c is not next line use with while(EOF!= (c = fgetc(dict))), so that first c that is seeked is used
        fseek(dict, -1, SEEK_CUR); // move the cursor back by one
        while((c = fgetc(dict)) != '\n') // if c is not next line, infinite loop when dictionary word does not end with \n
        // while((c = fgetc(dict)) != '\n' && (c = fgetc(dict)) != EOF) // if c is not next line, does not load last line without \n
        {
            if (c == '\'')
            {
                c = 'z' + 1;
            }
            // point current node to the next node, if no next node is present, create new
            if(current->children[c-'a'] == NULL)
            {
                current->children[c-'a'] = malloc(sizeof(node));
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

void freeNode(node *current)
{
    for(int i = 0; i < 27; i++)
    {
        if(current->children[i] != NULL)
        {
            freeNode(current->children[i]);
        }
    }
    free(current);
    return;
}

bool unload(void)
{
    freeNode(root);
    return true;
}