files=()


mkdir missing_files
while read -r line
do
  if [ ! -e $line ]; then
    echo "$line is not present"
    touch "missing_files/$line"
  else
    echo "$line is present"
  fi
done<$1
