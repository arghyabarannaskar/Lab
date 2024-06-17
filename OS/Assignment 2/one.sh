for file in *
do
    if [ -f "$file" ]
    then
        echo "$file: is a file"
    fi
    if [ -d "$file" ]
    then
        echo "$file: is a directory"
    fi
done
