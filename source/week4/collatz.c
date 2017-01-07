#include <stdio.h>
#include <stdlib.h>

int collatz(int n){
	int retValue = 1;
	if (n==1){
		return 0;
	}
	else if(n%2 == 0){
		retValue += collatz(n/2);
	} else {
		retValue += collatz(3*n + 1);
	}
	return retValue;
}

int main(int argc, char * argv[]){

	int val = 1;

	if(argc > 1){
		val = collatz(atoi(argv[1]));

	}
	
	printf("%i\n",val);

	return 0;
}
