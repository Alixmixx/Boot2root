input_file="./turtle"
output_file="output.txt"
sed -e 's/Tourne gauche de \([0-9]\+\(\.[0-9]\{1,3\}\)\?\) degrees/t.left(\1)/g' \
    -e 's/Avance \([0-9]\+\(\.[0-9]\{1,3\}\)\?\) spaces/t.forward(\1)/g' \
    -e 's/Recule \([0-9]\+\(\.[0-9]\{1,3\}\)\?\) spaces/t.backward(\1)/g' \
    -e 's/Tourne droite de \([0-9]\+\(\.[0-9]\{1,3\}\)\?\) degrees/t.right(\1)/g' \
    $input_file > $output_file