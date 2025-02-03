#include "huge_math.h"
#include <string.h>

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