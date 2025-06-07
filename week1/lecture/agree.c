#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree ? : \n");

    c == 'y' ? printf("Agreed. \n") : printf("Not agreed. \n");
}
