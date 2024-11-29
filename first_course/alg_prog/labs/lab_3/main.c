#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Максимальная длина чисел
#define MAX 1001

// Функция для сложения двух больших чисел
void add(char num1[], char num2[], char result[]) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0, sum;
    int i, j, k = 0;

    char temp[MAX] = {0};

    i = len1 - 1;
    j = len2 - 1;

    while (i >= 0 || j >= 0 || carry) {
        sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        temp[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    // Реверс результата
    for (i = 0; i < k; i++) {
        result[i] = temp[k - i - 1];
    }
    result[k] = '\0';
}

// Функция для вычитания двух больших чисел
void subtract(char num1[], char num2[], char result[]) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int borrow = 0, diff, i, j, k = 0;

    char temp[MAX] = {0};

    // Проверка, какое число больше
    int is_negative = 0;
    if (len1 < len2 || (len1 == len2 && strcmp(num1, num2) < 0)) {
        // Если num1 < num2, то поменяем их местами и запомним знак
        is_negative = 1;
        char *temp_ptr = num1;
        num1 = num2;
        num2 = temp_ptr;

        int tmp_len = len1;
        len1 = len2;
        len2 = tmp_len;
    }

    i = len1 - 1;
    j = len2 - 1;

    while (i >= 0 || j >= 0) {
        diff = (num1[i] - '0') - borrow;
        if (j >= 0) diff -= (num2[j] - '0');

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        temp[k++] = diff + '0';
        i--;
        j--;
    }

    // Удаление ведущих нулей
    while (k > 1 && temp[k - 1] == '0') {
        k--;
    }

    // Реверс результата
    for (i = 0; i < k; i++) {
        result[i] = temp[k - i - 1];
    }
    result[k] = '\0';

    // Добавление минуса, если результат отрицательный
    if (is_negative) {
        for (i = strlen(result); i >= 0; i--) {
            result[i + 1] = result[i];
        }
        result[0] = '-';
    }
}


// Функция для умножения двух больших чисел
void multiply(char num1[], char num2[], char result[]) {
    // В процессе
}

// Функция для возведения в степень
void power(char base[], int exponent, char result[]) {
    // В процессе
}

// Функция для вычисления факториала
void factorial(int n, char result[]) {
    // В процессе
}

// Функция для вычисления суммы от числа до числа
void sum_from_to(int from, int to, char result[]) {
    // В процессе
}

int main() {
    char num1[MAX], num2[MAX], result[MAX];
    int choice, exponent, from, to, n;

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Сложение\n");
        printf("2. Вычитание\n");
        printf("3. Умножение\n");
        printf("4. Возведение в степень\n");
        printf("5. Факториал\n");
        printf("6. Сумма чисел от и до\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            // Вызов сложения
                printf("Введите первое число: ");
                scanf("%s", num1);
                printf("Введите второе число: ");
                scanf("%s", num2);
                add(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
            case 2:
                // Вызов вычитания
                printf("Введите первое число: ");
                scanf("%s", num1);
                printf("Введите второе число: ");
                scanf("%s", num2);
                subtract(num1, num2, result);
                printf("Результат: %s\n", result);
                break;
                break;
            case 3:
                // Вызов умножения
                break;
            case 4:
                // Вызов возведения в степень
                break;
            case 5:
                // Вызов факториала
                break;
            case 6:
                // Вызов суммы от и до
                break;
            case 0:
                return 0;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}
