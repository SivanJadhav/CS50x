import sys
from pyfiglet import Figlet
from random import choices

figlet = Figlet()


def main():
    # Checking Number of Command Line Arguments
    if len(sys.argv) != 1 and len(sys.argv) != 3:
        print("Improper Usage")
        sys.exit(1)

    # Choosing Font based on number of args
    if len(sys.argv) == 1:
        figlet.setFont(font=(choices(figlet.getFonts())))

    elif len(sys.argv) == 3:
        if (sys.argv[1].startswith("-f") or sys.argv[1].startswith("--font")) and (
            sys.argv[2] in figlet.getFonts()
        ):
            figlet.setFont(font=sys.argv[2])
        else:
            sys.exit(1)

    # Getting User Input
    usr_input = input("Input: ")

    # Outputting Desired Text and Font
    print(figlet.renderText(usr_input))


# Calling main
main()
