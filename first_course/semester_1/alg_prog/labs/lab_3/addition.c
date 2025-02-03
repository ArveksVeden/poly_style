#include "huge_math.h"
#include <string.h>

void add_numbers(const char *num1, const char *num2, char *result) {
    char abs_num1[MAX_LENGTH + 1], abs_num2[MAX_LENGTH + 1];
    int is_negative1 = (num1[0] == '-');
    int is_negative2 = (num2[0] == '-');

    // Убираем знак, если он есть
    strcpy(abs_num1, is_negative1 ? num1 + 1 : num1);
    strcpy(abs_num2, is_negative2 ? num2 + 1 : num2);

    // Случай 1: оба числа положительные
    if (!is_negative1 && !is_negative2) {
        int carry = 0, sum = 0, i, j, k = 0; // carry - перенос
        char temp[MAX_LENGTH + 1]; // храним число в обратном порядке
        reverse_string(abs_num1); // будем складывать для удобства - от младшего до старшего разряда
        reverse_string(abs_num2);

        i = 0, j = 0;
        // работаем, пока числа не закончены или есть еще перенос
        while (i < strlen(abs_num1) || j < strlen(abs_num2) || carry) {
            int digit1 = (i < strlen(abs_num1)) ? abs_num1[i++] - '0' : 0;
            int digit2 = (j < strlen(abs_num2)) ? abs_num2[j++] - '0' : 0;
            sum = digit1 + digit2 + carry;
            temp[k++] = (sum % 10) + '0';
            carry = sum / 10;
        }

        temp[k] = '\0';
        reverse_string(temp);
        strcpy(result, temp);
    }
    // Случай 2: оба числа отрицательные
    // тогда просто складываем числа и добавляем в конце -
    else if (is_negative1 && is_negative2) {
        add_numbers(abs_num1, abs_num2, result);
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
    // Случай 3: одно из чисел отрицательное
    else {
        if (is_negative1) {
            // если отрицательное первое, то ответ: первое число - второе
            subtract_numbers(num2, abs_num1, result);
        } else {
            // если отрицательное второе, то ответ: второе число - первое
            subtract_numbers(num1, abs_num2, result);
        }
    }
}