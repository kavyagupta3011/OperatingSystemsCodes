/*    Program Number: 25b  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description:  
b. This program passes input arguments to an executable program and executes it.  
*/  

#include<stdio.h>
#include<unistd.h>

int main(){
    char *args[] = {"./Testing2obj","Argument1","Argument2",NULL};
    execv(args[0], args);
}

