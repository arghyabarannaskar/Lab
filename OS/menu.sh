ROOT_DIR=$(pwd)

choose_directory() {
  while true; do
    echo "Choose a directory:"
    echo "1) Assignment 1"
    echo "2) Assignment 2"
    echo "3) Assignment 3"
    echo "4) Quit"
    read -p "\nEnter your choice: " choice

    case $choice in
      1) DIRECTORY="Assignment 1";;
      2) DIRECTORY="Assignment 2";;
      3) DIRECTORY="Assignment 3";;
      4) echo "Quitting..."; exit 0 ;;
      *) echo "Invalid option. Try again." ; continue ;;
    esac

    cd "$ROOT_DIR/$DIRECTORY" || { echo "\nFailed to change directory"; exit 1; }
    list_scripts
  done
}

list_scripts() {
  while true; do
    echo "\nScripts in $DIRECTORY:"
    ls 
    echo "\nEnter the name of the script to run (type 'back' to change directory):"
    read -p "Script name: " script

    if [ "$script" == "back" ]; then
      cd "$ROOT_DIR"
      return
    elif [ "$DIRECTORY" == "Assignment 3" ] && [ "$script" == "one.sh" ]; then
       echo "Enter filename: "
       read filename
       ./one.sh $filename
    elif [ -f "$script" ]; then
      chmod +x "$script"
      echo "\nRunning $script..."
      ./"$script"
    else
      echo "\nScript not found. Try again."
    fi
  done
}

choose_directory
