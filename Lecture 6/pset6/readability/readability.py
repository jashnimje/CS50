from cs50 import get_string


def main():
    st = get_string("Text: ")
    cWords = 0
    cSent = 0
    cLetters = 0
    n = len(st)

    # Loop over all the char and increment
    for i in range(n):
        if (st[i] == ' '):
            cWords += 1
        if (st[i].lower().isalpha()):
            cLetters += 1
        if (st[i] == '.' or st[i] == '!' or st[i] == '?'):
            cSent += 1
    cWords += 1

    # Calculate
    index = int(round(0.0588 * (cLetters * 100 / float(cWords)) - 0.296 * (cSent * 100 / float(cWords)) - 15.8))

    # Answer
    if (index < 1):
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade ", index)


# Main call
main()