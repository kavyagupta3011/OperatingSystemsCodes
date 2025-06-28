/*    Program Number: 15  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program displays the environmental variables of the user  
             using the environ variable.  
*/  

#include <stdio.h>
#include <unistd.h>

int main() {
    extern char **environ;
    
    if (!environ) {
        printf("No environment variables found.\n");
        return 1;
    }

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}
