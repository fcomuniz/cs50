#include <cs50.h>
#include <stdio.h>

int GetPositiveInt(){
    int n;
    do {
        printf("minutes: ");
        n = GetInt();
    } while(n < 1);
    return n;
}

int main(void){
    
    int minutes = GetPositiveInt();
    int nOfBottles = 12*minutes;
    printf("bottles: %i\n", nOfBottles);
    
}