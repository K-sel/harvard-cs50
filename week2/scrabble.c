#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int array_contains(int arlen, char array[], char letter);
int count_points(string player_entry);

int main(int argc, string argv[])
{

    string player1_entry = get_string("Player 1 : ");
    string player2_entry = get_string("Player 2 : ");

    int player1_points = count_points(player1_entry);
    int player2_points = count_points(player2_entry);

    if (player1_points > player2_points)
    {
        printf("Player 1 wins !\n");
    }
    else if (player1_points < player2_points)
    {
        printf("Player 2 wins !\n");
    }
    else
    {
        printf("Tie !\n");
    }
}

int count_points(string player_entry)
{

    // Array lenght
    const int ONE_POINT_LETTER_ARRAY_LENGHT = 10;
    const int TWO_POINT_LETTER_ARRAY_LENGHT = 2;
    const int THREE_POINT_LETTER_ARRAY_LENGHT = 4;
    const int FOUR_POINT_LETTER_ARRAY_LENGHT = 5;
    const int FIVE_POINT_LETTER_ARRAY_LENGHT = 1;
    const int EIGHT_POINT_LETTER_ARRAY_LENGHT = 2;
    const int TEN_POINT_LETTER_ARRAY_LENGHT = 2;

    // Points attribution
    char one_points_letters[ONE_POINT_LETTER_ARRAY_LENGHT] = {'a', 'e', 'i', 'l', 'n', 'o', 'r', 's', 't', 'u'};
    char two_points_letters[TWO_POINT_LETTER_ARRAY_LENGHT] = {'d', 'g'};
    char three_points_letters[THREE_POINT_LETTER_ARRAY_LENGHT] = {'b', 'c', 'm', 'p'};
    char four_points_letters[FOUR_POINT_LETTER_ARRAY_LENGHT] = {'f', 'h', 'v', 'w', 'y'};
    char five_points_letter[FIVE_POINT_LETTER_ARRAY_LENGHT] = {'k'};
    char eight_points_letters[EIGHT_POINT_LETTER_ARRAY_LENGHT] = {'j', 'x'};
    char ten_points_letters[TEN_POINT_LETTER_ARRAY_LENGHT] = {'q', 'z'};

    int points = 0;

    for (int i = 0, n = strlen(player_entry); i < n; i++)
    {
        if (array_contains(ONE_POINT_LETTER_ARRAY_LENGHT, one_points_letters, player_entry[i]))
        {
            points++;
        }
        else if (array_contains(TWO_POINT_LETTER_ARRAY_LENGHT, two_points_letters, player_entry[i]))
        {
            points += 2;
        }
        else if (array_contains(THREE_POINT_LETTER_ARRAY_LENGHT, three_points_letters, player_entry[i]))
        {
            points += 3;
        }
        else if (array_contains(FOUR_POINT_LETTER_ARRAY_LENGHT, four_points_letters, player_entry[i]))
        {
            points += 4;
        }
        else if (array_contains(FIVE_POINT_LETTER_ARRAY_LENGHT, five_points_letter, player_entry[i]))
        {
            points += 5;
        }
        else if (array_contains(EIGHT_POINT_LETTER_ARRAY_LENGHT, eight_points_letters, player_entry[i]))
        {
            points += 8;
        }
        else if (array_contains(TEN_POINT_LETTER_ARRAY_LENGHT, ten_points_letters, player_entry[i]))
        {
            points += 10;
        }
    }

    return points;
}

int array_contains(int arlen, char array[], char letter)
{
    bool does_contains_letter = false;

    if (!islower(letter))
    {
        letter = tolower(letter);
    }

    for (int i = 0; i < arlen; i++)
    {

        if (array[i] == letter)
        {
            does_contains_letter = true;
        }
    }

    return does_contains_letter;
}
