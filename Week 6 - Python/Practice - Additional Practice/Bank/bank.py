usr_input = input("Greeting: ").lower().replace('"', "").replace(" ", "")


# If Starts with "hello", output $0
if usr_input.startswith("hello"):
    print("$0")

# If starts with "h", but not "hello" output $20
elif usr_input.startswith("h"):
    print("$20")

# Else output $100
else:
    print("$100")
