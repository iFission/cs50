/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
// https://raw.githubusercontent.com/raju249/CS50/master/pset5/pset5/dictionary.c
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

/**
 * Implementing a node datastructure
 */
typedef struct node
{
   bool eow;
   struct node *children[27];
}
node;

node *root;


 // total number of words counter
 int nwords = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    // letter as int

    // set current node to first node
    node *current = root;

    // looping through each letter in word
    int i = 0;
    while(word[i] != '\0')
    {
        char ch = word[i];


        // find is ch is apostrophe
        if (word[i] == '\'')
        {
            ch = 'z' + 1;
        }
        // converting letter between 0 and 25
        int childIndex = tolower(ch) - 'a';

        if (current -> children[childIndex] != NULL)
        {
            current = current -> children[childIndex];
            i++;
        }
        else
        {
            return false;
        }

    }

        if (current -> eow == true)
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
    // TODO

     // integer mapping for a and z

   // opening the dictionary file
   FILE* dict = fopen(dictionary,"r");

   // sanity check for null returned reference
   if (dict == NULL)
   {
    return false;
   }
   // mallocking memory for first node
   root = malloc(sizeof(node));

   // integer for current position in children array
   int c = 0;

   // cursor node
   node *current = NULL;

   // looping through dictionary until end of file is encountered
   while(EOF != (c = fgetc(dict)))
   {
      // setting current node to first node
      current = root;

      // iterating through c and adding each
      // letter to children until "\n"
      for(; c != '\n'; c = fgetc(dict))
      {
        // if apostrophe then store in
        if (c == '\'')
        {
          c = 'z' + 1;
        }

        // if the c is not in node...create one
        if (current -> children[c - 'a'] == NULL)
        {
          // malloc a new node
          current -> children[c - 'a'] = malloc(sizeof(node));
        }
        // got to address in children
        current = current -> children[c - 'a'];

      }
      current -> eow = true;
      nwords++;
   }

   // close the dictionary file
   fclose(dict);
   return true;

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return nwords;
}

// function to freenode
void freenode(node *root)
{
    for(int i = 0; i < 27; i++)
    {
        if (root -> children[i] != NULL)
        {
            freenode(root -> children[i]);
        }
    }
    free(root);
    return;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    node *current = root;
    freenode(current);
    return true;

}