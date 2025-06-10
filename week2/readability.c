#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{

    string phrase = get_string("Text :");

    int index = 0;
    float spaces = 0;
    float sentences = 0;
    float letters = 0;

    while (phrase[index] != '\0')
    {
        if (isspace(phrase[index]))
        {
            spaces++;
        }
        else if (phrase[index] == '.' || phrase[index] == '!' || phrase[index] == '?')
        {
            sentences++;
        }
        else if (isalpha(phrase[index]))
        {
            letters++;
        }

        index++;
    }

    float words = spaces + 1;

    float l = 100.0 * letters / words;
    float s = 100.0 * sentences / words;

    float grade_index = 0.0588 * l - 0.296 * s - 15.8;
    float floored = floor(0.0588 * l - 0.296 * s - 15.8);
    float decimal = (grade_index - floored);

    grade_index = (decimal < 0.5) ? floored : floored + 1;

    if (grade_index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade not rounded : %f\n", (0.0588 * l - 0.296 * s - 15.8));
        printf("Grade %i\n", (int) grade_index);
    }
}
