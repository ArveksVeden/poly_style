#include "huge_math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void divide_numbers(char *num1, char *result) {
    char one[MAX_LENGTH] = "1"; // Число 1 - делитель
    char temp_result[MAX_LENGTH] = "0"; // Инициализация результата
    char remainder[MAX_LENGTH]; // текущий остаток от деления = 1
    strcpy(remainder, one);

    // Проверка деления на ноль
    if (strcmp(num1, "0") == 0) {
        strcpy(result, "Ошибка: деление на ноль!");
        return;
    }

    strcat(temp_result, "."); // Добавляем начало дробной части
    int precision = 0; // Текущая позиция после точки - для контроля точности

    // Главный цикл для вычисления дробной части
    while (precision < 30 && strcmp(remainder, "0") != 0) { // Ограничиваем итерации для дробной части
        strcat(remainder, "0"); // Увеличиваем остаток
        int i;
        for (i = 9; i >= 0; i--) { // Ищем максимальный подходящий множитель - от 9 до 0
            char product[MAX_LENGTH];
            char digit[MAX_LENGTH];
            sprintf(digit, "%d", i);
            multiply_numbers(num1, digit, product); // проверяем текущую цифру

            if (compare_absolute(product, remainder) <= 0) break; // Если результат не превышает остаток
        }

        char digit[MAX_LENGTH];
        sprintf(digit, "%d", i);
        strcat(temp_result, digit);  // Добавляем цифру в результат

        char product[MAX_LENGTH];
        multiply_numbers(num1, digit, product);
        // обновляем остаток - из него вычитается произведение текущей цифры i на делитель num1
        subtract_numbers(remainder, product, remainder);

        precision++;
    }

    // Обрезаем до нужной точности
    int display_precision = 30; // Задаем количество знаков после запятой
    char *dot_pos = strchr(temp_result, '.'); // Находим положение точки во временном результате
    if (dot_pos != NULL) {
        // разность dot_pos - temp_result дает индекс точки в строк
        int total_length = (dot_pos - temp_result) + 1 + display_precision; // + 1 - сама точка
        temp_result[total_length] = '\0'; // Обрезаем строку
    }

    strcpy(result, temp_result);
}