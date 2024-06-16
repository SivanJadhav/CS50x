# Old and Gold Cash Problem

# Importing Get Float as per requirement
from cs50 import get_float


def main():
    # Amount owed, converted to cents
    while True:
        owed = (get_float("Amount Owed: ")) * 100  # type: ignore
        if owed < 0:
            pass
        else:
            break

    # Printing the amount of coins
    num_of_coins = greedy_alg(owed)

    print(num_of_coins)


def greedy_alg(am_owed):
    # Types of coins
    coins = [25, 10, 5, 1]

    # Counter for Counting Coins
    counter = 0

    # The Important Part
    while am_owed != 0:
        for n in coins:
            if am_owed >= n:
                counter += int(am_owed // n)
                am_owed -= n * (am_owed // n)

    # Returning The Amount of Coins
    return counter


# Calling Main for the code to function
main()
