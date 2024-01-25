#!/bin/bash

check_permissions() {
    local file="$1"
    local permissions=$(stat -c %a "$file")

    insecure_permissions="777"

    if [[ "$insecure_permissions" == *"$permissions"* ]]; then
        echo "Insecure permissions found: $file (Permissions: $permissions)">>insecure_report
    fi
}

traverse_directory() {
    local directory="$1"
    
    for item in "$directory"/*; do
        if [ -d "$item" ]; then
            traverse_directory "$item"
        elif [ -f "$item" ]; then
            check_permissions "$item"
        fi
    done
}

if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "Error: The specified directory does not exist."
    exit 1
fi

echo "Checking for insecure permissions in directory: $directory"
traverse_directory "$directory"

echo "Permission check complete."

