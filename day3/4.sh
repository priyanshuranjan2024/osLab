#!/bin/bash

echo "Enter direcotry path"
read  directory_path


for item in "$directory_path"/*; do
    if [ -f "$item" ]; then
      echo "$item"
    fi
done