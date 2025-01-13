#!/bin/bash
# Extract date data and format it

date_output=$(date)
# Example: "Thu Jan 2 14:21:54 IST 2014"

day=$(echo $date_output | awk '{print $3}')
month=$(echo $date_output | awk '{print $2}')
year=$(echo $date_output | awk '{print $6}')
time=$(echo $date_output | awk '{print $4}')

formatted_time=$(echo $time | sed 's/:/./g')
echo "$day/$month/$year/$formatted_time"
