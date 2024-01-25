#! /bin/bash


for num in $*
do
  number=$num
while [ $number -gt 0  ]
do
result=`expr $number % 10`
echo -n $result
number=`expr $number / 10`
done
echo -n " "
done


