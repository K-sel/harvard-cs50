#include <cs50.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int luhn_algorithm_check(long int number);
int count_digits(long int number);
int check_AMEX(long int number);
int check_VISA(long int number);
int check_MASTERCARD(long int number);

int main(void)
{
    long int number = get_long("Number : ");
    bool is_valid_number = luhn_algorithm_check(number);

    if (!is_valid_number)
    {
        printf("INVALID\n");
    }
    else if (check_VISA(number))
    {
        printf("VISA\n");
    }
    else if (check_AMEX(number))
    {
        printf("AMEX\n");
    }
    else if (check_MASTERCARD(number))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int luhn_algorithm_check(long int number)
{
    int luhn_sum = 0;
    int i = 0;

    do
    {
        i++;
        int decimal = number > 10 ? number % 10 : number;
        number /= 10;

        if (i % 2 == 0)
        {

            int product = decimal * 2;

            if (product > 9)
            {
                do
                {
                    luhn_sum += product % 10;
                    product /= 10;
                }
                while (product > 0);
            }
            else
            {
                luhn_sum += product;
            }
        }
        else
        {
            luhn_sum += decimal;
        }
    }
    while (number > 0);

    return luhn_sum % 10 == 0;
}

int count_digits(long int number)
{
    int count_divisons = 0;
    long int number_copy = number;

    do
    {
        number_copy /= 10;
        count_divisons++;
    }
    while (number_copy > 0);

    return count_divisons;
}

int check_AMEX(long int number)
{

    if (number && count_digits(number) == 15)
    {
        int number_of_digits = count_digits(number);
        long long int starting_two_digits = number / (long long int) pow(10, number_of_digits - 2);

        if (starting_two_digits == 34 || starting_two_digits == 37)
        {
            return true;
        }
    }

    return false;
}

int check_VISA(long int number)
{
    if (number && (count_digits(number) == 13 || count_digits(number) == 16))
    {
        int number_of_digits = count_digits(number);
        long long int first_digit = number / (long long int) pow(10, number_of_digits - 1);

        if (first_digit == 4)
        {
            return true;
        }
    }

    return false;
}

int check_MASTERCARD(long int number)
{
    if (number && count_digits(number) == 16)
    {
        int number_of_digits = count_digits(number);
        long long int starting_two_digits = number / (long long int) pow(10, number_of_digits - 2);

        if (starting_two_digits >= 51 && starting_two_digits <= 55)
        {
            return true;
        }
    }

    return false;
}
