#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define ARRAY_SIZE 100000
#define DATA_FILE "data.txt"

void generate_data_file(const char *filename, size_t size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (size_t i = 0; i < size; ++i) {
        int random_number = rand() % 100001; // Число от 0 до 100000
        if (rand() % 2 == 0) {
            random_number = -random_number; // С вероятностью 50% делаем отрицательным
        }
        fprintf(file, "%d\n", random_number); // Запись числа в файл
    }

    fclose(file);
}

void load_data_from_file(const char *filename, int *array, size_t size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; ++i) {
        fscanf(file, "%d", &array[i]);
    }

    fclose(file);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Простая сортировка: Сортировка выбором
void selection_sort(int *array, size_t size, unsigned long *comparisons, unsigned long *moves) {
    *comparisons = 0;
    *moves = 0;

    for (size_t i = 0; i < size - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < size; ++j) {
            (*comparisons)++;
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&array[i], &array[min_index]);
            (*moves) += 3;
        }
    }
}

// Улучшенная сортировка 1: Быстрая сортировка
void quick_sort(int *array, int low, int high, unsigned long *comparisons, unsigned long *moves) {
    if (low < high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            (*comparisons)++;
            if (array[j] <= pivot) {
                i++;
                swap(&array[i], &array[j]);
                (*moves) += 3;
            }
        }
        swap(&array[i + 1], &array[high]);
        (*moves) += 3;

        int partition_index = i + 1;
        quick_sort(array, low, partition_index - 1, comparisons, moves);
        quick_sort(array, partition_index + 1, high, comparisons, moves);
    }
}

// Улучшенная сортировка 2: Сортировка Шелла
void shell_sort(int *array, size_t size, unsigned long *comparisons, unsigned long *moves) {
    *comparisons = 0;
    *moves = 0;

    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < size; ++i) {
            int temp = array[i];
            size_t j;
            for (j = i; j >= gap && (++(*comparisons), array[j - gap] > temp); j -= gap) {
                array[j] = array[j - gap];
                (*moves)++;
            }
            array[j] = temp;
            (*moves)++;
        }
    }
}

void print_statistics(const char *sort_name, unsigned long comparisons, unsigned long moves, double time) {
    printf("%s:\n", sort_name);
    printf("Сравнения: %lu, Перемещения: %lu, Время: %.2f секунд\n\n", comparisons, moves, time);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int array[ARRAY_SIZE];
    unsigned long comparisons, moves;
    clock_t start, end;
    int choice;

    do {
        printf("Сегодня в меню:\n");
        printf("1. Генерация файла\n");
        printf("2. Сортировка выбором\n");
        printf("3. Быстрая сортировка\n");
        printf("4. Сортировка Шелла\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generate_data_file(DATA_FILE, ARRAY_SIZE);
                printf("Файл с данными успешно сгенерирован.\n\n");
                break;

            case 2: {
                load_data_from_file(DATA_FILE, array, ARRAY_SIZE);
                start = clock();
                selection_sort(array, ARRAY_SIZE, &comparisons, &moves);
                end = clock();
                print_statistics("Сортировка выбором", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                break;
            }

            case 3: {
                load_data_from_file(DATA_FILE, array, ARRAY_SIZE);
                comparisons = moves = 0;
                start = clock();
                quick_sort(array, 0, ARRAY_SIZE - 1, &comparisons, &moves);
                end = clock();
                print_statistics("Быстрая сортировка", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                break;
            }

            case 4: {
                load_data_from_file(DATA_FILE, array, ARRAY_SIZE);
                comparisons = moves = 0;
                start = clock();
                shell_sort(array, ARRAY_SIZE, &comparisons, &moves);
                end = clock();
                print_statistics("Сортировка Шелла", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                break;
            }

            case 0:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n\n");
        }
    } while (choice != 0);

    return 0;
}
