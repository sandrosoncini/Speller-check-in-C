// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z';

// Hash table
node *table[N];

// dictionary size
int dictionary_words = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
 
    int key = hash(word);
    
    node *cursor = table[key];
    
    while (cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) 
{
   
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += tolower(word[i]);
    }
    
    //counting dictionary words
    
    
    return (sum % N);

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open file
    FILE *file = fopen(dictionary, "r");
    
    // check if file opens;   
    if (file == NULL)
    {
        return false;
    }
    
    // buffer to hold the word read from dictionary
    char new_word[LENGTH + 1];
    
            
    for(int i = 0 ; i<N; i++)
    {
        table[i] = NULL;
    }
    
    //while loop throught words from dictionary until reach the "\0"
    while (fscanf(file, "%s", new_word) != EOF)
    {
        // creatting a node using malloc to generate space in the heap
        node* new_node = malloc(sizeof(node));
        
        // checking if the generation is ok
        if (new_node == NULL)
        {
            return 1;
        }

        //copy 
        strcpy(new_node -> word, new_word);
        

        int key = hash(new_word);
        
        if (table[key] == NULL)
        {
            new_node -> next = NULL;
            table[key] = new_node;
        }
        else
        {
            new_node -> next = table[key];
            table[key] = new_node;  
        }
        dictionary_words ++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
  
     return dictionary_words;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    
    return true;
}

