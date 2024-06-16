from csv import *
from sys import *


def main(argv):

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Please Enter 3 Arguments")
        exit(1)

    # First Argument is of CSV File, and second if of Text filename

    # TODO: Read database file into a variable
    rows = []

    with open(argv[1]) as csv_file:
        reader = DictReader(csv_file)
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    sequences = []

    with open(argv[2]) as database_file:
        sequences = database_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    List_of_STR = reader.fieldnames
    List_of_STR.remove("name")
    DNA_Things = {}

    for STR in List_of_STR:
        DNA_Things[STR] = longest_match(sequences, STR)

    # TODO: Check database for matching profiles
    for people in rows:
        match = True
        for STR in List_of_STR:
            if int(people[STR]) != DNA_Things[STR]:
                match = False
                break
        if match == True:
            print(people["name"])
            exit(0)

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# Calling main to execute file
main(argv)
