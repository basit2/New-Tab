#!/bin/bash
#Filename: menudriven.sh, Author: MD Basit Alam
while true; do
	clear
	t1=0
	directories=()
	for dir in Assignment*/; do
		if [ -d "$dir" ]; then
			t1=$((t1 + 1))
			directories+=("$dir")
			echo "${t1}.${dir}"
		fi
	done
	read -rp "Enter the assignment number [Only from 1 to 3]: " c1
	selected_dir="${directories[$((c1 - 1))]}"
	if [ -z "$selected_dir" ]; then
		echo "Invalid assignment number. Please enter a valid number."
		continue
	fi
	cd "$selected_dir" || continue

	t2=0
	scripts=()
	for file in *.sh; do
		if [ -f "$file" ]; then
			t2=$((t2 + 1))
			scripts+=("$file")
			echo "${t2}.${file}"
		fi
	done
	read -rp "Enter the program number: " c2
	selected_script="${scripts[$((c2 - 1))]}"
	if [ -z "$selected_script" ]; then
		echo "Invalid program number. Please enter a valid number."
		cd ..
		continue
	fi
	clear
	echo "$selected_script"
	printf "\n"
	"./$selected_script"
	printf "\n"
	echo "$selected_script executed successfully"
	read -rp "Press Enter to continue..."
	cd ..
done
