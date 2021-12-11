from cs50 import get_int
from cs50 import get_float
from cs50 import get_string


def main():
    # Main Code
    while (True):
        n = get_int("Number: ")
        if (n > 0 or int(n)):
            break

    # Cards Name array
    cards = {1: "MASTERCARD", 2: "AMEX", 3: "VISA"}

    count = len(str(n))

    # If the digits are less than 13 than invalid directly
    if (count < 13):
        ans = -1
    else:
        ans = check(n)

    if (ans > 3 or ans < 1):
        print("INVALID")
    else:
        print(cards[ans])


def check(no):
    # Check Code here
    count = len(str(no))
    ans = -1
    n = int(str(no)[0] + str(no)[1])

    # MasterCard Check
    if ((count == 16) and (n == 51 or n == 52 or n == 53 or n == 54 or n == 55)):
        ans = 1

    # AMEX Check
    elif ((count == 15) and (n == 34 or n == 37)):
        ans = 2

    # VISA Check
    elif ((count == 13 or count == 16) and (n // 10 == 4)):
        ans = 3

    i = count
    total = 0
    for i in range(count-2, -1, -2):
        val = 2 * int(str(no)[i])
        if val >= 10:
            total += val % 10
            val = val // 10
        total += val % 10

    for i in range(count-1, -1, -2):
        total += int(str(no)[i])

    if (total % 10 == 0):
        return ans
    return -1


# Call main method
main()