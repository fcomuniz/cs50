#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define INITIALS_SIZE 50

int getNonspaceStringPosition(string);

string getInitialsFromName(string);


int main()
{
    
    string name = GetString();
    
    string initials = getInitialsFromName(name);
    
    printf("%s\n",initials);
    
    return 0;
}


int getNonspaceStringPosition(string name){
    int n = strlen(name);
    int initialNameCharPos;
    for(initialNameCharPos = 0; initialNameCharPos < n && name[initialNameCharPos] == ' '; initialNameCharPos++);
    return initialNameCharPos;
}


string  getInitialsFromName(string name){
    
    // Loop through name
    string initials = malloc(INITIALS_SIZE*sizeof(char));

    int i=getNonspaceStringPosition(name); 
    int numberOfInitials = 0;
    initials[numberOfInitials] = toupper(name[i]);
    numberOfInitials++;
    i++;
    for(int n = strlen(name); i < n; i++){
        // Select the initials and put them in the return string
        if(name[i-1] == ' ' && name[i] != ' '){
            // Is initial so add to 
            initials[numberOfInitials] = toupper(name[i]);
            numberOfInitials++;
            
        }
        
    }
    initials[numberOfInitials] = '\0';
    return initials;
}
