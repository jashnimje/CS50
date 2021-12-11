from cs50 import get_int

# Ask for height of the pillar
while (True):
    height = get_int("Height: ")
    if (height >= 1) and (height <= 8):
        break

# Loop for height times
for i in range(1, height+1):
    # Print blank space height - i times
    print(" " * (height - i), end="")

    # Print # for i times
    print("#" * i, end="  ")

    # Print second pattern
    print("#" * i)
