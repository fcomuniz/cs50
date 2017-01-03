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
#define MAX_PASSWORD_SIZE 4

// min character to print
#define MIN_CHAR_VALUE 32

// max character to print
#define MAX_CHAR_VALUE 126


/**
 * This is the definition of a struct that makes it easier to generate the generic strings
 */
struct arr {
    /// This is the variable that stores the array of strings
    char * * values;
    /// This stores the amount of strings in the arr
    int size;
};
/// Defining the arr struct for easier reference
typedef struct arr arr;

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
//#define CRACK_GENERIC_TESTING
#define CREATE_GENERIC_COMBINATIONS_TESTING
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


/**
 * This is the main function for the code, it tries to crack the given crypted password
 * This is the most important function, that generates a decrypted password
 * Supposing the code is written using the crypt function with the DES algorithm
 * @param hashedPassword
 * @return the uncrypted password
 */
char * crackPassword(char * hashedPassword);



/**
 * This uses a words file for easier cracking
 * @param hashedPassword
 * @param saltValue
 * @return the cracked password if found, or a null pointer if not found
 */
char * crackWithWordsFile(char * hashedPassword, char * saltValue);

/**
 * This tries to crack a password using changes in simple words
 * @param hashedPassword
 * @param saltValue
 * @param wordToUse
 * @return
 */
char * crackUsingCombination (char * hashedPassword, char * saltValue, char * wordToUse);

/**
 * Gets the salt value from the password
 * @param hashedPassword the password in hashed format
 * @return the salt value of the password
 */
char * getSaltValue(char * hashedPassword);


/**
 * Crack a generic password, of any size, without using any word help
 * @param hashedPassword
 * @param saltValue got from the hashedPassword
 * @return
 */
char * crackGeneric (char * hashedPassword, char * saltValue);


/**
 * Create all of the combination of size nOfChar with the printable ASCII characters
 * @param nOfChars
 * @return all of the combination of size nOfChar with the printable ASCII characters
 */
arr createGenericCombinations( int nOfChars);


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
                crackedPassword = strdup(word);
                break;
            }
        }

    }
    if(crackedPassword == NULL){
        printf("Didn't find in file!\n");
        printf("Trying combinations!\n");
        rewind(wordsFile);
        while(fscanf(wordsFile,"%s", word) >= 0 && crackedPassword == NULL){
            if(strlen(word) <= MAX_PASSWORD_SIZE) {
                crackedPassword = crackUsingCombination(hashedPassword, saltValue, word);
            }
        }
        if(crackedPassword == NULL)
        {
            printf("Trying generec password");
            crackedPassword = crackGeneric(hashedPassword, saltValue);
        }
//        Generic password trying

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
    char * temporaryWord = malloc(MAX_PASSWORD_SIZE*sizeof(char));
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

//    Checking the case where other values are added
//    if(strlen(temporaryWord) < MAX_PASSWORD_SIZE && !hasFound){
//        for (int i = MAX_PASSWORD_SIZE - 1, len = strlen(temporaryWord); i > len; i-- ){
//            arr values = createGenericCombinations(MAX_PASSWORD_SIZE - i);
//    //        Put values in the back
//            for(int j = 0; j < values.size && !hasFound; j++){
//                char * tmp = strdup(temporaryWord);
//                strcpy(temporaryWord, values.values[j]);
//                strcat(temporaryWord, tmp);
//                free(tmp);
//                cryptedValue = crypt(temporaryWord, saltValue);
//                if(strcpy(cryptedValue    , hashedPassword) == 0){
//                    hasFound = 1;
//                }
//                strcpy(temporaryWord, wordToUse);
//                strcat(temporaryWord, values.values[j]);
//                cryptedValue = crypt(temporaryWord, saltValue);
//                if(strcpy(cryptedValue, hashedPassword) == 0){
//                    hasFound = 1;
//                }
//            }
//        }
//    }





    free(temporaryWord);
    return crackedValue;
}


