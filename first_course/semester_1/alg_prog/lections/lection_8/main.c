#include <stdio.h>

/*
    # бинарный поиск #
    *работает только с отсортированными массивами
    best: O(1) - элемент найден в середине массива
    worst: O(log_n)
    average: O(log_n)
*/
int binary_search(int target, int* data, int size)
{
    int low = 0, high = size - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2; // таким образом избегаем переполнения, так как (low + high) / 2, - могло бы привести к нему
        if (*(data + mid) == target)
        {
            return mid;
        } else if (*(data + mid) < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/*
    # линейный поиск с барьером #
    best: O(1) - элемент найден вначале массива
    worst: O(n) - элемент отсутствует || находится в конце массива
    average: O(n/2), что эквивалентно = O(n)
*/
int barrier_search(int target, int* data, int size)
{
    int last = *(data + size - 1);
    *(data + size - 1) = target;

    int i = 0;
    while (*(data + i) != target)
    {
        i++;
    }

    *(data + size - 1) = last;
    
    if (i < size - 1 || *(data + size - 1) == target)
    {
        return i;
    } else {
        return -1;
    }
}

/*
    # линейный поиск #
    best: O(1) - элемент найден вначале массива
    worst: O(n) - элемент отсутствует || находится в конце массива
    average: O(n/2), что эквивалентно = O(n)
*/
int line_search(int target, int* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (*(data + i) == target)
        {
            return i;
        }
    }
    return -1;
}

void bubble_sort(int* data, int size)
{
    short flag = 1, k = 0;
    while (flag)
    {
        flag = 0;
        for (int i = 1, temp = 0; i < size; i++)
        {
            if (*(data + i - 1) > *(data + i))
            {
                temp = *(data + i);
                *(data + i) = *(data + i - 1);
                *(data + i - 1) = temp;
                flag = 1;
            }
        }
    }
}
int main(void)
{
    int arr[10] = {42, 7, 63, 18, 95, 34, 56, 28, 11, 72};
    int user_num = 0, result = 0;
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("введите искомое число: \n");
    printf(">> ");
    scanf("%d", &user_num);

    // результат работы линейного поиска
    printf("# результат линейного поиска #\n");
    result = line_search(user_num, arr, size);
    if (result == -1)
    {
        printf(">> не найдено\n");
    } else {
        printf("ans: [ %d ]\n", result);
    }

    // результат работы линейного поиска с барьером
    printf("# результат линейного поиска с барьером #\n");
    result = barrier_search(user_num, arr, size);
    if (result == -1)
    {
        printf(">> не найдено\n");
    } else {
        printf("ans: [ %d ]\n", result);
    }

    // сортировка исходного массива
    bubble_sort(arr, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // результат работы бинарного поиска
    printf("# результат бинарного поиска #\n");
    result = binary_search(user_num, arr, size);
    if (result == -1)
    {
        printf(">> не найдено\n");
    } else {
        printf("ans: [ %d ]\n", result);
    }

    return 0;
}