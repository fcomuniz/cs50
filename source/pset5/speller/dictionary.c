/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include "dict-trie.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    bool retValue = false;
    //    First of all, we must put the word to lower case, as load will also put words with lower case values in the dictionary
    char * compareWord = strdup(word);

    for(int i = 0, n = strlen(compareWord) ; i < n ; i++){
        compareWord[i] = tolower(compareWord[i]);
    }



    free(compareWord);
    return retValue;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO



    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
