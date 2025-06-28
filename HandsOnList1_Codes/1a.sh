#    Program Number: 1a 
#    Student Name:  Kavya Gupta; Register Number: IMT2023016 
#    Date:  04-04-2025 
#    Description: This program creates different types of files, specifically a 
#    soft link, using shell commands .


#!/bin/bash
ln -s $1 $2
echo "Soft Line Created"
ls -l