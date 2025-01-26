#!/bin/bash

even_sum=0
odd_sum=0 

while read num; do
    if [ $((num % 2)) -eq 0 ]; then
        even_sum=$((even_sum + num)) #even sum will be calculated
    else
        odd_sum=$((odd_sum + num))  #odd sum will be calculated
    fi
done <"$1" #will take the file as input from the command line argument

echo "Even sum: $even_sum"
echo "Odd sum: $odd_sum"