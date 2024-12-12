#include "huge_math.h"
#include <stdlib.h>
#include <string.h>

void multiply_numbers(const char *num1, const char *num2, char *result) {
    char abs_num1[MAX_LENGTH + 1], abs_num2[MAX_LENGTH + 1];
    int is_negative1 = (num1[0] == '-');
    int is_negative2 = (num2[0] == '-');

    // Убираем знак, если есть
    strcpy(abs_num1, is_negative1 ? num1 + 1 : num1);
    strcpy(abs_num2, is_negative2 ? num2 + 1 : num2);

    // Проверка на случай, если одно из чисел равно "0"
    if (strcmp(abs_num1, "0") == 0 || strcmp(abs_num2, "0") == 0) {
        strcpy(result, "0");
        return;
    }

    int len1 = strlen(abs_num1), len2 = strlen(abs_num2);
    int temp[MAX_LENGTH * 2] = {0};

    // Умножение в столбик
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int product = (abs_num1[i] - '0') * (abs_num2[j] - '0');
            int pos = len1 + len2 - i - j - 2;
            temp[pos] += product;
            if (temp[pos] >= 10) {
                temp[pos + 1] += temp[pos] / 10;
                temp[pos] %= 10;
            }
        }
    }

    int k = len1 + len2;
    while (k > 0 && temp[k - 1] == 0) k--; // Удаляем ведущие нули

    for (int i = 0; i < k; i++) {
        result[i] = temp[k - i - 1] + '0';
    }

    result[k] = '\0';

    // Добавляем знак, если результат отрицательный
    if (is_negative1 ^ is_negative2 && strcmp(result, "0") != 0) {
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
}
