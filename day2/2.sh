#!/bin/bash

echo "Enter a string: "
read str

reverse=""

# for (( i=${#str}-1; i>=0; i-- )); do
#     reverse="$reverse${str:$i:1}"
# done

reversed=$(echo "$str" | rev)

if [ "$str" == "$reverse" ]; then
    echo "The string is a palindrome."
else
    echo "The string is not a palindrome."
fi