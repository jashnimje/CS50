from cs50 import get_string
import csv
import sys
import random


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Open file names
    csvfile = sys.argv[1]
    txtfile = sys.argv[2]

    # Open csv file
    with open(csvfile) as file:
        reader = csv.DictReader(file)
        dict_reader = list(reader)

    # Open txt file
    with open(txtfile) as file:
        sequence = file.read()

    # Store Key length and Sequence and dict names Length
    nCsv = len(reader.fieldnames)
    nSeq = len(sequence)
    nNames = len(dict_reader)

    # Store counts of all the fieldnames or dna in Dictionary
    mydict = {}

    # Answer variable
    ans = 'No match'

    # Loop over the value
    for i in range(nCsv):
        strDna = reader.fieldnames[i]
        mydict[strDna] = 0

        for j in range(nSeq):
            count = 0
            if sequence[j: (j+len(strDna))] == strDna:
                while sequence[j + (count * len(strDna)): (j + (count + 1) * len(strDna))] == strDna:
                    count += 1

                if (mydict[strDna] < count):
                    mydict[strDna] = count

    for i in range(nNames):
        count = 0
        for j in range(1, nCsv):
            dnaName = reader.fieldnames[j]
            # print(dnaName, dict_reader[i]['name'], dict_reader[i][dnaName], mydict[dnaName])
            if (int(dict_reader[i][dnaName]) != int(mydict[dnaName])):
                break
            count += 1
        if (count == (nCsv - 1)):
            ans = dict_reader[i]['name']
            break

    print(ans)


main()
