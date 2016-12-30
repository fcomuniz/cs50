#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
// Returns the position of either 'A' o 'a' in ASCII
int getBegginingCharValue(bool);

char encryptValue(int, char);

void printEncryptedMessage(string, int);

int main(int argc, char * argv[]){
    // Check commaand line argument
    if(argc != 2){
        printf("Command must be ran with one arugment!!!\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string messageToEncrypt = GetString();
    
    printEncryptedMessage(messageToEncrypt, key);
    
    return 0;
}

int getBegginingCharValue(bool isUpper){
    if (isUpper){
        return 'A';
    } else {
        return 'a';
    }
}
char encryptValue(int key, char value){
    char retValue;
    int integerRepresentation = value;
    if(isalpha(value)){
        retValue = (char) ( (integerRepresentation + key - getBegginingCharValue(isupper(value))) % ALPHABET_SIZE  + getBegginingCharValue(isupper(value)));
    } else {
        
        retValue = value;
    }
    return retValue;
}

void printEncryptedMessage(string message, int key){
    for(int i = 0, n = strlen(message); i < n; i++){
        printf("%c", encryptValue(key,message[i]));
    }    
    printf("\n");
}