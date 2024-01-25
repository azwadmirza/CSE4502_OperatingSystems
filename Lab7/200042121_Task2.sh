#!/bin/bash


directory="$1"

mkdir -p "$directory/last_7_days"
mkdir -p "$directory/last_30_days"
mkdir -p "$directory/older_than_30_days"

find "$directory" -type f -mtime -7 -exec mv {} "$directory/last_7_days" \;
find "$directory" -type f -mtime +6 -mtime -31 -exec mv {} "$directory/last_30_days" \;
find "$directory" -type f -mtime +30 -exec mv {} "$directory/older_than_30_days" \;


