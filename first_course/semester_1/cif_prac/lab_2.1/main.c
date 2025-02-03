#include <stdio.h>

int main(void)
{
    int user_num = 0, res = 0;
    scanf("%i", &user_num);
    while (user_num != 0)
    {
        if (user_num > 0 && user_num % 10 == 7)
        {
            res++;
        }
        scanf("%i", &user_num);
    }
    printf("%i", res);

    return 0;
}