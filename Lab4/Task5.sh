#!/bin/bash
for file in $(find . -type f)
do
  du -h $file
  du -h $file > value
done
total_size=$(du -sh ./ | awk '{print $1}')
echo "Total Size: $total_size"
