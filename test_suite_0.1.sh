#!/bin/bash

# Test Case 1: Display Prompt and Wait for User Input
echo "Test Case 1: Display Prompt and Wait for User Input"
echo -e "\n" | ./hsh
echo "==========================================="

# Test Case 2: Handling Ctrl+D (End of File Condition)
echo "Test Case 2: Handling Ctrl+D (End of File Condition)"
(echo -e "\x04" | ./hsh) 2>/dev/null
echo "==========================================="

# Test Case 3: Execute a Valid Command
echo "Test Case 3: Execute a Valid Command"
./hsh <<< "ls"
echo "==========================================="

# Test Case 4: Execute an Invalid Command
echo "Test Case 4: Execute an Invalid Command"
./hsh <<< "nonexistent_command"
echo "==========================================="

# Test Case 5: Execute Multiple Valid Commands
echo "Test Case 5: Execute Multiple Valid Commands"
./hsh <<< "ls
pwd"
echo "==========================================="

# Edge Case 1: Empty Command
echo "Edge Case 1: Empty Command"
./hsh <<< ""
echo "==========================================="

# Edge Case 2: Very Long Command
echo "Edge Case 2: Very Long Command"
# Create a very long command, e.g., a sequence of 'ls ' repeated 1000 times
long_command=$(printf "ls %.0s" {1..1000})
./hsh <<< "$long_command"
echo "==========================================="

# Edge Case 3: Command with Special Characters
echo "Edge Case 3: Command with Special Characters"
./hsh <<< "ls &"
echo "==========================================="

# Edge Case 4: Large Number of Commands
echo "Edge Case 4: Large Number of Commands"
# Create a sequence of commands, e.g., 'ls', 'pwd', and 'echo Hello', repeated 100 times
large_commands=$(printf "ls\npwd\necho Hello\n" {1..100})
./hsh <<< "$large_commands"
echo "==========================================="

# Add more test cases and edge cases as needed

echo "All test cases and edge cases completed"
