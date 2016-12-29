#include <cs50.h>
#include <stdio.h>

int GetPositiveInt(){
    int n;
    do {
        n = GetInt();
    } while(n < 1);
    return n;
}