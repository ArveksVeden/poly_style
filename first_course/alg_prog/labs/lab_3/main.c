#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct {
    char digits[MAX_DIGITS + 1]; // +1 для нуль-терминатора
    int sign; // 1 для положительных, -1 для отрицательных
} BigInt;

// Функция для инициализации BigInt
void initBigInt(BigInt *num, const char *str) {
    if (str[0] == '-') {
        num->sign = -1;
        strcpy(num->digits, str + 1);
    } else {
        num->sign = 1;
        strcpy(num->digits, str);
    }
}

// Функция для сложения двух больших чисел
BigInt add(BigInt a, BigInt b) {
    // Реализация сложения
    // ...
}

// Функция для вычитания двух больших чисел
BigInt subtract(BigInt a, BigInt b) {
    // Реализация вычитания
    // ...
}

// Функция для умножения двух больших чисел
BigInt multiply(BigInt a, BigInt b) {
    // Реализация умножения
    // ...
}

// Функция для возведения в степень
BigInt power(BigInt base, int exp) {
    // Реализация возведения в степень
    // ...
}

// Функция для вычисления факториала
BigInt factorial(int n) {
    // Реализация факториала
    // ...
}

// Функция для суммы всех чисел от a до b
BigInt sumRange(int a, int b) {
    // Реализация суммы
    // ...
}

// Функция для вывода большого числа
void printBigInt(BigInt num) {
    if (num.sign == -1) {
        printf("-");
    }
    printf("%s\n", num.digits);
}

int main() {
    BigInt num1, num2;
    initBigInt(&num1, "123456789012345678901234567890");
    initBigInt(&num2, "987654321098765432109876543210");

    BigInt result = add(num1, num2);
    printf("Сумма: ");
    printBigInt(result);

    // Пример использования других функций
    // ...

    return 0;
}
