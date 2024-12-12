#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

#define MAX_LENGTH 1000

void add_numbers(const char *num1, const char *num2, char *result);
void subtract_numbers(const char *num1, const char *num2, char *result);
void multiply_numbers(const char *num1, const char *num2, char *result);
void divide_numbers(char *num1, char *result);
void sum_range(const char* s1, const char* s2, char* ans);
void factorial_number(const char *num, char *result);
void power_numbers(char *base, char *exponent, char *result);

void reverse_string(char *str);
int compare_absolute(const char *num1, const char *num2);

#endif // MATH_OPERATIONS_H
