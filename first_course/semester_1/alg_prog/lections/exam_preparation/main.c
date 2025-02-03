#include <stdio.h>
#include <math.h>

void reverse(char *str, long long size)
{
    char *left = str;
    char *right = (str + size - 1);

    while (left < right)
    {
        char temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}

int main(void)
{
    char result[100];
    long long num = 0;

    printf("enter num: \n>> ");
    scanf("%lld", &num);

    if (num == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        printf("%s", result);
        return 0;
    }

    result[0] = (num > 0) ? '+' : '-';
    num = abs(num);

    int i = 1;
    while (num > 0)
    {
        result[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    reverse(result + 1, i - 1);
    printf("your string: %s", result);

    return 0;
}