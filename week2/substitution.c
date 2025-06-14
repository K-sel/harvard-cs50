#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_LENGTH 26

int indexOf(char array[], char letter_to_find);
int check_key(char key[], char regular_alphabet[]);
string substitute(char key[], string user_input, char regular_alphabet[]);

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc != 2)
    {
        printf("You must provide one and only one argument.\n");
        return 1;
    }
    else if (strlen(key) != ALPHABET_LENGTH)
    {
        printf("You must provide a key containing %i characters.\n", ALPHABET_LENGTH);
        return 1;
    }
    else
    {
        // lowercase the key
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            key[i] = tolower(key[i]);
        }

        // Composing lowercase alphabet array
        char regular_alphabet[ALPHABET_LENGTH];
        for (int i = 0; i < ALPHABET_LENGTH; i++)
        {
            regular_alphabet[i] = 'a' + i;
        }

        if (check_key(key, regular_alphabet) == 1)
        {
            printf("Key must contain every letter of alphabet once.\n");
            return 1;
        }
        else
        {
            string user_input = get_string("plaintext: ");
            string output = substitute(key, user_input, regular_alphabet);
            printf("ciphertext: %s\n", output);
        }
    }
}

int check_key(char key[], char regular_alphabet[])
{

    // all chars must be lowercase
    char current_letter;
    int index;

    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {

        current_letter = key[i];
        index = indexOf(key, regular_alphabet[i]);

        if (index == -1)
        {
            return 1;
        }
    }

    return 0;
}

int indexOf(char array[], char letter_to_find)
{
    // all chars must be lowercase
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (array[i] == letter_to_find)
        {
            return i;
        }
    }

    return -1;
}

string substitute(char key[], string user_input, char regular_alphabet[])
{
    int input_length = strlen(user_input);
    int index;
    string output = user_input;
    for (int i = 0; i < input_length; i++)
    {
        if (isalpha(user_input[i]))
        {
            index = indexOf(regular_alphabet, tolower(user_input[i]));

            if (index != -1)
            {
                if (isupper(user_input[i]))
                {
                    output[i] = toupper(key[index]);
                }
                else if (islower(user_input[i]))
                {
                    output[i] = tolower(key[index]);
                }
            }
        }
        else
        {
            output[i] = user_input[i];
        }
    }

    return output;
}
