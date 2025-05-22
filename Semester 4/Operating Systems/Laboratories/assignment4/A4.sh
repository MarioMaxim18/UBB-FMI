#!/bin/bash
#Write a Shell program that supervises the system, such that: 
#each time certain users (given as parameters) connect to or disconnect from the system, 
#it will save in a file the username, time, if it’s new connection or disconnection, and the server on which the action was made.


if [ "$#" -lt 1 ]; then
    echo "Usage: $0 user1 [user2 ...]"
    exit 1
fi

log_file="activity.txt"
hostname=$(hostname)

while true; do
  for user in "$@"; do
    if who | grep -wq "$user"; then
      echo "$user $(date) CONNECTED on $hostname" >> "$log_file"
    else
      echo "$user DISCONNECTED on $hostname" >> "$log_file"
    fi
  done
  sleep 10
done