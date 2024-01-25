var=$1
len=${#var}
for (( i=0; i<len; i++))
do
  char=${var:$i:1}
  case $char in 
    [aeiou])
    ;;
  *)
    echo -n $char
    ;;
  esac
done
