for file in *.exe; do
    if [ -f "$file" ]; then 
        new_name="${file%.exe}.sh"  
        mv "$file" "$new_name"  
        echo "Renamed: $file -> $new_name"
    fi
done
