#!/bin/bash

mkdir -p large_files

read -r -p "Enter the size in bytes: " size

find . -type f -size +"$size"c -exec mv {} large_files/ \;

