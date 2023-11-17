#!/bin/bash
# Directory containing the files
directory="./ft_fun"

# Loop through all files in the directory
for file in "$directory"/*.pcap
do
    # Extract the last line from the file
    last_line=$(tail -n 1 "$file")

    # Extract all characters starting from the third character of the last line
    new_name=${last_line:2}

    # Rename the script file to the new name
    # Note: $0 contains the name of the script being executed
    cp "$file" "$directory/end/$new_name"
done

# Loop again on all files an extract the first lane and put it in a file

for i in {1..749} 
do
    # Extract the first line from the file
    first_line=$(head -n 1 "./ft_fun/end/file$i")

    # Extract all characters starting from the third character of the last line
    echo "$first_line" >> "$directory"/end/output.txt
    rm ./ft_fun/end/file$i
done

cat ./ft_fun/end/file750 >> "$directory"/end/output.txt
rm ./ft_fun/end/file750