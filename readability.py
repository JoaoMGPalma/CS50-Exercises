"""
FILE: readability.py
DESCRIPTION:
    Calculates the reading grade level of a text using the Coleman-Liau 
    index. This version uses pure Python built-ins, removing all 
    dependencies on external libraries like cs50.

USAGE:
    python readability.py
    Input: A string of text.

LOGIC:
    1. Parsing:
       - count_letters: Uses .isalpha() to count only alphabetic characters.
       - count_words: Counts spaces to determine word breaks.
       - count_sentences: Scans for '!', '?', or '.' to identify sentence ends.
    2. Calculation:
       - Computes L (avg. letters per 100 words) and S (avg. sentences per 100 words).
       - Applies the formula: index = 0.0588 * L - 0.296 * S - 15.8.
    3. Output:
       - Grades under 1 report as "Before Grade 1".
       - Grades 16 or higher report as "Grade 16+".
"""

def count_letters(text):
    """Function for counting letters on a text"""
    letter_count = 0
    for l in text:
        if l.isalpha():
            letter_count += 1
    return letter_count

def count_words(text):
    """Function for counting words on a text"""
    # Initialize at 1 assuming there is at least one word in a valid string
    word_count = 1
    for c in text:
        if c == ' ':
            word_count += 1
    return word_count

def count_sentences(text):
    """Function for counting sentences on a text"""
    sentence_dividers = ['!', '?', '.']
    sentence_count = 0
    for c in text:
        if c in sentence_dividers:
            sentence_count += 1
    return sentence_count

def main():
    # Using built-in input() instead of get_string to remove dependency
    text = input("Text: ")
    while (not text):
        text = input("Text: ")

    letter_count = count_letters(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)

    # Coleman-Liau index calculation
    L = (letter_count / word_count) * 100
    S = (sentence_count / word_count) * 100
    cl_index = round(0.0588 * L - 0.296 * S - 15.8)

    if cl_index >= 16:
        print("Grade 16+")
    elif cl_index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {cl_index}")

if __name__ == "__main__":
    main()
