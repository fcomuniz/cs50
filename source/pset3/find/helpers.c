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
    // Variable to check if it one element was swapped 
    bool hasSwapped = false;
    // This variable stores the final unsorted position of the array, as with bubble sort, each passing makes the largest element in it's final position
    int endUnsortedPosition = n-1;
    // This is an auxiliary variable for swapping the two other variables
    int auxSwapVar;
    // First we must always see if any swaps have happened
    do {
        hasSwapped = false;
        for(int i = 0; i < endUnsortedPosition ; i++){
            if(values[i] > values[i+1]){
                // Indicates thar a swap has happend
                hasSwapped = true;
                
                // Swap the variables
                auxSwapVar = values[i];
                values[i] = values[i+1];
                values[i+1] = auxSwapVar;
                // End swap
            }
        }
        endUnsortedPosition--;
    } while(hasSwapped);
    
    
    
    return;
}


#ifdef HELPERS_TESTING

#include <stdio.h>

bool testSorted(){
    const int size = 10;
    int value[size];
    
    for(int i = 0 ; i < size; i++){
        value[i] = size-i;
        printf("%i ", value[i]);
    }
    printf("\n");
    
    sort(value,size);
    
    bool isSorted = true;
    for(int i = 0 ; i < size; i++){
        printf("%i ", value[i]);
        if(i < size-1){
            isSorted = isSorted && (value[i] < value[i+1]);
        }
    }
    printf("\n");
    return isSorted;
}

bool testSearch(){
    const int size = 10;
    int value[size];
    bool foundExistingElement = true;
    bool foundNonexistingElement = false;
    
    for(int i = 0 ; i < size; i++){
        value[i] = size-i;
    }
    sort(value,size);
    foundExistingElement = search(1,value,size);
    foundNonexistingElement = search(-1, value, size);
    
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
