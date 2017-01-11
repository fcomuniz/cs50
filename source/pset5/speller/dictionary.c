/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"
#include "dict-trie.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    bool retValue = false;
    //    First of all, we must put the word to lower case, as load will also put words with lower case values in the dictionary
    char * compareWord = strdup(word);

    for(int i = 0, n = strlen(compareWord) ; i < n ; i++){
        compareWord[i] = tolower(compareWord[i]);
    }

    retValue = hasWord(trie,compareWord);
    free(compareWord);
    return retValue;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    trie = createTrieNode();

//    Open dictionary file

    FILE * dict = fopen(dictionary, "r");
    if(dict == NULL){
        return false;
    }


    char line[LENGTH];

    int index = 0;
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            line[index] = c;
            index++;
        }
            // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(dict)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        }

            // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            line[index] = '\0';
            push(trie,line);
            index = 0;
        }

    }

    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return getSize(trie);
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    destroy(trie);
    return true;
}
