#!/bin/bash

#find the sum of all values passed through command line  arguments

sum=0
for i in $*
do
    sum=$(($sum + $i))
done

echo "Sum: $sum"

