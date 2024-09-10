#include <stdio.h>

// Функция для демонстрации работы с функциями
// Функция возвращает сумму двух чисел
int sum(int a, int b) {
    return a + b;
}

int main() {
    // Базовые типы данных
    int x = 5;    // Целое число
    float y = 3.14; // Число с плавающей точкой
    char ch = 'A';  // Символ

    // Ввод и вывод данных
    printf("Введите целое число: ");
    scanf("%d", &x);
    printf("Вы ввели число: %d\n", x);

    // Условный оператор if
    if (x > 0) {
        printf("Число положительное\n");
    } else if (x < 0) {
        printf("Число отрицательное\n");
    } else {
        printf("Число равно нулю\n");
    }

    // Оператор switch
    printf("Введите символ: ");
    scanf(" %c", &ch); // Пробел перед %c необходим для корректного чтения символа
    switch (ch) {
        case 'A':
            printf("Вы ввели 'A'\n");
            break;
        case 'B':
            printf("Вы ввели 'B'\n");
            break;
        default:
            printf("Вы ввели другой символ\n");
            break;
    }

    // Цикл for
    printf("Цикл for (вывод чисел от 1 до 5):\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // Цикл while
    printf("Цикл while (пока x > 0):\n");
    while (x > 0) {
        printf("x = %d\n", x);
        x--;  // Уменьшаем x на 1
    }

    // Цикл do-while
    printf("Цикл do-while (однократное выполнение при x = 0):\n");
    do {
        printf("Это будет выполнено хотя бы один раз\n");
    } while (x > 0);

    // Массивы
    int arr[5] = {1, 2, 3, 4, 5};  // Объявление и инициализация массива
    printf("Массив: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Работа с функцией
    int a = 10, b = 20;
    int result = sum(a, b);  // Вызов функции для суммы
    printf("Сумма %d и %d равна %d\n", a, b, result);

    return 0;  // Завершение программы
}
