#include <stdio.h>
#include <cs50.h>


// testing defines
// #define SUM_OF_DIGITS
// #define NUMBER_OF_DIGITS
// #define GET_LAST_N_DIGITS
// #define HAS_CORRECT_NUMBER_OF_DIGITS
// #define HAS_VALID_CHECKSUM
// #define IS_VALID_GENERIC_CARD_NUMBER
// #define IS_AMEX_CARD
// #define IS_MASTERCARD_CARD
// #define IS_VISA_CARD
#define COMPLETE_PROGRAM



int sumOfDigits(long long number){
    int sumDigits = 0;
    while(number > 0){
        sumDigits += number%10;
        number = number/10;
    }
    return sumDigits;
}



int numberOfDigits(long long number){
    int retValue = 0;
    while(number > 0){
        retValue++;
        number = number/10;
    }
    return retValue;
}

long long getLastNDigits(int nDigits, long long number){
    if(nDigits < 0){
        return 0;
    }
    long long retValue = number;
    int totalDigits = numberOfDigits(number);
    while(totalDigits > nDigits){
        retValue = retValue/10;
        totalDigits--;
    }
    return retValue;
}
    

bool hasCorrectNumberOfDigits(long long creditCardNumber){
    int nDigits = numberOfDigits(creditCardNumber);
    return nDigits == 13 || nDigits == 15 || nDigits ==16;
}
// @todo fix this function This function is bugged
bool hasValidChecksum(long long creditCardNumber){
    int modValue;
    long long remainingNumber = creditCardNumber;
    int sum = 0;
    int index = 0;
    do {
        index++;
        modValue = remainingNumber%10;
        remainingNumber = remainingNumber/10;
        
        if(index%2 == 0){
            // this is still incorrect, as we must add the digits;
            // printf ("secondary digit: %i ", modValue);
            // printf("doubled secondary digit: %i ", 2*modValue);
            sum += sumOfDigits(2*modValue);
        } else {
            // printf ("primary digit: %i ", modValue);
            sum += modValue;
        }
        // printf("\n");
    } while(remainingNumber > 0);
    return sum % 10 == 0;
}

// Check if credit card is valid
bool isValidGenericCreditCardNumber (long long creditCardNumber){
    return hasCorrectNumberOfDigits(creditCardNumber) && hasValidChecksum(creditCardNumber);
}

bool isAmexCard(long long creditCardNumber){
    int lastDigits = getLastNDigits(2,creditCardNumber);
    return numberOfDigits(creditCardNumber) == 15 && (lastDigits == 34 || lastDigits == 37);
}

bool isMastercardCard(long long creditCardNumber){
    int lastDigits = getLastNDigits(2,creditCardNumber);
    return (numberOfDigits(creditCardNumber) == 16 && (lastDigits >=51 && lastDigits <=55));
}

bool isVisaCard(long long creditCardNumber){
    int nDigits = numberOfDigits(creditCardNumber);
    int lastDigit = getLastNDigits(1,creditCardNumber);
    return (nDigits == 13 || nDigits ==16) && lastDigit == 4;
}

// Return the type of credit card it is
string getCreditCardType(long long creditCardNumber){
    string outputString;
    // Check for generic validity
    if(isValidGenericCreditCardNumber(creditCardNumber)){
        // Test cases for credit card number
        if(isAmexCard(creditCardNumber)){
            // Am card
            outputString = "AMEX";
        } else if(isMastercardCard(creditCardNumber)){
            // Master card
            outputString = "MASTERCARD";
        } else if(isVisaCard(creditCardNumber)){
            // Visa card
            outputString = "VISA";
        } else {
            outputString = "INVALID";
        }
    } else {
        outputString = "INVALID";
    }
    return outputString;
}

#ifdef COMPLETE_PROGRAM
int main(){
    printf("Number: ");
    string outputString;
    long long creditCardNumber = GetLongLong();
    outputString = getCreditCardType(creditCardNumber);
    printf("%s\n", outputString);
    return 0;
}
#endif


#ifdef SUM_OF_DIGITS
// testing the functions
int main(void){
    long long numberTest = 0;
    int sumOfD;
    for (int i = 0; i < 20; i++){
        printf("%i. %lld %i\n",i,numberTest, sumOfD);    
        numberTest = numberTest*10 + 1;
        sumOfD = sumOfDigits(numberTest);
    }
    
    
    
    
    return 0;
}
#endif

