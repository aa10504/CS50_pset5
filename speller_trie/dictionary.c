/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h> //for NULL
#include <stdlib.h> //for malloc
#include <string.h> //for strlen

#include "dictionary.h"

int numbersOfword = 0;

trienode *getnode(void)
{
    trienode *ptr = NULL;
    ptr = malloc(sizeof(trienode));
    if(ptr == NULL)
    {
        printf("Insufficient Memory!\n");
        exit(1);
    }
    
    ptr -> is_word = false;
    for(int i = 0; i < 27; i++)
    {
        ptr -> children[i] = NULL;
    }
    
    return ptr;
}

void destroy(trienode *head)
{
    if(head == NULL)
    {
        return;
    }
    else
    {
        for(int i = 0; i < 27; i++)
        {
            destroy(head -> children[i]);
        }
        free(head);
    }
}



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int aAsInt = (int)'a';
    trienode *travel_ptr = root;
    
    for(int i = 0; i < strlen(word); i++)
    {
        if(word[i] >= 65 && word[i] <= 90) //if the alphabat is capital
        {
            int child = word[i] - 65;
            if(travel_ptr -> children[child] == NULL)
            {
                return false;
            }
            else
            {
                travel_ptr = travel_ptr -> children[child];
            }
        }
        else if(word[i] == '\'')
        {
            if(travel_ptr -> children[26] == NULL)
            {
                return false;
            }
            else
            {
                travel_ptr = travel_ptr -> children[26];
            }
        }
        else
        {
            int child = word[i] - aAsInt;
            if(travel_ptr -> children[child] == NULL)
            {
                return false;
            }
            else
            {
                travel_ptr = travel_ptr -> children[child];
            }
        }
    }
    
    if(travel_ptr -> is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    root = getnode(); //initialize root
    
    FILE *fptr = fopen(dictionary, "r");
    if(fptr == NULL)
    {
        printf("Could not open %s!\n", dictionary);
        exit(1);
    }
    
    trienode *cursor = root; //current trienode
    char buffer; //temporarily store the alphabet
    int aAsInt = (int)'a';
    
    while((buffer = fgetc(fptr)) != EOF)
    {
        if(buffer == '\n')
        {
            cursor -> is_word = true;
            cursor = root;
            numbersOfword++;
        }
        else
        {
            if(buffer == '\'')
            {
                if(cursor -> children[26] == NULL)
                {
                    cursor -> children[26] = getnode();
                    cursor = cursor -> children[26];
                }
                else
                {
                    cursor = cursor -> children[26];
                }
            }
            else if(cursor -> children[buffer - aAsInt] == NULL)
            {
                cursor -> children[buffer - aAsInt] = getnode();
                cursor = cursor -> children[buffer - aAsInt];
            }
            else if(cursor -> children[buffer -aAsInt] != NULL)
            {
                cursor = cursor -> children[buffer - aAsInt];
            }
        }
    }
    
    fclose(fptr);
    
    int judgement = 0;
    for(int i = 0; i < 27; i++)
    {
        if(root -> children[i] == NULL)
        {
            judgement++;
        }
    }
    
    if(judgement == 27)
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
    return numbersOfword;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    int checker = 0;
    
    trienode *travel_ptr = root;
    if(travel_ptr == NULL)
    {
        checker++;
    }
    else
    {
        destroy(travel_ptr);
        checker++;
    }

    
    if(checker == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
