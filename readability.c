#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int countWords(string text);
int countLetters(string text);
int countSentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int text_len = strlen(text);
    int n_letters = countLetters(text);
    int n_words = countWords(text);
    int n_sentences = countSentences(text);
    float L = ((float) n_letters/(float) n_words)*100;
    float S = ((float) n_sentences/(float) n_words)*100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", index);
    }
    printf("\n");
}

int countSentences(string text)
{
    int text_len = strlen(text), n_sentences = 0;

    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == '!' ||
            text[i] == '?' ||
            text[i] == '.')
        {
            n_sentences += 1;
        }
    }

    return n_sentences;
}

int countWords(string text)
{
    int text_len = strlen(text), n_words = 0;

    for (int i = 0; i < text_len; i++)
    {
        if (text[i] == ' ')
        {
            n_words += 1;
        }
    }

    return n_words+1;
}


int countLetters(string text)
{
    int text_len = strlen(text);
    int n_letters = 0;

    for (int i = 0; i < text_len; i++)
    {
        if (text[i] != ',' &&
            text[i] != '!' &&
            text[i] != '?' &&
            text[i] != '.' &&
            text[i] != ';' &&
            text[i] != ' ' &&
            text[i] != '\'')
        {
            n_letters += 1;
        }
    }

    return n_letters;
}
