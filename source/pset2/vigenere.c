
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
// Returns the position of either 'A' o 'a' in ASCII
int getBegginingCharValue(bool);

char encryptValue(char valueToEncrypty, char encryptionLetter);

void printEncryptedMessage(string messageToEncrypt, string keyMessage);

bool isAlphabetic(string str){
    bool retValue = true;
    for(int i = 0, n = strlen(str); i < n; i++){
        retValue = retValue && isalpha(str[i]);
    }
    return retValue;
}

int main(int argc, char * argv[])
{
    if(argc != 2){
        // Handle incorrect input
        printf("Use only one argument!!\n");
        return 1;
    }
    if(!isAlphabetic(argv[1])){
        printf("String must only contain alphabet characters!!\n");
        return 1;
    }

    
    string keyMessage = argv[1];
    
    string messageToEncrypt=GetString();
    
    
    
    printEncryptedMessage(messageToEncrypt, keyMessage);
    
}


char encryptValue(char valueToEncrypt, char encryptionLetter){
    char retValue;
    
        retValue = (char) ( (valueToEncrypt + encryptionLetter - getBegginingCharValue(isupper(valueToEncrypt)) - getBegginingCharValue(isupper(encryptionLetter))) % ALPHABET_SIZE  + getBegginingCharValue(isupper(valueToEncrypt)));
    
    return retValue;
}

void printEncryptedMessage(string messageToEncrypt, string keyMessage){
    for(int i = 0, n = strlen(messageToEncrypt), j = 0, nKey = strlen(keyMessage); i < n ; i++){
        if(j >= nKey){
            j = 0;
        }
        if(isalpha(messageToEncrypt[i])){    
            printf("%c", encryptValue(messageToEncrypt[i], keyMessage[j]));
            j++;
        } else {
            printf("%c", messageToEncrypt[i]);
        }
    }
    printf("\n");
}

int getBegginingCharValue(bool isUpper){
    if (isUpper){
        return 'A';
    } else {
        return 'a';
    }
}