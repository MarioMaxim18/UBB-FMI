#!/bin/bash
#Write a shell script which takes as parameters several user accounts (ex: gmae0221 jpae0229). 
#The script will display those user accounts (from those given as parameters) that are currently connected to the server.

# Check if at least one user was given
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 user1 [user2 ...]"
    exit 1
fi

# Get the list of currently logged-in users
logged_in_users=$(who | awk '{print $1}' | sort -u)

# Check each given user
for user in "$@"; do
    if echo "$logged_in_users" | grep -w "$user"; then
        echo "User '$user' is currently logged in."
    fi
done