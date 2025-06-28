/*    Program Number: 57 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will print system limitations for:
- Maximum length of arguments in the exec family of functions.
- Maximum number of simultaneous processes per user ID.
- Number of clock ticks (jiffies) per second.
- Maximum number of open files.
- Size of a page.
- Total number of pages in physical memory.
- Number of currently available pages in physical memory.
*/

#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Max Length of Arguments (exec family)           : %ld\n", sysconf(_SC_ARG_MAX));
    printf("Max no. of simultaneous processes per UID        : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("No. of Clock Ticks per Second                    : %ld\n", sysconf(_SC_CLK_TCK));
    printf("Max no. of open files                            : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Page Size                                        : %ld\n", sysconf(_SC_PAGESIZE));
    printf("Total no. of pages in physical memory            : %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("No. of available pages right now                 : %ld\n", sysconf(_SC_AVPHYS_PAGES));

    return 0;
}

