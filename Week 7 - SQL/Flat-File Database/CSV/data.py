import csv

from collections import Counter


def main():
    with open("journals.csv") as file:
        reader = csv.DictReader(file)
        counts = Counter()

        for row in reader:
            day = row["Name"]
            counts[day] += 1

    day = input("Day: ")

    print(f"{day}: {counts[day]}")


# Calling Main at The End
main()
