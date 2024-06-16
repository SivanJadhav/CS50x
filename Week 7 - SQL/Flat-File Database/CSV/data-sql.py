from cs50 import SQL

db = SQL("sqlite:///journals.db")

day = input("Day: ")

row = db.execute("SELECT COUNT(*) AS n FROM journals WHERE day = ?", day)
row = row[0]

print(row["n"])
