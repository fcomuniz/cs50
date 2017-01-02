#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define _GNU_SOURCE
#include <crypt.h>

//Constant definitions

// Definitions for a word file to use for comparison
#define WORDS_FILE "/usr/share/dict/words"


// Max password size
#define MAX_PASSWORD_SIZE 2

// min character to print
#define MIN_CHAR_VALUE 60

// max character to print
#define MAX_CHAR_VALUE 70


// defines for program and testing
/// MAIN DEFINE
// If set runs the main program
// #define MAIN_PROGRAM

/// TESTING DEFINES
// If any of these are set, runs the related testing scheme
// #define CRYPT_TESTING
//#define OPEN_WORDS_FILE
//#define SIMPLE_CRACK_TESTING
// #define FULL_CRACK_TESTING
// #define GET_SALT_VALUE_TESTING
// #define FILE_CRACK_TESTING
//#define CRACK_USING_COMBINATION_TESTING
#define CRACK_GENERIC_TESTING
/**
 *
 *
 *
 *
 * DECLARATION OF THE FUNCTIONS
 *
 *
 *
 */


// This is the main function for this code
// it tries to crack the given password
char * crackPassword(char * hashedPassword);


//This uses a words file for easier cracking
char * crackWithWordsFile(char * hashedPassword, char * saltValue);

char * crackUsingCombination (char * hashedPassword, char * saltValue, char * wordToUse);

char * getSaltValue(char * hashedPassword);

char * crackGeneric (char * hashedPassword, char * saltValue);





#ifdef MAIN_PROGRAM
// this is a program for cracking a password that is given in command line form in the first argument
int main(int argc, char * argv[]){
	if(argc != 2){
		printf("Must be one argument\n");
		return 1;
	}
	char * hashedPassword = argv[1];
	char * crackedPassword;
    crackedPassword = crackPassword(hashedPassword);
    if(crackedPassword == NULL){

    } else {
        printf("%s\n",crackedPassword);
    }
    free(crackedPassword);
    return 0;
}
#endif


/**
 *
 *
 *
 *
 * IMPLEMENTATION OF THE FUNCTIONS
 *
 *
 *
 *
 *
 *
 */


// This is the most important function, that generates a decrypted password
// Supposing the code is written using the crypt function with the DES algorithm
char * crackPassword(char * hashedPassword){
	

	// Getting the salt value from the password
	char * saltValue = getSaltValue(hashedPassword);
	char * crackedPassword;

//  This tries to crack a password using the words file as a helper
// Using the words file can make it faster if word is in file, but it will slow down the code if it isn't present
    crackedPassword = crackWithWordsFile(hashedPassword,saltValue);

    if(crackedPassword == NULL){

//        Tries a more complex crack, trying all possibilites
    }

	// Cleaning the allocated variables

	free (saltValue);
	return crackedPassword;

}

char * crackWithWordsFile(char * hashedPassword, char * saltValue){
    char * crackedPassword;
    FILE * wordsFile = fopen(WORDS_FILE, "r");

    // Go through words in the file and compare those words with the password
    char word[100];
    crackedPassword = NULL;
    while(fscanf(wordsFile,"%s", word) >= 0){
        // tries a single word multiple times because it may be only a variation of the word
        // if we assume the password length isn't bigger than 8 we can make the program a lot faster


        // Encrypt word to read
        if(strlen(word) <= MAX_PASSWORD_SIZE){

            char * cryptedValue = crypt(word, saltValue);

            if(strcmp(cryptedValue, hashedPassword) == 0){
                printf("Found password!\n");
                crackedPassword = malloc(sizeof(word));
                strcpy(crackedPassword,word);
                break;
            }
        }

    }
    while(crackedPassword == NULL){
        printf("Didn't find in file!\n");
        printf("Trying combinations!\n");
        rewind(wordsFile);
        while(fscanf(wordsFile,"%s", word) >= 0 && crackedPassword == NULL){
            if(strlen(word) <= MAX_PASSWORD_SIZE) {
                crackedPassword = crackUsingCombination(hashedPassword, saltValue, word);
            }
        }
        if(crackedPassword != NULL)
            break;
//        Generic password trying
        crackedPassword = crackGeneric(hashedPassword, saltValue);
    }


    fclose(wordsFile);
    return crackedPassword;
}

char * getSaltValue(char * hashedPassword){
	char * saltValue = malloc(3*sizeof(char));
	saltValue[0] = hashedPassword[0];
	saltValue[1] = hashedPassword[1];
	saltValue[2] = '\0';
	return saltValue;
}

