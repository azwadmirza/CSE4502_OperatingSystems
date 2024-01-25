#!/bin/bash

mkdir $1
for i in $(find . -type f -name "*.$1")
do
  echo "Moving $i to $1/"
  mv $i $1/
done
