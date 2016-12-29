#include <stdio.h>
#include <cs50.h>
#include <math.h>

int findNumberOfCoins(float changeOwed){
    int possibleCoinTypes[] = {25,10,5,1};
    int coinTypeIndex = 0;
    changeOwed  = 100.0*changeOwed;
    int integerChangeOwed = round(changeOwed);
    int numberOfCoins = 0;
    do {
        if(integerChangeOwed - possibleCoinTypes[coinTypeIndex] < 0){
            coinTypeIndex++;
        } else {
            integerChangeOwed -= possibleCoinTypes[coinTypeIndex];
            numberOfCoins++;
        }
    } while(integerChangeOwed > 0);
    return numberOfCoins;
}

int main()
{
    float changeOwed;
    int numberOfCoins = 0;
    do {
        printf("How much change is owed? ");
        changeOwed = GetFloat();
    } while(changeOwed < 0.0);
    numberOfCoins = findNumberOfCoins(changeOwed);
    printf("%d\n", numberOfCoins);
    return 0;
}