count=0

for file in *; do
    if [ -f "$file" ] && [[ "$file" == *.sh ]]; then
        ((count++))
    fi
done

echo "Total number of shell scripts (.sh) in the current directory: $count"
