#!/bin/bash

directory=$1

if [ ! -d "$directory" ]; then
  echo "Directory does not exist."
  exit 1
fi

small_size=1024 
medium_size=1048576 

small_count=0
medium_count=0
large_count=0

echo "Files categorized by size in $directory:"

find "$directory" -type f | while read -r file; do
  file_size=$(stat -c "%s" "$file")

  if [ "$file_size" -le "$small_size" ]
  then
    echo "Small: $file"
    small_count=$(($small_count + 1))
  elif [ "$file_size" -le "$medium_size" ]
  then
    echo "Medium: $file"
    medium_count=$(($medium_count + 1))
  else
    echo "Large: $file"
    large_count=$(($large_count + 1))
  fi
  echo "Small files count: $small_count, Medium Files Count: $medium_count, Large files count:  $large_count" | cat > resultTask5.txt
done
cat resultTask5.txt
