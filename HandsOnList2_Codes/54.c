/*    Program Number: 54 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will print system resource limits using the getrlimit system call.
*/

#include <stdio.h>
#include <sys/resource.h>

void print_limit(const char *name, int resource) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == 0) {
        printf("%sSoft Limit = %ld, Hard Limit = %ld\n", name, limit.rlim_cur, limit.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    print_limit("Stack size            : ", RLIMIT_STACK);
    print_limit("CPU time             : ", RLIMIT_CPU);
    print_limit("File size            : ", RLIMIT_FSIZE);
    print_limit("No. of files open    : ", RLIMIT_NOFILE);
    return 0;
}

