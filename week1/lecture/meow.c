#include <cs50.h>
#include <stdio.h>

void meow(int n);
int get_positive_int(void);

// commentaire dans le code

int main(void)
{

    int n = get_positive_int();

    meow(n);
}

int get_positive_int(void)
{
    int times;

    do
    {
        times = get_int("What's the number o  f meows ? : ");
    }
    while (times <= 0);

    return times;
}

void meow(int n)
{
    for (int i = n; i > 0; i--)
    {
        printf("meow \n");
    }
}
