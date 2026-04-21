/**
 * FILE: readability.c
 * DESCRIPTION: 
 * Calculates the reading grade level of a text using the Coleman-Liau 
 * index. The formula is: index = 0.0588 * L - 0.296 * S - 15.8.
 *
 * USAGE: 
 * ./readability
 * Input: A string of text.
 *
 * LOGIC:
 * 1. Parsing: Iterates through the string once to count letters, words, 
 * and sentences based on character types and punctuation.
 * 2. Calculation: Computes L (avg. letters per 100 words) and S 
 * (avg. sentences per 100 words).
 * 3. Output: Rounds the result to the nearest integer grade.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Function prototypes using standard char pointers
int count_words(char *text);
int count_letters(char *text);
int count_sentences(char *text);

int main(void)
{
    char text[2048]; // Buffer for user input to remove cs50.h dependency

    printf("Text: ");
    
    // Use fgets for standard input instead of get_string
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        return 1;
    }

    int n_letters = count_letters(text);
    int n_words = count_words(text);
    int n_sentences = count_sentences(text);

    // Calculate Coleman-Liau index variables
    float L = ((float) n_letters / (float) n_words) * 100;
    float S = ((float) n_sentences / (float) n_words) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // Output formatting
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(char *text)
{
    int n_letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            n_letters++;
        }
    }
    return n_letters;
}

int count_words(char *text)
{
    int n_words = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            n_words++;
        }
    }
    
    return (length > 0) ? n_words + 1 : 0;
}

int count_sentences(char *text)
{
    int n_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            n_sentences++;
        }
    }
    return n_sentences;
}
