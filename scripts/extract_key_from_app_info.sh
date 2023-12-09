#!/bin/bash

# Check if a key is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <key>"
    exit 1
fi

# Define the path to your text file
file_path="app.info"

if [ ! -f "$file_path" ]; then
  echo "Error: File \"$file_path\" not found."
  exit 2
fi

# Get the value for the specified key
key="$1"
value=$(grep "^$key=" "$file_path" | cut -d '=' -f 2)

# Check if the key was found
if [ -n "$value" ]; then
    echo "Value for $key: $value"
else
    echo "Key $key not found in the file."
fi

