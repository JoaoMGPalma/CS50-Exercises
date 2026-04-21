"""
FILE: credit.py
DESCRIPTION: 
    A credit card validator that uses Luhn's Algorithm to verify checksums 
    and Regular Expressions to identify the card issuer (AMEX, MasterCard, or VISA).

USAGE: 
    python credit.py
    Input: A credit card number (digits only).

LOGIC:
    1. Luhn's Algorithm:
       - Reverse digits. 
       - Double every second digit. If result > 9, subtract 9.
       - Sum all digits. If sum % 10 == 0, it is a valid number.
    2. Issuer Detection: 
       - Uses regex patterns to check digit length and starting prefixes.
"""

import re

# Array of dictionaries -
# holds the identifier data (number of digits, starting digits)
# for each card issuer (AMEX, VISA, MASTERCARD)
issuers = [
    {"name": "AMEX", "len": r"^\d{15}$", "chk_digits": r"^3[47]"},
    {"name": "MASTERCARD", "len": r"^\d{16}$", "chk_digits": r"^5[1-5]"},
    {"name": "VISA", "len": r"^(\d{13}|\d{16})$", "chk_digits": r"^4"},
]

def calc_luhn(card_number):
    """Returns True if the card number passes Luhn's algorithm."""
    card_digits = [int(digit) for digit in card_number]
    
    doubled_digits = []
    other_digits = []

    # Reverse and iterate with index
    for i, digit in enumerate(reversed(card_digits)):
        if i % 2 != 0:
            doubled = digit * 2
            if doubled > 9:
                doubled -= 9
            doubled_digits.append(doubled)
        else:
            other_digits.append(digit)

    luhn_sum = sum(doubled_digits) + sum(other_digits)
    return luhn_sum % 10 == 0

def main():
    # Using built-in input() to remove cs50 dependency
    card_number = input("Number: ").strip()

    # Basic numeric check
    if not card_number.isdigit():
        print("INVALID")
        return

    found_match = False

    if calc_luhn(card_number):
        # Iterate through issuer patterns
        for i in issuers:
            if re.match(i["len"], card_number) and re.match(i["chk_digits"], card_number):
                print(f"{i['name']}")
                found_match = True
                break

        if not found_match:
            print("INVALID")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
