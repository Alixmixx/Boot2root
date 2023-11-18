#!/bin/bash

tar -xf fun


for file in ./ft_fun/*.pcap
do
    last_line=$(tail -n 1 $file)
    new_name=${last_line:2}
    mv $file ./ft_fun/$new_name
done

for i in {1..749} 
do
    first_line=$(head -n 1 ./ft_fun/file$i)
    echo $first_line >> ./ft_fun/output.txt
    rm ./ft_fun/file$i
done

cat ./ft_fun/file750 >> ./ft_fun/output.txt
rm ./ft_fun/file750

cat ft_fun/output.txt | grep Now | grep -o '"[^"]*"' > flag.txt
string=$(cat ft_fun/output.txt | grep return | rev | cut -c 3 | rev | tr -d '\n') 

echo $string >> flag.txt

hash_value=$(echo -n "$string" | openssl sha256)

echo "SHA-256 hash of \"$string\":" >> flag.txt
echo "$hash_value" >> flag.txt

