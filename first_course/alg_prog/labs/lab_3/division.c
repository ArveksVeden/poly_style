#include "huge_math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void divide_numbers(char *num1, char *result) {
    char one[MAX_LENGTH] = "1"; // Число 1
    char temp_result[MAX_LENGTH] = "0"; // Инициализация результата
    char remainder[MAX_LENGTH];
    strcpy(remainder, one);

    // Проверка деления на ноль
    if (strcmp(num1, "0") == 0) {
        strcpy(result, "Ошибка: деление на ноль!");
        return;
    }

    strcat(temp_result, "."); // Добавляем начало дробной части
    int precision = 0;

    // Главный цикл для вычисления дробной части
    while (precision < 30 && strcmp(remainder, "0") != 0) { // Ограничиваем итерации для дробной части
        strcat(remainder, "0"); // Увеличиваем остаток
        int i;
        for (i = 9; i >= 0; i--) { // Ищем максимальный подходящий множитель
            char product[MAX_LENGTH];
            char digit[MAX_LENGTH];
            sprintf(digit, "%d", i);
            multiply_numbers(num1, digit, product);

            if (compare_absolute(product, remainder) <= 0) break; // Если результат не превышает остаток
        }

        char digit[MAX_LENGTH];
        sprintf(digit, "%d", i); // Добавляем цифру в результат
        strcat(temp_result, digit);

        char product[MAX_LENGTH];
        multiply_numbers(num1, digit, product);
        subtract_numbers(remainder, product, remainder); // Обновляем остаток

        precision++;
    }

    // Обрезаем до нужной точности
    int display_precision = 30; // Задаем количество знаков после запятой
    char *dot_pos = strchr(temp_result, '.');
    if (dot_pos != NULL) {
        int total_length = (dot_pos - temp_result) + 1 + display_precision;
        temp_result[total_length] = '\0'; // Обрезаем строку
    }

    strcpy(result, temp_result);
}