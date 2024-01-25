for file in $(find . -type f)
do
  filename="./$(date +%d%m%y)$(date +%T)$(basename $file)"
  mv $(basename $file) $filename
done
