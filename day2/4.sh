#!/bin/bash

# Check for maximum 8 arguments
if [ "$#" -gt 8 ]; then
    echo "Error: Please provide a maximum of 8 integers."
    exit 1
fi

# Ensure at least two arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Error: Please provide at least two integers."
    exit 1
fi


a=$1
b=$2

if [ $((a % b)) -eq 0 ]; then
    result=$((a / b))
elif [ $((b % 5)) -eq  0 ]; then
    result=$((a * b))
elif [ $a -gt $b ]; then
    result=$((a - b))
else
    result=$((a + b))
fi

echo "Result: $result"
