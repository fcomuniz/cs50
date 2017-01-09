//
// Created by francisco on 08/01/17.
//

#include "dict-trie.h"
#include <stdbool.h>
#include <stdio.h>
#define NUMBER_OF_SPACES 2

void printSpace(int nOfSpace){
    for(int i = 0; i < nOfSpace; i++){
        printf(" ");
    }
}

void printTrieNode(dict_trie * node, int depth){
    char auxChar;
    if(node->hasValue == true){
        printSpace(depth*NUMBER_OF_SPACES);
        printf("EOW\n");
    } else {

        for(int i = 0 ; i < N_OF_LETTERS; i++){
            if(node->children[i] != NULL) {
                if(i < N_OF_LETTERS -1 ){

                    auxChar = i + 'a';
                } else {
                    auxChar = '\'';
                }
                printSpace(depth*NUMBER_OF_SPACES);
                printf("%c \n",  auxChar);
                printTrieNode(node->children[i], depth+1);
            }
        }
    }
}

void printTrie(dict_trie * trie){
    printf("This is the root node\n");
    char auxChar;
    for(int i = 0 ; i < N_OF_LETTERS; i++){
        if(trie->children[i] != NULL){
            if(i < N_OF_LETTERS - 1){
                auxChar = i + 'a';
            } else {
                auxChar = '\'';
            }
            printf("%c\n", auxChar);
            printTrieNode(trie->children[i], 1);
        }
    }
}



void createtest(){
    printf("createtest:\n");
    dict_trie * trie;

    trie = createTrieNode();
    printf("trie->hasValue: %i\n", trie->hasValue);
    for (int i = 0 ; i < N_OF_LETTERS ; i++){
        printf("trie->children[%i] == NULL : %i\n", i , trie->children[i] == NULL);
    }

    free(trie);
}

void destroytest(){

    dict_trie * trie;
    trie = createTrieNode();
    for(int i = 0 ; i < N_OF_LETTERS; i++){
        trie->children[i] = createTrieNode();
    }
    for(int i = 0 ; i < N_OF_LETTERS; i++){
        for (int j = 0 ; j < N_OF_LETTERS; j+=2){
            trie->children[i]->children[j] = createTrieNode();
        }
    }

    destroy(trie);
}

void pushtest(){
    dict_trie * trie;
    trie = createTrieNode();

    push(trie,"test\'s");

    printTrie(trie);

    push(trie, "testing");

    printTrie(trie);
    destroy(trie);
}

void pushWord(dict_trie * trie, const char * word, int * size){
    push(trie, word);
    (*size)++;
}

void sizetest(){

    dict_trie * trie;
    trie = createTrieNode();
    int realSize = 0;
    pushWord(trie,"test\'s", &realSize);
    pushWord(trie, "testing", &realSize);
    pushWord(trie, "fucking", &realSize);
    pushWord(trie, "more", &realSize);
    pushWord(trie, "words", &realSize);
    int size = getSize(trie);
    printf("realSize: %i\nsize: %i\n", realSize, size);
    destroy(trie);
}

void haswordtest(){

    dict_trie * trie;
    trie = createTrieNode();
    const char * word = "test\'s";
    push(trie,word);
    push(trie, "testing");
    bool hasThisWord = hasWord(trie, word);

    printf("hasThisWord: %i\n", hasThisWord);
    destroy(trie);
}

int main(int argc, char * argv[]){
//    destroytest();
//    pushtest();
//    sizetest();
    haswordtest();
    return 0;

}
