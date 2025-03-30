#!/bin/bash
#Write a shell script which takes as parameters several file names. 
#The script will replace the 3rd word with the 1st word in each line of the given files. 
#The words shall contain only letters or numbers and shall be separated by ":".

#!/bin/bash

# Check if at least one file is given
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

# Loop through each file
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "File $file does not exist!"
        continue
    fi

   #replace 3rd field with 1st using awk
   awk -F: -v OFS=: '{ if (NF>=3) $3=$1; print }' "$file"
done