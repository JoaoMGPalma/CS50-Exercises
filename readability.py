from cs50 import get_string

# Function for counting letters on a text


def count_letters(text):
    letter_count = 0
    for l in text:
        if l.isalpha():
            letter_count += 1

    return letter_count

# Function for counting words on a text


def count_words(text):
    word_count = 1
    for c in text:
        if c == ' ':
            word_count += 1

    return word_count

# Function for counting senteces on a text


def count_sentences(text):
    sentence_dividers = ['!', '?', '.']
    sentence_count = 0
    for c in text:
        if c in sentence_dividers:
            sentence_count += 1

    return sentence_count


def main():
    text = get_string("Text: ")
    while (not text):
        text = get_string("Text: ")

    letter_count = count_letters(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)

    # Coleman-Liau index calculation
    L = (letter_count / word_count)*100
    S = (sentence_count / word_count)*100
    cl_index = round(0.0588 * L - 0.296 * S - 15.8)

    if cl_index >= 16:
        print("Grade 16+")
    elif cl_index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {cl_index}")


if __name__ == "__main__":
    main()
