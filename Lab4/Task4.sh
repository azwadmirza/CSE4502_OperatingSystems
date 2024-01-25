#!/bin/bash

create_directory_structure() {
    local path="$1"
    local dir_name="$2"
    local subdirectories="$3"
    local files="$4"

    mkdir -p "$path/$dir_name"

    for sub_dir in $subdirectories; do
        mkdir -p "$path/$dir_name/$sub_dir"
    done

    for file in $files; do
        touch "$path/$dir_name/$file"
    done
}
echo "Create a new directory structure."
read -p "Enter the base directory name: " base_dir
read -p "Enter subdirectory names (space-separated): " subdirs
read -p "Enter file names (space-separated): " files
create_directory_structure "$PWD" "$base_dir" "$subdirs" "$files"
echo "Directory structure created in $PWD/$base_dir"

