/*    Program Number: 25a  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description:  
a. This program executes another program using the exec system call.  
*/  

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    char *args[] = {"./randomexec",NULL};
    execv(args[0], args);
}
