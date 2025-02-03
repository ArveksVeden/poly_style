#include "huge_math.h"
#include <stdlib.h>
#include <string.h>

void power_numbers(char *base, char *exponent, char *result) {
    char temp[MAX_LENGTH] = "1";  // Промежуточный результат
    char current_exp[MAX_LENGTH]; // копия степени, чтобы не изменять оригинал
    int is_negative = 0;

    // Проверяем знак степени
    if (exponent[0] == '-') {
        is_negative = 1;
        // копируем в current_exp из exponent + 1 - указатель + 1, и сколько байт копируем
        memmove(current_exp, exponent + 1, strlen(exponent)); // Убираем знак "-"
    } else {
        strcpy(current_exp, exponent);
    }

    // Обрабатываем нулевую степень
    if (strcmp(current_exp, "0") == 0) {
        strcpy(result, "1");
        return;
    }

    // Обрабатываем положительные степени
    while (strcmp(current_exp, "0") != 0) {
        char temp_result[MAX_LENGTH];
        multiply_numbers(temp, base, temp_result); // temp *= base
        strcpy(temp, temp_result);

        // Уменьшаем степень на 1
        char one[MAX_LENGTH] = "1";
        subtract_numbers(current_exp, one, current_exp); // current_exp--
    }

    // Если степень отрицательная, делим 1 на результат
    if (is_negative) {
        divide_numbers(temp, result); // result = 1 / temp
    } else {
        strcpy(result, temp);
    }
}
