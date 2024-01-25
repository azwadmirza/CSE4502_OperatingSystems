n=$1
fib=(0 1)
echo "1"
for ((i=1; i <= n; i++))
do
  nextnum=$(( fib[i] + fib[$(( i - 1 ))] ))
  fib+=($nextnum)
done

for num in {1..5}
do
  echo "${fib[$num]}"
done
