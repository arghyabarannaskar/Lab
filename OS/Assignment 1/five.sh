read -p "Enter the login name: " username

user_info=$(grep "^$username:" /etc/passwd)

if [ -z "$user_info" ]
then
    echo "User '$username' not found"
    exit 1
fi

IFS=':' read -r user pass uid gid info home shell <<< "$user_info"

echo "User Information for '$username':"
echo "---------------------------------"
echo "Username      : $user"
echo "Password      : $pass"
echo "User ID       : $uid"
echo "Group ID      : $gid"
echo "User ID Info  : $info"
echo "Home Directory: $home"
echo "Login Shell   : $shell"
echo "---------------------------------"
