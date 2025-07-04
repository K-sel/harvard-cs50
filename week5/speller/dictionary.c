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

const unsigned int N = 678;
int size_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *n = table[index];

    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*
    Hash table [0] -> every word containing an ' (appostrophe).
    Hash table [1] -> every word beginning with the first two letters that are NOT alphabetical
    (speicals or is to short). (edge cases) Hash table [2 - 677] -> every two letters combinaisons.
    AA - AB...ZZ .
    */

    // Every word with ' will be in linked list 0.
    if (strchr(word, '\'') != NULL)
    {
        return 0;
    }

    else
    {

        if (word[0] && isalpha(word[0]) && word[1] && isalpha(word[1]))
        {
            int word0 = toupper(word[0]);
            int word1 = toupper(word[1]);

            return 2 + 26 * (toupper(word[0]) - 'A') + (toupper(word[1]) - 'A');
        }
        else
        {
            return 1;
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Couldn't open file");
        return false;
    }

    // Reset the size counter everytime load is called.
    size_counter = 0;
    char word[LENGTH + 1];

    while (fscanf(source, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->next = NULL;

        printf("%s", word);

        int index = hash(word);
        n->next = table[index];
        table[index] = n;
        size_counter++;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload()
{
    for (int i = 0; i < N; i++)
    {

        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
