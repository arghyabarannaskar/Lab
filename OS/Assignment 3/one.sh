if [ $# -eq 0 ]
then
  echo "Usage: $0 filename"
  exit 1
fi

while IFS=' ' read -r num1 num2 num3
do
  sum=$((num1 + num2 + num3))
  echo "Sum of integers $num1, $num2, $num3 is: $sum"
done < "$1"
