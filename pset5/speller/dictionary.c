// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 1000;
#define N 1000

// Hash table
node *table[N];

// Number of entries in dictionary
unsigned int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node* p = table[hash(word) % N];
    while(p != NULL) {
        if (strcasecmp(p->word, word) == 0) {
            return true;
        }
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // sdbm hash - case insensitive
    unsigned int hash = 0;
    int c;

    while ((c = *word++)) {
        hash = tolower(c) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        printf("Could not open dictionary.\n");
        return false;
    }

    char word_read[LENGTH + 1];

    // For each word in dictionary
    while(fscanf(dict, "%s", word_read) != EOF) {

        // Allocate a new node
        node *n = malloc(sizeof(node));

        if (n == NULL) {
            printf("Out of memory.\n");
            return false;
        }

        strcpy(n->word, word_read);

        node** head = &table[hash(word_read) % N];
        n->next = *head;
        *head = n;

        num_words++;
    }
    
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *p;
    node *tmp;
    for (int i = 0; i < N; i++) {
        p = table[i];
        
        while (p != NULL) {
            tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    return true;
}