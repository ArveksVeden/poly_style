#include "huge_math.h"
#include <stdlib.h>
#include <string.h>

void subtract_numbers(const char *num1, const char *num2, char *result) {
    char abs_num1[MAX_LENGTH + 1], abs_num2[MAX_LENGTH + 1];
    int is_negative1 = (num1[0] == '-');
    int is_negative2 = (num2[0] == '-');

    // Убираем знак, если он есть
    strcpy(abs_num1, is_negative1 ? num1 + 1 : num1);
    strcpy(abs_num2, is_negative2 ? num2 + 1 : num2);

    // Случай 1: оба числа положительные
    if (!is_negative1 && !is_negative2) {
        int cmp = compare_absolute(abs_num1, abs_num2);
        if (cmp == 0) {
            strcpy(result, "0");
            return;
        }

        // заем | diff - разность разрядов
        int borrow = 0, diff = 0, i, j, k = 0;
        char temp[MAX_LENGTH + 1];

        // |num1| > |num2|
        if (cmp > 0) {
            reverse_string(abs_num1);
            reverse_string(abs_num2);
            i = 0, j = 0;
            while (i < strlen(abs_num1) || j < strlen(abs_num2)) {
                int digit1 = (i < strlen(abs_num1)) ? abs_num1[i++] - '0' : 0;
                int digit2 = (j < strlen(abs_num2)) ? abs_num2[j++] - '0' : 0;
                digit1 -= borrow; // учитываем заем из предыдущего разряда

                if (digit1 < digit2) {
                    digit1 += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }

                diff = digit1 - digit2;
                temp[k++] = diff + '0';
            }

            while (k > 1 && temp[k - 1] == '0') k--; // Удаляем ведущие нули
            temp[k] = '\0';
            reverse_string(temp);
            strcpy(result, temp);
        // |num1| < |num2|
        } else {
            subtract_numbers(abs_num2, abs_num1, result);
            memmove(result + 1, result, strlen(result) + 1);
            result[0] = '-';
        }
    }
    // Случай 2: оба числа отрицательные
    else if (is_negative1 && is_negative2) {
        subtract_numbers(abs_num2, abs_num1, result);
    }
    // Случай 3: одно из чисел отрицательное
    else {
        if (is_negative1) {
            add_numbers(abs_num1, abs_num2, result);
            memmove(result + 1, result, strlen(result) + 1);
            result[0] = '-';
        } else {
            add_numbers(abs_num1, abs_num2, result);
        }
    }
}
