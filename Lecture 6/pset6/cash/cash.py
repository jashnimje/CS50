from cs50 import get_float

# Ask for input
while (True):
    # Get Float
    dollars = get_float("Change owed: ")
    if (dollars >= 0):
        break

# Convert to cents from dollars
cents = int(dollars * 100)

# Initialise coin variable
coin = 0

# Get coin of valuation 25
coin += cents // 25
cents = cents % 25

# Get coin of valuation 10
coin += cents // 10
cents = cents % 10

# Get coin of valuation 5
coin += cents // 5
cents = cents % 5

# Get coin of valuation 1
coin += cents // 1
cents = cents % 1

print(coin)