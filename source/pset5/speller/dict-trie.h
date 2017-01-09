//
// Created by francisco on 08/01/17.
//

#ifndef CS50_DICT_TRIE_H
#define CS50_DICT_TRIE_H

#define N_OF_LETTERS 27

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * Defining the dict_trie structure for simple usage
 */
typedef struct dict_trie {

    bool hasValue;
    struct dict_trie * children[N_OF_LETTERS];

} dict_trie;

dict_trie * createTrieNode();

void destroy(dict_trie * trie);

void push( dict_trie * node, const char * word );

bool hasWord(const dict_trie * node, const char * word);

int getSize(const dict_trie * node);

int getCharPosition(const char * charToFind);

#endif //CS50_DICT_TRIE_H
