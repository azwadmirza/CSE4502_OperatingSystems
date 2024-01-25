#!/bin/bash
directory="$1"

declare -A file_sizes_by_extension
total=0
find "$directory" -type f | while read -r i
do
  file_size=$(stat -c %s "$i")
  file_extension=$(echo "$i" | awk -F'.' '{print tolower($NF)}')
  file_sizes_by_extension["$file_extension"]=`expr ${file_sizes_by_extension["$file_extension"]} + $file_size`
  echo "$file_extension has size ${file_sizes_by_extension["$file_extension"]}";
  total=$(($total+$file_size))
  echo "Total Size: $total" | cat > resultTask1.txt;
done

cat resultTask1.txt

total_size=0

for extension in ${file_sizes_by_extension[@]}
do
  size=${file_sizes_by_extension["$extension"]}
  echo $size
  total_size=$(($total_size + $size))
  echo "$extension: $size bytes"
done


