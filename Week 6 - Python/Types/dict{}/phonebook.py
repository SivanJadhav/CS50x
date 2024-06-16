people = [
    {"name": "Sivan", "age": "15"},
    {"name": "Sai", "age": "8"},
]

name = input("Name: ")

for person in people:
    if person["name"] == name:
        crr_name = person["name"]
        crr_age = person["age"]
        print(f"Found! | Name: {crr_name} | Age: {crr_age}")
        break
else:
    print("Not Found")
