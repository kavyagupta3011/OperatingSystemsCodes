/*    Program Number: 60 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will ignore a SIGINT signal and then reset it to the default action using the signal system call.
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	signal(SIGINT,SIG_IGN);
	for(int i=0;i<10;i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
	signal(SIGINT,SIG_DFL);
	printf("SIGINT Reset\n");
	for(int i=0;i<10;i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
}
