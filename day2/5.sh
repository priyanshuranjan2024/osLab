#!/bin/bash

even_sum=0
even_count=0
odd_sum=0
odd_count=0

# read from file
while read num; do
    if [ $((num % 2)) -eq 0 ]; then
        even_sum=$((even_sum + num))
        even_count=$((even_count + 1))
    else
        odd_sum=$((odd_sum + num))
        odd_count=$((odd_count + 1))
    fi
done < "$1"

# even average
if [ $even_count -eq 0 ]; then
    echo "No even numbers found."
else
    even_avg=$(( $even_sum / $even_count ))
    echo "Average of even numbers: $even_avg"
fi

# odd average
if [ $odd_count -eq 0 ]; then
    echo "No odd numbers found."
else
    odd_avg=$(( $odd_sum / $odd_count ))
    echo "Average of odd numbers: $odd_avg"
fi
