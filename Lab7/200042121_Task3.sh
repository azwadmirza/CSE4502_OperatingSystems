#!/bin/bash

read -p "Enter the search string: " search_string
read -p "Enter the replacement string: " replacement_string

directory=$1

if [ ! -d "$directory" ]; then
  echo "Directory does not exist."
  exit 1
fi

for file in "$directory"/*.txt; do
  if [ -f "$file" ]; then
    sed -i "s/$search_string/$replacement_string/g" "$file"
    echo "Replaced in: $file"
  fi
done

echo "Search and replace operation completed."


