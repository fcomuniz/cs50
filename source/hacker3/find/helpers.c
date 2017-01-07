/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"
#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    // We must use binary search to find an element
    int beginning= 0, end =n, middle;
    int pos = -1;
    bool hasFound = false;
    while(end >= beginning && !hasFound){
        
        middle = (beginning+end)/2;
        int cmpValue = values[middle];
        if(value == cmpValue){
            pos = middle;
            hasFound=true;
            // The element has been found
        } else if(value < cmpValue){
            // realocate beginning and end
            end = middle -1;
        } else {
            beginning = middle+1;
        }
    }
    
    return hasFound;
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int auxValues[LIMIT] = {};
    for(int i = 0 ; i < n ; i++){
        auxValues[values[i]]++;
    }
    for(int i = 0, k = 0; i < LIMIT; i++){
    
        while(auxValues[i] > 0){
            values[k] = i;
            k++;
            auxValues[i]--;
        }
            
        
    }
    return;
}


#ifdef HELPERS_TESTING

#include <stdio.h>

bool testSorted(){
    const int size = 11;
    int value[size];
    
    for(int i = 0 ; i < size; i++){
        value[i] = size-i;
        printf("%i ", value[i]);
    }
    value[0] = 1; 
    printf("\n");
    
    sort(value,size);
    
    bool isSorted = true;
    for(int i = 0 ; i < size; i++){
        printf("%i ", value[i]);
        if(i < size-1){
            isSorted = isSorted && (value[i] <= value[i+1]);
        }
    }
    printf("\n");
    return isSorted;
}

bool testSearch(){
    const int size = 3;
    int value[] = {42,43,44};
    bool foundExistingElement = true;
    bool foundNonexistingElement = false;
    sort(value,size);
    foundExistingElement = search(42,value,size);
    foundNonexistingElement = search(45, value, size);
    
    return foundExistingElement && !foundNonexistingElement;
}

int main(){
    
    if(testSorted()){
        printf("Is sorting elements correctly\n");
    }
    if(testSearch()){
        printf("Is searching correctly\n");
    }
    
    return 0;
}


#endif
