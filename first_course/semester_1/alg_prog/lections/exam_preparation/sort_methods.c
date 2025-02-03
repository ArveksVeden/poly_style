#include <stdio.h>

/*
    Цель сортировки данных - облегчить последующий поиск элементов

    экономное использование памяти: эти сортировки не используют дополнительную память (т.е. O(1))
    *- сортировки на том же месте*
*/

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void print_array(int *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(data + i));
    }
    printf("\n");
}

// сортировка пузырьком
void bubble_sort(int *data, int size)
{
    int flag;

    for (int i = 0; i < size - 1; i++)
    {
        flag = 0;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (*(data + j) > *(data + j + 1))
            {
                swap((data + j), (data + j + 1));
                flag = 1; // была хоть одна перестановка
            }
        }

        if (!flag)
        {
            // если не было перестановок за весь проход => массив отсортирован
            break;
        }
    }
}

// сортировка вставками
void insertion_sort(int *data, int size)
{
    int key, j;

    for (int i = 0; i < size - 1; i++)
    {
        key = *(data + i);
        j = i;

        while (j > 0 && key < *(data + j - 1))
        {
            
        }
    }
}

int main(void)
{
    int arr[7] = {-1, 0, 9, 3, -48, 4, 10};
    int size = 7;
    //bubble_sort(arr, size);
    print_array(arr, size);

    return 0;
}