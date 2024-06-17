if [ $# -eq 0 ]
then
    echo "Usage: $0 directory1 [directory2 ...]:"
    exit 1
fi

for dir in "$@"
do
    if [ -d "$dir" ]
    then
        echo "Disk usage for directory: $dir"
        du -b "$dir"
    else
        echo "$dir is not a directory"
    fi
done
