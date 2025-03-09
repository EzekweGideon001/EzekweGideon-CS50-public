# Here's a little Easter egg showing that I, Ezekwe Gideon Somtochukwu actually wrote this code. IG:@lets_patois
from cs50 import get_string

def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Implement Coleman-Liau formula
    L = (letters *  100.0) / words
    S = (sentences * 100.0) / words
    index = 0.0588 * L - 0.296 * S - 15.8

    # Print out the grades according to the index
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")



def count_letters(text):
    # Initialise the counter
    count = 0

    # Loop through and count each alphabet character.
    for char in text:
        if char.isalpha():
            count += 1
    return count

def count_words(text):
    # Split technique learnt from Programming with Mosh (YouTube channel)
    return len(text.split())


def count_sentences(text):
    count = 0

    # Loop through and count terminal punctuations
    for char in text:
        if char in [".", "?", "!"]:
            count += 1
    return count

# Calling the main function
main()
