sum=0

echo "Enter a number: "
read num

while [ "$num" -ne 0 ]
do
    rem=$(($num%10))
    num=$(($num/10))
    sum=$((sum+rem))
done

echo "The sum of the digits of the number is $sum"
