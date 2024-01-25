#! /bin/bash
read -r -p 'Enter your Password: ' PASS
len=${#PASS}
if [[ $PASS =~ [A-Z] ]] 
then 
  if [ $len -ge 8 ]
  then
    if [[ $PASS =~ [a-z] ]]
    then
      if [[ $PASS =~ [0-9] ]]
      then
        echo "Strong Password"
      else
        echo "Weak Password"
      fi
    else
      echo "Weak Password"
    fi
  else
    echo "Weak Password"
  fi
else
  echo 'Weak Password'
fi

