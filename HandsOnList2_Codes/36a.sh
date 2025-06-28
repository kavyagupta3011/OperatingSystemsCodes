#Program Number: 36(a) 
#Student Name:  Kavya Gupta; Register Number: IMT2023016  
#Date:  12-05-2025 
#Description: This program will create a FIFO file using the mknod command.


#!/bin/bash

echo "Creating a FIFO file"

# Create a FIFO named 'myfifo'
mknod myfifo p

