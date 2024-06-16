def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass
        else:
            print("Error")


def main():
    x = get_int("x: ")
    print(x)


main()
