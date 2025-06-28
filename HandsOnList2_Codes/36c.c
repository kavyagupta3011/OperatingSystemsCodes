/*    Program Number: 36(c) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will use the strace command to determine which command (mknod or mkfifo) is more efficient.
*/


// use strace command to find out, which command (mknod or mkfifo) is better.
//MKNOD is better 

// strace mknod fifoa p
// strace mkfifo fifob 

int main(){
  printf("MKNOD is better\n");
  return 0;
}
