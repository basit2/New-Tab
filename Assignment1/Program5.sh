#!/bin/bash
#Problem 1.5, Filename: Program5.sh, Author: MD Basit Alam
echo "Please enter a username:"
read username

user_entry=$(grep "^$username:" /etc/passwd)

if [ -n "$user_entry" ]; then
	# Extract relevant fields from the entry
	IFS=: read -r uname passwd uid gid info homedir shell <<<"$user_entry"

	# Display user details
	echo "Username: $uname"
	echo "User ID (UID): $uid"
	echo "Group ID (GID): $gid"
	echo "User ID Info: $info"
	echo "Home Directory: $homedir"
	echo "Login Shell: $shell"
else
	echo "User '$username' not found."
fi
