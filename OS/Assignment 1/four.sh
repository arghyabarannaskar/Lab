rev=0

read -p "Enter a number: " num
number=$num
while [ "$num" -ne 0 ]
do
    rem=$((num%10))
    num=$((num/10))
    rev=$((rev*10+rem))
done

echo "The reverse of $number is $rev"