#ifdef NUMBER_OF_DIGITS

int main(void)
{
    long long numberTest = 1;
    int numberOfD = numberOfDigits(numberTest);
    for (int i = 0; i < 20; i++){
        printf("%i. %lld %i\n",i,numberTest, numberOfD);    
        numberTest = numberTest*10;
        numberOfD = numberOfDigits(numberTest);
    }
    return 0;
}

#endif

#ifdef GET_LAST_N_DIGITS

int main(void){
    long long value = 378282246310005;
    for(int i = 0; i < 6; i++){
        long long auxValue = getLastNDigits(i,value);    
        printf("%i. %lld\n", i, auxValue);
    }
    return 0;
    
}

#endif

#ifdef HAS_CORRECT_NUMBER_OF_DIGITS
#define LIST_SIZE 8
int main(void){
    long long listOfValues[LIST_SIZE] = {378282246310005,371449635398431,378734493671000,5555555555554444,5105105105105100,4111111111111111,4012888888881881,
        4222222222222};
    for(int i = 0; i < LIST_SIZE; i++){
        bool auxValue = hasCorrectNumberOfDigits(listOfValues[i]);    
        int nDigits = numberOfDigits(listOfValues[i]);
        printf("%i. %i %i\n", i, auxValue, nDigits);
    }
    return 0;
}
    
#endif

#ifdef HAS_VALID_CHECKSUM
#define LIST_SIZE 8
int main(void){
    long long listOfValues[LIST_SIZE] = {378282246310005,371449635398431,378734493671000,5555555555554444,5105105105105100,4111111111111111,4012888888881881,
        4222222222222
    };
    for(int i = 0; i < LIST_SIZE; i++){
        bool auxValue = hasValidChecksum(listOfValues[i]);    
        printf("%i. %i\n", i, auxValue);
    }
    return 0;
}
    
#endif

#ifdef IS_VALID_GENERIC_CARD_NUMBER
#define LIST_SIZE 8
int main(void){
    // Correct list of values
    long long listOfValues[LIST_SIZE] = {378282246310005,371449635398431,378734493671000,5555555555554444,5105105105105100,4111111111111111,4012888888881881,
        4222222222222
    };
    printf("Should all be 1:\n");
    for(int i = 0; i < LIST_SIZE; i++){
        bool auxValue = isValidGenericCreditCardNumber(listOfValues[i]);    
        printf("%i. %i\n", i, auxValue);
    }
    long long listOfIncorrectValues[LIST_SIZE] = {1 , 114245512,3231242,23231425,378734493671002, 7722574501, 772257451213, 982897441};
    printf("Should all be 0:\n");
    for(int i = 0; i < LIST_SIZE; i++){
        bool auxValue = isValidGenericCreditCardNumber(listOfIncorrectValues[i]);    
        printf("%i. %i\n", i, auxValue);
    }
    return 0;
}


#endif

#ifdef IS_AMEX_CARD
int main(void){
    long long cardValue =378282246310005;
    bool isamex = isAmexCard(cardValue);
    bool ismaster = isMastercardCard(cardValue);
    bool isvisa = isVisaCard(cardValue);
    printf("amex:%i master:%i visa:%i\n", isamex,ismaster,isvisa);
    return 0;
}
#endif

#ifdef IS_MASTERCARD_CARD
int main(void){
    long long cardValue =5555555555554444;
    bool isamex = isAmexCard(cardValue);
    bool ismaster = isMastercardCard(cardValue);
    bool isvisa = isVisaCard(cardValue);
    printf("amex:%i master:%i visa:%i\n", isamex,ismaster,isvisa);
    return 0;
}
#endif

#ifdef IS_VISA_CARD
int main(void){
    long long cardValue =4111111111111111;
    bool isamex = isAmexCard(cardValue);
    bool ismaster = isMastercardCard(cardValue);
    bool isvisa = isVisaCard(cardValue);
    printf("amex:%i master:%i visa:%i\n", isamex,ismaster,isvisa);
    return 0;
}
#endif

