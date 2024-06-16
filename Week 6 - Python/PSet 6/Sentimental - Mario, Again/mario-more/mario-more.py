from cs50 import get_int


def main():
    # Getting User Input
    while True:
        height = get_int("Height: ")
        if height in range(1, 9):
            break

    # Printing Triangle
    triangle(height)


# Printing Triangle
def triangle(n):
    for i in range(n):
        print(" " * (n - 1 - i), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1), end="")
        print()


# Calling Main at The End
main()
