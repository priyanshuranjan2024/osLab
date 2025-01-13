#!/bin/bash
# Adding two numbers passed as arguments

if [ $# -ne 2 ]; then
  echo "Usage: $0 num1 num2"
  exit 1
fi

num1=$1
num2=$2
sum=$((num1 + num2))

echo "The sum of $num1 and $num2 is: $sum"
