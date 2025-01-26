#!/bin/bash

#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory_path> <number_of_files_to_keep>"
    exit 1
fi

# Assign arguments to variables
DIRECTORY=$1
NUM_FILES_TO_KEEP=$2

# Validate directory
if [ ! -d "$DIRECTORY" ]; then
    echo "Error: Directory $DIRECTORY does not exist."
    exit 1
fi

# Validate NUM_FILES_TO_KEEP
if ! [[ "$NUM_FILES_TO_KEEP" =~ ^[0-9]+$ ]]; then
    echo "Error: Number of files to keep must be a positive integer."
    exit 1
fi

# Find and delete files, keeping the latest N files
FILES_TO_DELETE=$(ls -t "$DIRECTORY" | tail -n +$((NUM_FILES_TO_KEEP + 1)))

if [ -z "$FILES_TO_DELETE" ]; then
    echo "No files to delete. $NUM_FILES_TO_KEEP files or fewer are present in $DIRECTORY."
else
    echo "$FILES_TO_DELETE" | while read -r FILE; do
        rm -f "$DIRECTORY/$FILE"
        echo "Deleted: $FILE"
    done
fi

echo "Done. Kept the latest $NUM_FILES_TO_KEEP files in $DIRECTORY."
