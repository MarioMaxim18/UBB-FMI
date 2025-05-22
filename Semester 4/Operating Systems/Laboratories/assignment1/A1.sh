#!/bin/bash
# Write a shell script that reads usernames from keyboard. 
# For each user, the script will display the number of times it was logged in to the server in the current month. 
# If he/she has not logged in at all during the current month, the script will display the message: "User X has never logged in during the current month".

echo "Enter username:"
read user

current_month=$(date +'%b')
count=$(last "$user" | grep "$current_month" | wc -l)

if [ "$count" -eq 0 ]; then
    echo "User $user has never logged in during the current month."
else
    echo "User $user has logged in $count times this month."
fi