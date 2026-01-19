/*
    Substitution Cypher
    This program implements a classic substitution cipher.
    It takes a 26‑character key as a command‑line argument and
    uses it to encrypt a plaintext string provided by the user.

    Features:
    - Validates that the key contains exactly 26 characters
    - Preserves the case of alphabetic characters
    - Leaves non‑alphabetic characters unchanged
    - Converts the key to lowercase internally for consistent indexing

    For testing use the cypher 'ZYXWVUTSRQPONMLKJIHGFEDCBA' and 
    provide a text to be transformed (ex. "Hello World!")
    Expected output: ciphertext: Svool Dliow! 
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int key_size = 26;

char *cypherText(char *text, char *key);

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 2)
    {
        printf("Provide one argument: Key\n");
        return 1;
    }

    if (strlen(argv[1]) != key_size)
    {
        printf("Key must contain 26 caharacters.");
        return 1;
    }

    char *key = argv[1];

    // Replace get_string with fgets
    char plain_text[256];
    printf("plaintext: ");
    fgets(plain_text, sizeof(plain_text), stdin);

    // Remove trailing newline if present
    plain_text[strcspn(plain_text, "\n")] = '\0';

    char *cipher_text = cypherText(plain_text, key);

    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

char *cypherText(char *text, char *key)
{
    char *cipher_text = text;

    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = tolower(key[i]);
    }

    for (int i = 0; i < strlen(text); i++)
    {
        int ascii_value = text[i];
        if (isupper(text[i])) // Upper case char
        {
            cipher_text[i] = toupper(key[ascii_value - 'A']);
        }
        else if (islower(text[i])) // Lower case char
        {
            cipher_text[i] = tolower(key[ascii_value - 'a']);
        }
        else
        {
            if (ascii_value > 32 && ascii_value != 127)
                cipher_text[i] = text[i];
        }
    }

    return cipher_text;
}
