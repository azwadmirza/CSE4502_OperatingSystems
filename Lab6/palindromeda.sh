str=$1
len=${#str}
for (( i=0; i<$(($len/2)); i++))
do
  char=${str:$i:1}
  rev=$(($len-$i-1))
  char2=${str:$rev:1}
  if [ $char -eq $char2 ]
  then
    continue
  else
    echo "I am Groot! Try Again!"
    exit
  fi
done
echo "I am Groot!"
