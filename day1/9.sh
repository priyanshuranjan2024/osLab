#!/bin/bash
# Format date command output to "02/01/2014/2:21:54 PM"

formatted_date=$(date "+%d/%m/%Y/%I:%M:%S %p")
echo "$formatted_date"
