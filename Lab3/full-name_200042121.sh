echo "First Name: "
read fname
echo "Middle Name: "
read mname
echo "Last Name: "
read lname
echo "Hi ${lname}, do you want me to display your full name?[y/n]"
echo -e "\n\n\n"
read choice
echo -e "\n\n\n"
if [ "$choice" = "y" ]
then
  echo "Your Full Name is ${fname} ${mname} ${lname}."
elif [ "$choice" = "n" ]
then
  echo "Thank you ${lname} for your time"
else
  echo "Invalid Choice"
fi
