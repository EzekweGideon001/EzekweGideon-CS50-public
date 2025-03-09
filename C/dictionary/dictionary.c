// Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Global value to keep count
unsigned int size_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain an index for searching
    int word_index = hash(word);
    node *cursor = table[word_index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Implements DJB2 (a common hashing technique) Sourced from the internet.
    unsigned int hash = 0;
    while (*word)
    {
        hash = (hash << 5) + hash + toupper((unsigned char)*word); // hash * 31 + c
        word++;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the dictionary
    FILE *shelf= fopen (dictionary, "r");
    if (shelf == NULL)
    {
        return false;
    }

    // Reads strings from the dictonary
    char word[LENGTH + 1];
    // Resets size count before loop
    size_count = 0;

    while (fscanf (shelf, "%s", word) != EOF)
    {
        // Creates a new node to store the string
        node *new_node = malloc (sizeof(node));
        if (new_node == NULL)
        {
            fclose(shelf);
            return false;
        }
        // Copies each word to the node
        strcpy (new_node->word, word);

        // Hashes the word
        int hash_num = hash (new_node->word);

        // Inserts the word into the hash table
        new_node->next = table[hash_num];
        table[hash_num] = new_node; // Inserts at the beginning of the linked list

        // Increases size count
        size_count++;
    }

    fclose(shelf); // Closes the file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loops through each index in the table
    for (int i = 0; i < N; i ++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;   // Store current node
            cursor = cursor->next; // Move to next node
            free(tmp);// free current node
        }
        table[i] = NULL;
    }
    return true;
}
