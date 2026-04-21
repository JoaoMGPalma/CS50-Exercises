// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table - We will check the first 2 letters of each word, for that
// we need 26*26 = 676 "buckets"
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Global variable will keep track of how many words were loaded from the dictionary
unsigned int word_count = 0;

// Global variable will be true if the dictionary is already loaded into memory
bool loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *selected = table[hash(word)];

    while (selected != NULL)
    {
        if (strcasecmp(word, selected->word) == 0)
        {
            return true;
        }

        selected = selected->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int first_h = (toupper(word[0]) - 'A') * 26;
    unsigned int secnd_h = 0;
    if (isalpha(word[1]) && word[1] != '\0')
    {
        secnd_h = (toupper(word[1]) - 'A');
    }

    return first_h + secnd_h;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char buffer[LENGTH + 1];
    FILE *input = fopen(dictionary, "r");

    if (input != NULL)
    {
        while (fscanf(input, "%s", buffer) == 1)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                fclose(input);
                return false;
            }

            strcpy(n->word, buffer);
            unsigned int index = hash(buffer);

            n->next = table[index];
            table[index] = n;

            word_count++;
        }
    }

    else
    {
        return false;
    }

    loaded = true;
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return word_count;
    }

    return 0;
}

// Frees allocated memory from all the nodes on a linked list
void free_list(node *list)
{
    while (list != NULL)
    {
        node *temp = list->next;

        free(list);

        list = temp;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }

    return true;
}
