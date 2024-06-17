file_count=0
dir_count=0

files=()
directories=()

for item in *; do
    if [ -f "$item" ]; then
        files+=("$item")   
        ((file_count++))
    elif [ -d "$item" ]; then
        directories+=("$item")
        ((dir_count++))
    fi
done

echo "Files in the current directory:"
printf '%s\n' "${files[@]}"

echo "Directories in the current directory:"
printf '%s\n' "${directories[@]}"

echo "Total files: $file_count"
echo "Total directories: $dir_count"
