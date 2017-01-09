//
// Created by francisco on 08/01/17.
//

#include <ctype.h>
#include "dict-trie.h"

dict_trie * createTrieNode(){
    dict_trie * newTrieNode = malloc(sizeof(dict_trie));
    newTrieNode->hasValue = false;
    for(int i = 0 ; i  < N_OF_LETTERS; i++){
        newTrieNode->children[i] = NULL;
    }
    return newTrieNode;
}

void destroy(dict_trie * trie){
    if(trie == NULL){
        return;
    }
    for(int i = 0 ; i < N_OF_LETTERS ; i++){
        destroy(trie->children[i]);
    }
    free(trie);
}


void push( dict_trie * trie, const char * word ) {
//    Check if has finished remaining word
   if(strlen(word) > 0) {
//       Has some word left to process
       int charPos = getCharPosition(word);
       if(trie->children[charPos] == NULL){
//           Allocate memory for this position
           trie->children[charPos] = createTrieNode();
       }
       push(trie->children[charPos], word+1);
   } else {
//       The word has ended, put a true here
       trie->hasValue = true;
   }

}

bool hasWord(const dict_trie * node, const char * word){

//    iterate through the trie to find if it has a word or not
    return  false;
}

int getSize(const dict_trie * node){
    return 0;
}

int getCharPosition(const char * charToFind){
    if(isalpha(*charToFind)){
        return (*charToFind) - 'a';
    } else if(*charToFind == '\''){
        return N_OF_LETTERS-1;
    } else {
        return -1;
    }
}
