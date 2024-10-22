#include <stdio.h>

int main(void)
{
    for (unsigned short i = 65535; i > 0; i--)
    {
        printf("%u;", i);
    }
    printf("0");

    return 0;
}