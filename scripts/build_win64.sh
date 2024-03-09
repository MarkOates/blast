#!/bin/bash

# Check for the correct number of arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <project_name> <version>"
    exit 1
fi

# Assign command-line arguments to variables
project_name="$1"
version="$2"
source_release="${project_name}-${version}-SourceRelease"
win64_release="${project_name}-${version}-win64"

# Execute the command
reset && ./scripts/build_win64_release.sh "$source_release" "$version" "$win64_release"

