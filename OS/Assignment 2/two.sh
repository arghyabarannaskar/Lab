IFS=':' read -r -a directories <<< "$PATH"

for dir in "${directories[*]}"
do
    echo "Directory: $dir"
    if [ -d "$dir" ]
    then
        stat -c "\nPermission: %A\nModification Time: %y" "$dir"
    fi
done

