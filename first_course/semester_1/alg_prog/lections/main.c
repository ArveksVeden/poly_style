#include <stdio.h>
#include <math.h>


void reverse(char *str, long long size)
{
    char *left = str;
    char *right = (str + size - 1);
    char temp = ' ';

    while (left < right)
    {
        temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}
/*
    task_1
    Дано число long long. Нужно перевести в строку и в начале поставить + или -  
    в зависимости положительное оно или нет а после само число, если 0, то просто 0
*/
void task_1()
{
    char result[100];
    long long num = 0;

    printf("enter your num:\n>> ");
    scanf("%lld", &num);

    if (num == 0)
    {
        result[0] = (num + '0');
        result[1] = '\0';
        printf("%s\n", result);
        return;
    }

    result[0] = (num > 0) ? '+' : '-';
    num = abs(num);

    int i = 1;
    // получаем перевернутое число num со знаком в строке
    while (num > 0)
    {
        result[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    reverse((result + 1), i - 1);
    printf("%s\n", result);
}

int binarySearch(int *arr, int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    //task_1();
    int arr[] = {1, -3, 5, 11, 9, 0, 13, -15};
    int target = 9, size = sizeof(arr) / sizeof(arr[0]);
    //printf("%d\n", binarySearch(arr, size, target));
    bubble_sort(arr, size);
    for (int i = 0; i < size - 1; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");


    return 0;
}