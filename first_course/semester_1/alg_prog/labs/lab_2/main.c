#include <stdio.h>
#include <math.h>
#define MACHINE_EPSILON pow(2, -52)

// Функция для вычисления суммы ряда Тейлора для функции синуса
double taylor_series_sum(double x, int terms, double epsilon) {
    int count = 0;                // Счетчик для отслеживания количества членов ряда
    double term_value = x;        // Первое слагаемое ряда (x^1 / 1!)
    double result = term_value;   // Инициализация результата с первым членом ряда

    while (1) {
        count++;  // Увеличиваем счетчик на 1 для следующего члена ряда

        // Вычисление следующего члена ряда с использованием рекурсивной формулы
        // term_value = (-1)^(n) * x^(2n+1) / (2n+1)!
        term_value *= (-1) * x * x / ((2 * count) * (2 * count + 1));
        result += term_value;  // Добавляем текущее слагаемое к результату

        // Вывод результата после указанного количества членов
        if (count == terms) {
            printf("Сумма ряда после %d членов: %.15lf\n", terms, result);
        }

        // Если абсолютное значение текущего члена меньше epsilon, то можно остановить вычисления
        if (fabs(term_value) < epsilon) {
            printf("Сумма ряда с максимально возможной точностью: %.15lf\n, %d", result, count);
            break;
        }
    }

    return result;
}

int main(void) {
    double x_value;
    int term_count;

    printf("Введите количество членов и значение x: ");
    scanf("%d %lf", &term_count, &x_value);

    double epsilon = MACHINE_EPSILON;
    taylor_series_sum(x_value, term_count, epsilon);

    return 0;
}
