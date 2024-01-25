#! /bin/bash
read -r -p "Enter Directory Path 1: " dir1
read -r -p "Enter Directory Path 2: " dir2

if [ ! -d $dir1 ]
then
  exit 1
fi

if [ ! -d $dir2 ]
then
  exit 1
fi

diff -qsr $dir1 $dir2
