sum=$(ls -l | awk '{total += $5} END {print total}')
echo "Total size of all files in current directory: $sum bytes"