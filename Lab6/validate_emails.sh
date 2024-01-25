invalid=()
valid=()

for i in $@
do
  if [[ $i =~ ^[a-zA-Z0-9.-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$ ]]
  then 
    valid+=($i)
  else 
    invalid+=($i)
  fi
done

echo "Valid Email Addresses:"
for i in ${valid[@]}
do
  echo $i
done
echo "Invalid Email Addresses:"
for i in ${invalid[@]}
do
  echo $i
done
