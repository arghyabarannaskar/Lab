echo "Enter base salary: "
read b
read -p "Enter the percentage of da: " da
daAmount=`expr $b \* $da`
daAmount=$(echo "scale=2; $daAmount / 100" | bc)
echo "daAmount = $daAmount"
net=$(echo "scale=2; $b+$daAmount" | bc)
echo "Basic Salary: $b, da: $da, daAmount: $daAmount, Net salary is: $net"