# The old and gold Readability

from cs50 import get_string


def main():
    text = get_string("Text: ")

    level = read(text)

    print(level)


def read(text):
    # Counting the number of letters
    num_letters = count_letters(text)

    # Counting the number of words
    num_words = text.count(" ") + 1

    # Counting the Number of Sentences
    num_sentences = 0
    num_sentences += text.count(".")
    num_sentences += text.count("!")
    num_sentences += text.count("?")

    # Calculating Reading level as per coleiman liau index
    L = (num_letters / num_words) * 100.0
    S = (num_sentences / num_words) * 100.0

    level = 0.0588 * L - 0.296 * S - 15.8

    # Rounding it to the nearest integer
    level = round(level)

    # Returning something as per requirement
    if level < 1:
        return "Before Grade 1"
    elif level > 16:
        return "Grade 16+"
    else:
        return f"Grade {level}"


def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1
    return count


# Calling Main
main()
