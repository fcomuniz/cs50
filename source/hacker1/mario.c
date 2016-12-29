#include <stdio.h>
#include <cs50.h>
#include <string.h>

void printCharNTimes(int nTimes, char charToPrint){
    for (int i = 0; i < nTimes; i++){
        printf("%c", charToPrint);
    }
}

void printCorrectChars(int nOfHash, int nOfSpace){
    printCharNTimes(nOfSpace, ' ');
    printCharNTimes(nOfHash, '#');
    printCharNTimes(2,' ');
    printCharNTimes(nOfHash, '#');
}

int main(void){
    
    
    int height;
    do {
        printf("Height: ");
        height = GetInt();
    } while(height > 23 || height < 0);
    // iterate through the lines
    int nOfHash;
    int nOfSpace;
    if(height < 0){
        printCharNTimes(1,'\n');
    }
    for(int i = 1; i <= height; i++){
        nOfHash = i;
        nOfSpace = height -i;
        printCorrectChars(nOfHash, nOfSpace);
        printCharNTimes(1,'\n');
    }
    
    return 0;
}
