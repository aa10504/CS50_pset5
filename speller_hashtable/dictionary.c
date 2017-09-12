/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h> //for NULL
#include <stdlib.h> //for malloc
#include <string.h> //for strcpy
#include <strings.h> //for strcasecmp

#include "dictionary.h"

sllnode *hashtable[26];
int counter = 0;

/**
 * turn the first alphabet of a word into an int from 0 to 25
 */
int hash(char *word)
{
    int temp;
    if(word[0] < 97)
    {
        temp = word[0] - 65;
    }
    else
    {
        temp = word[0] - 97;
    }
    return temp;
}

/**
 * destroy a singly linked node
 */
void destroy(sllnode *head)
{
    if(head == NULL)
    {
        return;
    }
    else
    {
        destroy(head -> next);
        free(head);
    }
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    char buffer[LENGTH + 1];
    strcpy(buffer, word);
    int h_number = hash(buffer);
    
    sllnode *travel_ptr = hashtable[h_number];
    do
    {
        if(travel_ptr == NULL)
        {
            return false;
        }
        else if(strcasecmp(word, travel_ptr -> word) == 0)
        {
            return true;
        }
        
        travel_ptr = travel_ptr -> next;
    }
    while(true);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    for(int i = 0; i < 26; i++)
    {
        hashtable[i] = NULL;
    }
    /**
     * initialize a hashtable
     */
    
    FILE *fPtr = fopen(dictionary, "r");
    if (fPtr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        exit(1);
    }
    
    char buffer[LENGTH + 1];
    while(fscanf(fPtr, "%s", buffer) != EOF)
    {
        int index = hash(buffer);
        
        sllnode *ptr = NULL;
        ptr = malloc(sizeof(sllnode));
        if(ptr == NULL)
        {
            fprintf(stderr, "Insufficient memory.\n");
            unload();
            return(false);
        }
        strcpy(ptr -> word, buffer);
        ptr -> next = NULL;
        
        if(hashtable[index] == NULL)
        {
            hashtable[index] = ptr;
        }
        else
        {
            ptr -> next = hashtable[index];
            hashtable[index] = ptr;
        }
        counter++;
    }
    fclose(fPtr);
    
    int judge = 0;
    for(int i = 0; i < 26; i++)
    {
        if(hashtable[i] == NULL)
        {
            judge++;
        }
    }
    
    if(judge == 26)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    int checker = 0;
    for(int i = 0; i < 26; i++)
    {
        sllnode *travel_ptr = hashtable[i];
        if(travel_ptr == NULL)
        {
            checker++;
        }
        else
        {
            destroy(travel_ptr);
            checker++;
        }
    }
    
    if(checker == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

