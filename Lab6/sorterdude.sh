a=$@

if [ "$1" == "-h" ]
then
    echo "./sorterdude.sh sorts a list of N unsorted numbers in order provided and optionally removes duplicate numbers from that list
    Syntax: ./sorterdude.sh <number_1> <number_2> ... <order> <unique>
    Parameter 1 <number_1>: First number in the list
    Parameter 2 <number_2>: Second number in the list
    ...
    Parameter N <number_N>: Nth number in the list
    <order>: -a for ascending or -d for descending order of sorting
    <unique>(optional): -u to ensure each number appears exactly once in the sorted list"
    exit
 fi

if [ $# -le 2 ]
then
    echo "Syntax Error!!
           Syntax: ./sorterdude.sh <number_1> <number_2> ... <order> <unique>
           For more information type: ./sorterdude.sh -h"
fi       

len=${a[*]}
num=()
commands=()
for i in ${a[@]}
do
  if [[ $i =~ ^[0-9]$ ]]
  then
    num+=($i)
  else
    commands+=($i)
  fi

done




len=${#num[*]}
for ((i=0; i < $len; i++))
do
  min=${num[$i]}
  min_ix=$i
  for ((j=$i+1; j< $len; j++))
  do
    val=${num[$j]}
    if [ $val -lt $min ]
    then
      min_ix=$j
      min=$val
    fi
  done

  temp=${num[$min_ix]}
  num[$min_ix]=${num[$i]}
  num[$i]=$temp
done

if [ ${#commands[*]} -ge 2 ]
   then
   sorted=() 
   if [ "${commands[1]}" == "-u" ]
   then
       for ((i=0; i<$len;i++))
       do 
        if [[ ${sorted[@]} =~ ${num[$i]} ]]
        then
            continue
        else
            sorted+=(${num[$i]})
        fi
       done
       num=($(echo "${sorted[@]}"))
   fi
fi
   
    
        
    


if [ "${commands[0]}" == "-a" ]
then
echo ${num[*]}
else
for ((i=$len-1; i>=0;i--))
do
echo -n "${num[$i]} "
done
fi

