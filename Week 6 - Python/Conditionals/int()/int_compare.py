from cs50 import get_int

x = get_int("Number 1: ")
y = get_int("Number 2: ")

if x > y:
    print("x is greater than y")
elif y > x:
    print("y is greater than x")
else:
    print("both numbers are same")
