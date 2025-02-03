#include "huge_math.h"
#include <stdio.h>
#include "locale.h"

#define MAX_LENGTH 1000

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    char num1[MAX_LENGTH], num2[MAX_LENGTH], result[MAX_LENGTH];
    int choice, power;

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Умножение\n");
        printf("4. Возведение в степень\n");
        printf("5. Факториал\n");
        printf("6. Сумма от и до\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                printf("Введите два числа: ");
                scanf("%s %s", num1, num2);
                add_numbers(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            case 2:
                printf("Введите два числа: ");
                scanf("%s %s", num1, num2);
                subtract_numbers(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            case 3:
                printf("Введите два числа: ");
                scanf("%s %s", num1, num2);
                multiply_numbers(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            case 4:
                printf("Введите число и степень: ");
                scanf("%s %s", num1, num2);
                power_numbers(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            case 5:
                printf("Введите число: ");
                scanf("%s", num1);
                factorial_number(num1, result);
                printf("Результат: %s\n", result);
                break;
            case 6:
                printf("Введите два числа (от и до): ");
                scanf("%s %s", num1, num2);
                sum_range(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            default:
                printf("Неверный выбор!\n");
        }
    }

    return 0;
}