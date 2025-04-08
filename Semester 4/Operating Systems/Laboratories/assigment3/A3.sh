#!/bin/bash
#Write a shell script which takes as parameters two words followed by several file names. 
#The script will replace any occurrence of the first word with the second word in each line of the given files.

if [ "$#" -lt 3 ]; then
    echo "Usage: $0 word1 word2 file1 [file2 ...]"
    exit 1
fi

word1=$1
word2=$2
shift 2 

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi
    sed -i "" "s/[[:<:]]$word1[[:>:]]/$word2/g" "$file"
done