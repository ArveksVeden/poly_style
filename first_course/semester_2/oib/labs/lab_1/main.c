#include <stdio.h>

// расширенный алгоритм Евклида (находит НОД и коэффиценты x, y)
// вычисляет НОД(a, b), а также находит коэффициенты x и y такие, что ax + by = НОД(a, b)
int extended_gcd(int a, int b, int *x, int *y)
{
    // большее число записываем на первое место
    if (a < b)
    {
        int temp = b;
        b = a;
        a = temp;
    }

    // Если b == 0, то НОД(a, 0) = a, и x = 1, y = 0 (основной случай)
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    // промежуточные коэффиценты
    int x1, y1;
    // рекурсивный вызов: вычисляем gcd(b, a % b) и получаем x1, y1
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1; // новый x берется из предыдущего y
    *y = x1 - (a / b) * y1; // новый y вычисляется по формулы

    return gcd;
}

// алгоритм Евклида (поиск НОД)
int gcd(int a, int b)
{
    // большее число записываем на первое место
    if (a < b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int main(void)
{
    int a = 0, b = 0, x = 0, y = 0;
    printf("enter a, b: ");
    scanf("%d %d", &a, &b);

    printf("[standart] GCD(%d, %d) = %d\n", a, b, gcd(a, b));
    printf("[extended] GCD(%d, %d) = %d\n", a, b, extended_gcd(a, b, &x, &y));
    printf("coefficients (ax + by = GCD(a, b)): %d*%d + %d*%d = %d", a, x, b, y, gcd(a, b));

    return 0;
}