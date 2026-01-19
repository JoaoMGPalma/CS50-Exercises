/*
    Credit Card Validator

    This program validates a credit card number using Luhn’s algorithm
    and identifies the issuing network (AMEX, MASTERCARD, or VISA).

    Features:
    - Computes the length of the card number
    - Extracts individual digits by position
    - Implements Luhn’s checksum to detect invalid numbers
    - Checks card prefixes and length to determine the network
    - Prints the correct network name or "INVALID" when appropriate

    For testing use:
    4111111111111111 (Visa)
    4222222222222  (Visa)
    5105105105105100 (MasterCard)
    378282246310005 (American Express)
*/


#include <stdio.h>
#include <stdlib.h>

int getNumberLength(long long number);
int getNthDigit(long long cardNumber, int digit_position);
int luhnCheckSum(long long cardNumber);
int checkInvalid(long long cardNumber);
void checkNetwork(long long cardNumber);
void validateCC(long long cardNumber);

struct Card
{
    long long number;
    int length;
};

int main(int argc, char *argv[])
{
    struct Card card;

    printf("Number: ");
    scanf("%lld", &card.number);

    card.length = getNumberLength(card.number);

    validateCC(card.number);
    system("pause");
}

void validateCC(long long cardNumber)
{
    if (checkInvalid(cardNumber))
        return;
    else
        checkNetwork(cardNumber);
}

// Checks the number of digits in a number
int getNumberLength(long long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }

    return length;
}

// Returns the digit of a number at a set position
int getNthDigit(long long cardNumber, int digit_position)
{
    for (int i = 1; i < digit_position; i++)
    {
        cardNumber /= 10;
    }

    return cardNumber % 10;
}


// Checks all options for invalidation
int checkInvalid(long long cardNumber)
{
    int length = getNumberLength(cardNumber);
    int sum_last_digit = luhnCheckSum(cardNumber);
    int first_digit = getNthDigit(cardNumber, length);
    int second_digit = getNthDigit(cardNumber, length - 1);


    if ((length < 13 || length > 16) || (sum_last_digit != 0) ||
        (first_digit != 3 && first_digit != 4 && first_digit != 5))
    {
        printf("INVALID\n");
        return 1;
    }

    else
        return 0;

    return 0;
}

// Checks the Payment network
void checkNetwork(long long cardNumber)
{
    int length = getNumberLength(cardNumber);
    int first_digit = getNthDigit(cardNumber, length);
    int second_digit = getNthDigit(cardNumber, length - 1);
    int last_digit = getNthDigit(cardNumber, length);

    if (length == 15 && first_digit == 3)
    {
        if (second_digit == 4 || second_digit == 7)
            printf("AMEX\n");
        else
            printf("INVALID\n");
    }
    else if (length == 16 && first_digit == 5)
    {
        if (second_digit >= 1 && second_digit <= 5)
            printf("MASTERCARD\n");
        else
            printf("INVALID\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
        printf("VISA\n");
    else
        printf("INVALID\n");
}

int luhnCheckSum(long long number)
{
    int sum = 0;
    int length = getNumberLength(number);

    for (int i = 2; i <= length; i += 2)
    {
        int buffer = getNthDigit(number, i) * 2;

        if (buffer > 9)
            sum += (buffer / 10) + (buffer % 10);
        else
            sum += buffer;
    }

    for (int i = 1; i <= length; i += 2)
    {
        sum += getNthDigit(number, i);
    }

    return sum % 10;
}

