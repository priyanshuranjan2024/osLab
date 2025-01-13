#!/bin/bash
# Move files and directories in "XYZ"

XYZ_DIR=~/XYZ
MYFILE_DIR="$XYZ_DIR/MyFile"
MYDIR_DIR="$XYZ_DIR/MyDir"

# Create destination directories if they don't exist
mkdir -p "$MYFILE_DIR" "$MYDIR_DIR"

# Move files to "MyFile"
find "$XYZ_DIR" -maxdepth 1 -type f -exec mv {} "$MYFILE_DIR" \;

# Move subdirectories to "MyDir"
find "$XYZ_DIR" -maxdepth 1 -type d ! -name "MyFile" ! -name "MyDir" ! -name "XYZ" -exec mv {} "$MYDIR_DIR" \;

echo "Files moved to $MYFILE_DIR and directories moved to $MYDIR_DIR."
