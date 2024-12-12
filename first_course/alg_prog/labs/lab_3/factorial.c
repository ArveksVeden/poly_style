#include "huge_math.h"
#include <stdlib.h>
#include <string.h>

void factorial_number(const char *num, char *result) {
    char current[MAX_LENGTH];
    char one[MAX_LENGTH] = "1";
    char temp_result[MAX_LENGTH];

    // Если число отрицательное, факториал не определён
    if (num[0] == '-') {
        strcpy(result, "Ошибка: факториал отрицательных чисел не существует!");
        return;
    }

    // Начальные условия
    strcpy(result, "1");
    strcpy(current, num);

    // Итеративное умножение
    while (strcmp(current, "0") != 0) {
        multiply_numbers(result, current, temp_result); // result *= current
        strcpy(result, temp_result);

        subtract_numbers(current, one, current); // current -= 1
    }
}
