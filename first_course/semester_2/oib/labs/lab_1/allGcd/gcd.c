#include <stdio.h>

// расширенный алгоритм Евклида
// ax + by = НОД(a, b)
long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    // базовый случай: если b = 0, то НОД = a
    // x = 1, y = 0
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    // рекурсивно вычисляем НОД(b, a % b) и коэффициенты x1, y1
    long long gcd = extended_gcd(b, a % b, &x1, &y1);

    // x = y1 (коэффициент от b на следующем шаге становится коэффициентом a)
    *x = y1;
    // y = x1 - (a / b) * y1 (коэффициент b корректируется с учетом деления)
    *y = x1 - (a / b) * y1;

    // возвращаем НОД, который остается неизменным на всех шагах
    return gcd;
}

// алгоритм Евклида (поиск НОД)
long long gcd(long long a, long long b)
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
    long long a = 0, b = 0, x = 0, y = 0;
    printf("enter a, b: ");
    scanf("%lld %lld", &a, &b);

    printf("[standart] GCD(%lld, %lld) = %d\n", a, b, gcd(a, b));
    printf("[extended] GCD(%lld, %lld) = %d\n", a, b, extended_gcd(a, b, &x, &y));
    // если y отрицательный, то d = y + a
    printf("coefficients (ax + by = GCD(a, b)): %lld*%lld + %lld*%lld = %lld", a, x, b, y, gcd(a, b));

    return 0;
}