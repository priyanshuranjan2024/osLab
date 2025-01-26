#!/bin/bash

#write a shell program to add two numbers and  do the same using command line arguments

echo "Enter two numbers"
read a
read b
sum=`expr $a + $b`
echo "Sum of $a and $b is $sum"


sum=`expr $1 + $2`
echo "Sum of $1 and $2 is $sum"

