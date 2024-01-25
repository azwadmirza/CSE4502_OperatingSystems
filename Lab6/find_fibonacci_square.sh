low=$1
high=$2
fib=(0 1)
squares=()
for ((i=1; i <= high; i++))
do
  nextnum=$(( fib[i] + fib[$(( i - 1 ))] ))
  fib+=($nextnum)
  
  square=$(echo "scale=0; sqrt($i)" | bc)
  if [ $i -le 1 ]
  then
    continue
  fi
  if [ $(($square*$square)) -eq $i ]
  then
    squares+=($i)
  fi
done
echo -n "List of Fibonacci: ["
for i in ${fib[@]}
do
  if [ $i -ge $low ]
  then
    if [ $i -le $high ]
    then
     echo -n "$i "
    fi
  fi
done
echo "]"

echo -n "List of Perfect Square: [" 
for i in ${squares[@]}
do
  echo -n "$i "
done
echo "]"
