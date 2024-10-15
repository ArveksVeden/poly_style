#include <stdio.h>

int main(void)
{
    int int_part1 = 0, int_part2 = 0, frac_part1 = 0, frac_part2 = 0;
    int frac1[3] = {0, 0, 0}, frac2[3] = {0, 0, 0}, frac3[3] = {0, 0, 0};
    int int_res = 0, frac_res = 0;
    scanf("%d.%d+%d.%d", &int_part1, &frac_part1, &int_part2, &frac_part2);
    frac1[0] = frac_part1;

    for (int i = 2; i >= 0; i--)
    {
        frac2[i] = frac_part2 % 10;
        frac_part2 /= 10;
    }

    int_res = int_part1 + int_part2; //5

    frac3[2] = (frac1[2] + frac2[2]);
    frac3[1] = (frac1[1] + frac2[1]) + (frac3[2] / 10);
    frac3[2] = frac3[2] % 10;
    frac3[0] = (frac1[0] + frac2[0]) + (frac3[1] / 10);
    frac3[1] = frac3[1] % 10;
    int_res += frac3[0] / 10;
    frac3[0] = frac3[0] % 10;

    short cout = 2;
    if (frac3[2] == 0)
    {
        cout = 1;
        if (frac3[1] == 0)
        {
            cout = 0;
        }
    }

    printf("%d.", int_res);
    for (int i = 0; i <= cout; i++)
    {
        printf("%d", frac3[i]);
    }

    return 0;
}