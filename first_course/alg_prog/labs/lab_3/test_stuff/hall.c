#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 1000

void subtract_numbers(const char *num1, const char *num2, char *result);
void multiply_numbers(const char *num1, const char *num2, char *result);
void divide_numbers(char *s, char *ans);

// Функция для переворота строки
void reverse_string(char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

// Функция сравнения двух чисел по модулю
// Возвращает:
//  1, если abs(num1) > abs(num2)
// -1, если abs(num1) < abs(num2)
//  0, если abs(num1) == abs(num2)
int compare_absolute(const char *num1, const char *num2) {
    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    for (size_t i = 0; i < len1; i++) {
        if (num1[i] > num2[i]) return 1;
        if (num1[i] < num2[i]) return -1;
    }

    return 0;
}

// Функция для сложения двух чисел
void add_numbers(const char *num1, const char *num2, char *result) {
    char abs_num1[MAX_LENGTH + 1], abs_num2[MAX_LENGTH + 1];
    int is_negative1 = (num1[0] == '-');
    int is_negative2 = (num2[0] == '-');

    // Убираем знак, если он есть
    strcpy(abs_num1, is_negative1 ? num1 + 1 : num1);
    strcpy(abs_num2, is_negative2 ? num2 + 1 : num2);

    // Случай 1: оба числа положительные
    if (!is_negative1 && !is_negative2) {
        int carry = 0, sum = 0, i, j, k = 0;
        char temp[MAX_LENGTH + 1];
        reverse_string(abs_num1);
        reverse_string(abs_num2);

        i = 0, j = 0;
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
    else if (is_negative1 && is_negative2) {
        add_numbers(abs_num1, abs_num2, result);
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
    }
    // Случай 3: одно из чисел отрицательное
    else {
        int cmp = compare_absolute(abs_num1, abs_num2);
        if (cmp == 0) {
            strcpy(result, "0");
        } else if (cmp > 0) {
            // Если модуль первого числа больше
            int borrow = 0, diff = 0, i, j, k = 0;
            char temp[MAX_LENGTH + 1];
            reverse_string(abs_num1);
            reverse_string(abs_num2);

            i = 0, j = 0;
            while (i < strlen(abs_num1) || j < strlen(abs_num2)) {
                int digit1 = (i < strlen(abs_num1)) ? abs_num1[i++] - '0' : 0;
                int digit2 = (j < strlen(abs_num2)) ? abs_num2[j++] - '0' : 0;
                digit1 -= borrow;

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

            if (is_negative1) { // Первое число отрицательное
                memmove(temp + 1, temp, strlen(temp) + 1);
                temp[0] = '-';
            }

            strcpy(result, temp);
        } else {
            // Если модуль второго числа больше
            subtract_numbers(abs_num2, abs_num1, result);
            if (is_negative2) { // Второе число отрицательное
                memmove(result + 1, result, strlen(result) + 1);
                result[0] = '-';
            }
        }
    }
}

// Функция для вычитания двух чисел
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

        int borrow = 0, diff = 0, i, j, k = 0;
        char temp[MAX_LENGTH + 1];

        if (cmp > 0) {
            reverse_string(abs_num1);
            reverse_string(abs_num2);
            i = 0, j = 0;
            while (i < strlen(abs_num1) || j < strlen(abs_num2)) {
                int digit1 = (i < strlen(abs_num1)) ? abs_num1[i++] - '0' : 0;
                int digit2 = (j < strlen(abs_num2)) ? abs_num2[j++] - '0' : 0;
                digit1 -= borrow;

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

// Функция для умножения двух чисел
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
    while (precision < 10 && strcmp(remainder, "0") != 0) { // Ограничиваем итерации для дробной части
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
    int display_precision = 40; // Задаем количество знаков после запятой
    char *dot_pos = strchr(temp_result, '.');
    if (dot_pos != NULL) {
        int total_length = (dot_pos - temp_result) + 1 + display_precision;
        temp_result[total_length] = '\0'; // Обрезаем строку
    }

    strcpy(result, temp_result);
}

void power_numbers(char *base, char *exponent, char *result) {
    char temp[MAX_LENGTH] = "1";  // Промежуточный результат
    char current_exp[MAX_LENGTH];
    int is_negative = 0;

    // Проверяем знак степени
    if (exponent[0] == '-') {
        is_negative = 1;
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
        char one[MAX_LENGTH] = "1";
        divide_numbers(temp, result); // result = 1 / temp
    } else {
        strcpy(result, temp);
    }
}

// Функция для вычисления факториала числа
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

// Функция для вычисления суммы чисел от `from` до `to`
void sum_range(const char* s1, const char* s2, char* ans) {
    char current[MAX_LENGTH], target[MAX_LENGTH], step[MAX_LENGTH] = "1", temp_result[MAX_LENGTH];
    char temp1[MAX_LENGTH], temp2[MAX_LENGTH], temp_ans[MAX_LENGTH];

    if (s1[0] != '-' && s2[0] != '-') {
        // Оба числа положительные
        strcpy(current, s1);
        strcpy(target, s2);
        strcpy(ans, "0");

        while (compare_absolute(current, target) <= 0) {
            add_numbers(ans, current, temp_ans);
            strcpy(ans, temp_ans);

            add_numbers(current, step, temp_result);
            strcpy(current, temp_result);
        }
    } else if (s1[0] == '-' && s2[0] == '-') {
        // Оба числа отрицательные
        char mod_s1[MAX_LENGTH], mod_s2[MAX_LENGTH];

        // Убираем знаки "-"
        strcpy(mod_s1, s1 + 1);
        strcpy(mod_s2, s2 + 1);

        sum_range(mod_s2, mod_s1, ans); // Рекурсивный вызов с инверсией порядка

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

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    char num1[MAX_LENGTH], num2[MAX_LENGTH], result[MAX_LENGTH];
    int choice, power, from, to;

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