char * crackUsingCombination (char * hashedPassword, char * saltValue, char * wordToUse){
    char * crackedValue = NULL;
    char * temporaryWord = malloc(sizeof(wordToUse));
    strcpy(temporaryWord, wordToUse);

//    First we put everything in lowercase
    for ( int i = 0 , n = strlen(temporaryWord); i < n ; i++){
        temporaryWord[i] = tolower(temporaryWord[i]);
    }

    // start checking with case combinations
    char * cryptedValue;

    int hasFound = 0;

    for(int i = 0, len = strlen(temporaryWord),n = 1 << len; i < n && !hasFound ; i++){
        for(int j = 0; j < len; j++){
            temporaryWord[j] = ( i >> j ) & 1 ? toupper(temporaryWord[j]) : temporaryWord[j];
        }
        cryptedValue = crypt(temporaryWord, saltValue);
        if(strcmp(cryptedValue, hashedPassword) == 0){
            crackedValue = malloc(sizeof(temporaryWord));
            strcpy(crackedValue,temporaryWord);
    //  don't look other passwords if found the one
            hasFound = 1;
        }
//        printf("%s\n", temporaryWord);
        strcpy(temporaryWord, wordToUse);
    }

    // check all posible combinations with case and munging





//    Check Password munging
//    See more abount munging in    https://en.wikipedia.org/wiki/Munged_password







    free(temporaryWord);
    return crackedValue;
}


char * crackGeneric(char * hashedPassword, char * saltValue){
    char * crackedPassword = NULL;

    for(int wordsSize = 1; wordsSize <= MAX_PASSWORD_SIZE; wordsSize++){
        char word[wordsSize];
        char charValues[wordsSize];
        for(int index = 0; index < wordsSize; index++){
            printf("index: %i\n", index);
//            Soo we must use recursion to generate the generic words
            int hasEnded = 0;
            for(int j = 0; j <= index; j++){
                for(charValues[j] = MIN_CHAR_VALUE; charValues[j]<= MAX_CHAR_VALUE; charValues[j]++){
                    word[j] = charValues[j];

                }
            }
            // Has generated the word
//            printf("%s\n", word);
        }

    }


    return  crackedPassword;
}

/**
 *
 *
 *
 *
 *
 * TESTING THE FUNCTIONS
 *
 *
 *
 *
 *
 *
 */


// Testing functions using the given defines in the beggining of the file


// Test the usage of the crypt function
#ifdef CRYPT_TESTING

	int main(){
		char * passwordToEncrypt = "berkeley";
		char * encryptedPassword = crypt(passwordToEncrypt, "50");
		printf("encrypted password: %s\n", encryptedPassword);

		return 0;
	}

#endif

#ifdef OPEN_WORDS_FILE
	int main() {
		FILE * wordsFile = fopen(WORDS_FILE, "r");


		fclose(wordsFile);
		return 0;
	}

#endif

// Test the cracking function with a simple password
#ifdef SIMPLE_CRACK_TESTING

int main(){
	char * uncryptedPassword = "testing";
	char * passwordToCrack = crypt(uncryptedPassword, "50");
	char * crackedPassword = crackPassword(passwordToCrack);
	 printf("Has Cracked Password: %d\n", strcmp(uncryptedPassword, crackedPassword) == 0);
}

#endif

#ifdef FULL_CRACK_TESTING
int main(){
	char * passwordToCrack = "HALRCq0IBXEPM";
	char * crackedPassword = crackPassword(passwordToCrack);
    if(crackedPassword != NULL){
        printf("Cracked Password: %s\n", crackedPassword);
    }
}


#endif

#ifdef GET_SALT_VALUE_TESTING

int main(){
	char * passwordToCrack = "HALRCq0IBXEPM";
	char * saltValue = getSaltValue(passwordToCrack);
	printf("Correct Salt Value: %d\n", strcmp(saltValue ,"HA") == 0);
}

#endif


#ifdef FILE_CRACK_TESTING

int main(){
    int nPasswords = 5;
    char * passwordToCrack [] = {"HALRCq0IBXEPM",
                                 "50qxN6GeQfHvw",
                                 "50zPJlUFIYY0o",
                                 "HAYRs6vZAb4wo",
                                 "50QykIulIPuKI",
                                };
    for (int i = 0; i < nPasswords ; i++){
        printf("Trying to find password %i\n", i+1);
        char * saltValue = getSaltValue(passwordToCrack[i]);
        char * crack=  crackWithWordsFile(passwordToCrack[i],saltValue);
        if(crack != NULL){
            printf("Cracked Password %i: %s\n", i+1, crack);
        } else {
            printf("Could not find password %i\n", i +1);
        }
        printf("\n");
    }


}

#endif

#ifdef CRACK_USING_COMBINATION_TESTING

    int main(){
        char * passwordToCrack = "50QykIulIPuKI";
        char * crackedPassword = crackUsingCombination(passwordToCrack, "50", "harvard");
        free(crackedPassword);
        return 0;
    }


#endif

#ifdef CRACK_GENERIC_TESTING

    int main(){
        char * passwordToCrack = "50QykIulIPuKI";
        char * saltValue = getSaltValue(passwordToCrack);
        char * crackedPassword = crackGeneric(passwordToCrack, saltValue);

        free(crackedPassword);
        free(saltValue);
    }


#endif