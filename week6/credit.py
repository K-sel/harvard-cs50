import cs50

number = cs50.get_int("Number: ")
number_str = str(number)


def main():
    if luhn(number):
        if len(number_str) == 15 and number_str[:2] in ["37", "34"]:
            print("AMEX")
        elif len(number_str) in [13, 16] and number_str[:1] == "4":
            print("VISA")
        elif len(number_str) == 16 and int(number_str[:2]) in range(51, 56):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def luhn(n):
    total = 0
    double = False

    while n > 0:
        digit = n % 10
        n //= 10

        if double:
            digit *= 2
            if digit > 9:
                digit -= 9

        total += digit
        double = not double

    return total % 10 == 0


main()
