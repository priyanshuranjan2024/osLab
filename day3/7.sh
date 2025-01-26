#wap to distribute all files in a folder to different folders according to file type
#wap to display current time in am pm format
#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

# Assign argument to a variable
SOURCE_DIR=$1

# Validate directory
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Directory $SOURCE_DIR does not exist."
    exit 1
fi

# Iterate over files in the source directory
for FILE in "$SOURCE_DIR"/*; do
    # Skip if it's not a file
    if [ ! -f "$FILE" ]; then
        continue
    fi

    # Get the file extension (lowercase)
    EXTENSION=$(echo "${FILE##*.}" | tr '[:upper:]' '[:lower:]')

    # Handle files with no extension
    if [ "$EXTENSION" == "$FILE" ]; then
        EXTENSION="no_extension"
    fi

    # Create a subfolder for the file type if it doesn't exist
    TARGET_FOLDER="$SOURCE_DIR/$EXTENSION"
    mkdir -p "$TARGET_FOLDER"

    # Move the file to the appropriate folder
    mv "$FILE" "$TARGET_FOLDER"
    echo "Moved $FILE to $TARGET_FOLDER"
done

echo "File organization by type is complete."
