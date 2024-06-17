for file in *~; do
    if [ -f "$file" ]; then  
        rm "$file"           
        echo "Deleted: $file"
    fi
done