char * crackGeneric(char * hashedPassword, char * saltValue){
    char * crackedPassword = NULL;

    int hasFoundPassword = 0;
    for(int wordsSize = 1; wordsSize <= MAX_PASSWORD_SIZE; wordsSize++){
        arr genericWords = createGenericCombinations(wordsSize);
        for(int i = 0; i < genericWords.size; i++){

            char * cmpString = strdup(genericWords.values[i]);

            char * cryptedValue = crypt(cmpString, saltValue);

//            printf("%s %s\n", cryptedValue, hashedPassword);

            hasFoundPassword = strcmp(cryptedValue,hashedPassword) == 0;
            if(hasFoundPassword){
                crackedPassword = strdup(cmpString);
                break;


            }
            free(genericWords.values[i]);
            free(cmpString);
        }
        if(hasFoundPassword){
            break;
        }
        free(genericWords.values);
    }


    return  crackedPassword;
}

arr createGenericCombinations( int nOfChars){
    char * * value = NULL;
    int size = 0;
    if(nOfChars == 1){
//        return a single

        value = malloc((MAX_CHAR_VALUE - MIN_CHAR_VALUE+1)*sizeof(char*));
        size = ((MAX_CHAR_VALUE-MIN_CHAR_VALUE +1));
        for(int i = 0, k = MIN_CHAR_VALUE; i <= MAX_CHAR_VALUE - MIN_CHAR_VALUE; i++, k++){
            value[i] = malloc(2*sizeof(char));
            value[i][0] = (char) k;
            value[i][1] = '\0';
        }
    } else if(nOfChars > 1){
//        value = createGenericCombinations(nOfChars-1);
//       concatenate value with generated strings
//        Must allocate a lot of space
        arr partialGenericCombinations = createGenericCombinations(nOfChars-1);
        size = (MAX_CHAR_VALUE - MIN_CHAR_VALUE + 1)*partialGenericCombinations.size;
        value = malloc(size*sizeof(char*));

        int numberOfCombinations = partialGenericCombinations.size;

        for (int i = 0 ; i < numberOfCombinations; i ++){

            for(int k = 0; k <= MAX_CHAR_VALUE - MIN_CHAR_VALUE ; k++){
                value[i + k*numberOfCombinations] = malloc(sizeof(partialGenericCombinations.values[i])+1);
                strcpy(value[i + k*numberOfCombinations],partialGenericCombinations.values[i]);
//                Now we cat the string with the value of k
                char auxValue[] = {k+MIN_CHAR_VALUE, '\0'};
                char * tmp = strdup(value[i+k*numberOfCombinations]);
                strcpy(value[i+k*numberOfCombinations], auxValue);
                strcat(value[i+k*numberOfCombinations], tmp);
                free(tmp);
            }
            free(partialGenericCombinations.values[i]);
        }
        free(partialGenericCombinations.values);

    }
    arr val;
    val.values = value;
    val.size = size;
    return val;

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
		char * passwordToEncrypt = "12345";
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
                                 "50zPJlUFIYY0o",
                                 "50MxVjGD7EfY6",
                                 "50z2Htq2DN2qs",
                                 "50CMVwEqJXRUY",
                                 "50TGdEyijNDNY",
                                 "50QykIulIPuKI",
                                 "50q.zrL5e0Sak",
                                 "50Bpa7n/23iug",
                                 "HAYRs6vZAb4wo",
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
        free(crack);
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
        char * passwordToCrack = "50MxVjGD7EfY6";
        char * saltValue = getSaltValue(passwordToCrack);
        char * crackedPassword = crackGeneric(passwordToCrack, saltValue);

        if(crackedPassword != NULL){

            printf("%s", crackedPassword);
        }

        free(crackedPassword);
        free(saltValue);
    }


#endif

#ifdef CREATE_GENERIC_COMBINATIONS_TESTING
    int main(){
        arr allCombinations = createGenericCombinations(MAX_PASSWORD_SIZE);
        int n = allCombinations.size;
        for (int i = 0 ; i < n ; i++){
            printf("%s ", allCombinations.values[i]);
            free(allCombinations.values[i]);
        }
        free(allCombinations.values);

    }



#endif