#include "huge_math.h"
#include <stdlib.h>
#include <string.h>

void sum_range(const char* s1, const char* s2, char* ans) {
    char current[MAX_LENGTH], target[MAX_LENGTH], step[MAX_LENGTH] = "1", temp_result[MAX_LENGTH];
    char temp_ans[MAX_LENGTH];

    if (s1[0] != '-' && s2[0] != '-') {
        // Оба числа положительные
        strcpy(current, s1);
        strcpy(target, s2);
        strcpy(ans, "0");

        while (compare_absolute(current, target) <= 0) {
            // Добавляем в ответ
            add_numbers(ans, current, temp_ans);
            strcpy(ans, temp_ans);

            // Увеличиваем current
            add_numbers(current, step, temp_result);
            strcpy(current, temp_result);
        }
    } else if (s1[0] == '-' && s2[0] == '-') {
        // Оба числа отрицательные
        char mod_s1[MAX_LENGTH], mod_s2[MAX_LENGTH];

        // Убираем знаки "-"
        strcpy(mod_s1, s1 + 1);
        strcpy(mod_s2, s2 + 1);

        sum_range(mod_s2, mod_s1, ans); // Рекурсивный вызов с инверсией порядка, так как модуль s2 меньше модуля s1

        // Добавляем знак "-" к результату
        char neg_ans[MAX_LENGTH];
        neg_ans[0] = '-';
        strcpy(neg_ans + 1, ans);
        strcpy(ans, neg_ans);

    } else if (s1[0] == '-' && s2[0] != '-') {
        // Диапазон от отрицательного до положительного
        char neg_one[MAX_LENGTH] = "-1", zero[MAX_LENGTH] = "0";
        char sum_neg[MAX_LENGTH], sum_pos[MAX_LENGTH];

        // Сумма отрицательных чисел
        sum_range(s1, neg_one, sum_neg);

        // Сумма положительных чисел
        sum_range(zero, s2, sum_pos);

        // Складываем две суммы
        add_numbers(sum_pos, sum_neg, ans);
    } else {
        // Некорректный диапазон: положительное начало и отрицательный конец
        strcpy(ans, "0");
    }
}
