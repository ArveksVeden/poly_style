#include <stdio.h>

int is_palindrom(int num)
{
    int original = num;
    if (num < 0)
    {
        return 0;
    }

    int reverse = 0;
    while (num != 0)
    {
        reverse = (reverse * 10) + (num % 10);
        num /= 10;
    }

    return original == reverse;
}

int main(void)
{
    int num = 0;
    scanf("%d", &num);
    if (is_palindrom(num))
    {
        printf("num is palind.\n");
    } else {
        printf("num is NOT palind.\n");
    }

    return 0;
}