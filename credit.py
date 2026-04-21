import re
from cs50 import get_string

# Array of dictionaries -
# holds the identifier data (number of digits, starting digits)
# for each card issuer (AMEX, VISA, MASTERCARD)
issuers = [
    {"name": "AMEX", "len": r"^\d{15}$", "chk_digits": r"^3[47]"},
    {"name": "MASTERCARD", "len": r"^\d{16}$", "chk_digits": r"^5[1-5]"},
    {"name": "VISA", "len": r"^(\d{13}|\d{16})$", "chk_digits": r"^4"},
]

# Returns true if the provided card number is valid under the luhn's algorithm; False otherwise
def calc_luhn(card_number):
    card_digits = []
    for digit in card_number:
        card_digits.append(int(digit))

    doubled_digits = []
    other_digits = []

    for i, digit in enumerate(reversed(card_digits)):
        if i % 2 != 0:
            doubled = int(digit*2)
            if doubled > 9:
                doubled -= 9
            doubled_digits.append(doubled)
        else:
            other_digits.append(int(digit))

    luhn_sum = sum(doubled_digits) + sum(other_digits)
    return luhn_sum % 10 == 0


def main():
    # We ask the user to input the card number and use .strip() to clear any whitespace included by mistake
    card_number = get_string("Number: ").strip()

    found_match = False

    # If the calc_luhn funtion returns False we immediately return INVALID
    if calc_luhn(card_number):

        # Here we iterate the patterns for each card issuer and check if there's a match
        for i in issuers:
            if re.match(i["len"], card_number) and re.match(i["chk_digits"], card_number):
               print(f"{i["name"]}")
               found_match = True

        if not found_match:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()
