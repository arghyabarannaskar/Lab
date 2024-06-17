echo "Enter the length of the rectangle: "
read len
echo "Enter the breadth of the rectangle: "
read br

area=$((len*br))
peri=$((2*(len+br)))

echo "The area of the rectangle is: $area"
echo "The Perimeter of the rectangle is: $peri"
