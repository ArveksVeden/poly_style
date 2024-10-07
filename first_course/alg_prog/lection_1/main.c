#include <stdio.h>

int main(void)
{
    short i = 0xffffe544;
    printf("%hx=%i", i, i);

    return 0;
}