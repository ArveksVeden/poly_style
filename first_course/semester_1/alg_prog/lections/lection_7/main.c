/*
    # рекурсивная функция #
*/

#include <stdio.h>
// пример рекурсивной функции
void recursive_func(int count)
{
    if (count == 0)
    {
        return;
    } else {
        printf("Recursion call: %d\n", count);
        recursive_func(count - 1);
    }
}

// прямая рекурсия
void print_numbers(int num)
{
    if (num > 0)
    {
        printf("%d\n", num);
        // прямой вызов самой себя
        print_numbers(num - 1);
    }
}

// косвенная рекурсия
void functionA(int n);
void functionB(int n);
void functionA(int n)
{
    if (n > 0)
    {
        printf("A: %d\n", n);
        functionB(n - 1);
    }
}
void functionB(int n)
{
    if (n > 0)
    {
        printf("B: %d\n", n);
        functionA(n - 1);
    }
}

// функция вычисления факториала
int factorial(int n)
{
    if (n > 1)
    {
        return n * factorial(n - 1);
    }
}

int main(void)
{
    //recursive_func(5);
    //print_numbers(10);
    //functionA(10);
    printf("5! = %d", factorial(5));

    return 0;
}