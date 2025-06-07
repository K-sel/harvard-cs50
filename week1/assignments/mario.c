#include <cs50.h>
#include <stdio.h>

int get_bricks(void);
void build_pyramide(int height);

int main(void)
{

    int bricks_wanted = get_bricks();

    build_pyramide(bricks_wanted);
}

int get_bricks(void)
{
    int bricks;

    do
    {
        bricks = get_int("How many bricks do you want ? : ");

        if (bricks <= 0)
        {
            printf("It must be at least 1 brick high...\n");
        }
    }

    while (bricks < 0);

    return bricks;
}

void build_pyramide(int height)
{
    for (int row = 0; row < height; row++)
    {

        for (int a = 1; a < height - row; a++)
        {
            printf(" ");
        }

        for (int b = 0; b <= 1; b++)
        {
            for (int col = 0; col <= row; col++)
            {
                printf("#");
            }
            printf("  ");
        }

        printf("\n");
    }
}
