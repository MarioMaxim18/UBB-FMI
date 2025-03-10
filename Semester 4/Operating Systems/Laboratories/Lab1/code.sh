#!/bin/bash

# Create a new directory called lab_2
mkdir -p ~/lab_2

# Navigate to lab_2 and create dir1
cd ~/lab_2
mkdir dir1

# Create dir2/dir2_1 in one line
mkdir -p dir2/dir2_1

# Verify directory structure using ls
echo "Listing structure of lab_2:"
ls -R

# Use tree to show structure
tree

# Create directories with different permissions
mkdir -m 000 dir2
mkdir -m 777 dir3

# List directory with details
ls -l

# Try entering dir2 (should fail due to permissions)
echo "Trying to enter dir2:"
cd dir2 2>/dev/null || echo "Permission denied"

# Create a file file1.txt in dir1
cd ~/lab_2/dir1
touch file1.txt

# Add text using cat
echo "This is a test file" | cat > file1.txt

# Display file content
cat file1.txt

# Alternative way: use nano
nano file2.txt

# Remove directories
cd ~/lab_2
rm -r dir1_1
rm -r dir2

# Create multiple directories in one command
mkdir dir3 dir4 dir5

# Create files in each directory
touch dir3/dir3_file1.txt dir4/dir4_file2.txt

# Copy file from dir3 to dir4
cp dir3/dir3_file1.txt dir4/

# Move file from dir4 to dir3
mv dir4/dir3_file1.txt dir3/

# Move dir3 to dir4
mv dir3 dir4

echo "Practice tasks completed!"