# created with ChatGPT
# https://chat.openai.com/chat/f248dcbd-04b9-47e5-9696-abdb06dc87a4

import os
import re
import subprocess
import sys


# Get the name of the executable from the command-line arguments
print(len(sys.argv))

if len(sys.argv) < 2:
    print("Usage: python3 run_debugy.py <executable>")
    print("Example: python3 run_debugy.py bin/tests/CubeShooter/StarMap/StarMapTest")
    sys.exit(1)
executable_name = sys.argv[1]


# Define the directory to search for C++ source files
search_dir = "src/"

# Define the regular expression to match the debug statement
debug_regex = r"\/\/\s*DEBUG:"

# Find all the C++ source files in the directory
cpp_files = [os.path.join(root, filename)
             for root, dirnames, filenames in os.walk(search_dir)
             for filename in filenames
             if filename.endswith(".cpp")]

print(cpp_files)

# Loop over each C++ source file
for cpp_file in cpp_files:
    # Open the file and read its contents
    with open(cpp_file, "r") as f:
        contents = f.read()

    # Use regular expressions to find the line with the debug statement
    match = re.search(debug_regex, contents)
    if match:
        # Extract the line number of the debug statement
        line_number = contents.count('\n', 0, match.start()) + 1

        # Launch an lldb session with a breakpoint on the debug statement
        # subprocess.run(["lldb", "-o", f"breakpoint set -f {cpp_file} -l {line_number}", "--", "a.out"])
        subprocess.run(["lldb",
                        "-o", f"breakpoint set -f {cpp_file} -l {line_number}",
                        "-o", "run",
                        "--", executable_name])


