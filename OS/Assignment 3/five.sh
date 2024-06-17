for file in *.sh; do
    if [ -f "$file" ]; then 
        new_name="${file%.sh}.exe"  
        mv "$file" "$new_name"  
        echo "Renamed: $file -> $new_name"
    fi
done
