# Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
# Import the get_int function from cs50 library
from cs50 import get_int

# Get an integer input from the user within the range of 1 and 8 (inclusive)
height = 0
while height not in range (1,9):
    height = get_int("Height: ")

# Loop over each row
for i in range(1, height + 1):
    # Print spaces and hashes for the left pyramid
    print(" " * (height - i) + "#" * i, end="  ")
    # Print hashes for the right pyramid
    print("#" * i)
