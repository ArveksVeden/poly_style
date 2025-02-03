#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define ARRAY_SIZE 100000
#define DATA_FILE "data.txt"
#define OUTPUT_FILE "sorted_data.txt"

// Генерация файла с случайными числами
void generate_data_file(char *filename, size_t size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    // RAND_MAX = 32767
    srand(time(NULL));
    for (size_t i = 0; i < size; ++i) {
        int random_number = rand() % 100000;
        if (rand() % 2 == 0) {
            random_number = -random_number;
        }
        fprintf(file, "%d\n", random_number);
    }

    fclose(file);
}

// Загрузка данных из файла
void load_data_from_file(char *filename, int *array, size_t size) {
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

// Сохранение отсортированного массива в файл
void save_sorted_to_file(char *filename, int *array, size_t size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка создания файла");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; ++i) {
        fprintf(file, "%d\n", array[i]);
    }

    fclose(file);
}

// Обмен элементов
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Сортировка выбором
// На каждом шаге ищет минимальный элемент в неотсортированной части массива и ставит его в начало среза.
/*
    временная сложность сортировки выбором:
    лучшая:  O(n^2) - Даже если массив уже отсортирован, сортировка выбором выполняет те же операции: 
    необходимо пройтись по массиву, чтобы найти минимум для каждой итерации.

    средняя: O(n^2) - В среднем случае алгоритм будет выполнять примерно столько же сравнений, как и в худшем. 
    Перемещения элементов здесь почти не влияют, так как их число ограничено O(n).

    худшая:  O(n^2) - Если массив отсортирован в обратном порядке, 
    алгоритм всё равно должен пройти через n2n2 сравнений и nn перемещений.
*/
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

// Быстрая сортировка
/*
    временная сложность быстрой сортировки:
    лучшая:  O(n * log(n)) - Происходит, если массив делится на две равные или почти равные части на каждом уровне рекурсии.
    В каждом уровне деления выполняется O(n) сравнений (поиск опорного и разделение массива), а глубина рекурсии будет O(log⁡n).
    
    средняя: O(n * log(n)) - При случайном выборе опорного элемента массив чаще всего будет делиться на примерно равные части.
    худшая:  O(n^2) - Происходит, если массив делится неравномерно, например, когда опорный элемент 
    всегда оказывается минимальным или максимальным (например, при выборе первого элемента в уже отсортированном массиве).
*/
void quick_sort(int *array, int low, int high, unsigned long *comparisons, unsigned long *moves) {
    // Если левая граница не меньше правой (low >= high), значит, массив из одного или нуля элементов, и сортировать его не нужно.
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

// Сортировка Шелла
/*
    временная сложность сортировки вставками:
    сортировка вставками: Сравнивает каждый элемент с предыдущими и вставляет его на нужное место.
    лучшая:  O(n) - Если массив почти отсортирован, сортировка вставками  будет очень эффективной.
    средняя: O(n^2) - Элементы перемешаны случайным образом. Каждый элемент вставляется на соответствующее место.
    худшая:  O(n^2) - Массив отсортирован в обратном порядке. Каждый элемент перемещается через весь массив.
*/
/*
    // Использует шаг (gap) для сравнения элементов на большом расстоянии, постепенно уменьшая gap до 1.
    временная сложность сортировки Шелла:
    лучшая:  O(n log n) - Массив частично упорядочен (например, группы элементов уже отсортированы).
    средняя: O(n log n) - Элементы распределены случайно.
    худшая:  O(n^2) - Массив отсортирован в обратном порядке и используется неэффективная последовательность шагов.
*/
void shell_sort(int *array, size_t size, unsigned long *comparisons, unsigned long *moves) {
    *comparisons = 0;
    *moves = 0;

    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < size; ++i) {
            int current = array[i];
            size_t j = i;

            while (j >= gap && array[j - gap] > current) {
                (*comparisons)++;
                array[j] = array[j - gap];
                j -= gap;
                (*moves)++;
            }

            array[j] = current;
            (*moves)++;
        }
    }
}

// Вывод статистики
void print_statistics(char *sort_name, unsigned long comparisons, unsigned long moves, double time) {
    printf("%s:\n", sort_name);
    printf("Сравнения: %lu, Перемещения: %lu, Время: %.2f секунд\n\n", comparisons, moves, time);
}

// Главная функция
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
                save_sorted_to_file(OUTPUT_FILE, array, ARRAY_SIZE);
                print_statistics("Сортировка выбором", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                printf("Результат сохранён в %s\n\n", OUTPUT_FILE);
                break;
            }

            case 3: {
                load_data_from_file(DATA_FILE, array, ARRAY_SIZE);
                comparisons = moves = 0;
                start = clock();
                quick_sort(array, 0, ARRAY_SIZE - 1, &comparisons, &moves);
                end = clock();
                save_sorted_to_file(OUTPUT_FILE, array, ARRAY_SIZE);
                print_statistics("Быстрая сортировка", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                printf("Результат сохранён в %s\n\n", OUTPUT_FILE);
                break;
            }

            case 4: {
                load_data_from_file(DATA_FILE, array, ARRAY_SIZE);
                comparisons = moves = 0;
                start = clock();
                shell_sort(array, ARRAY_SIZE, &comparisons, &moves);
                end = clock();
                save_sorted_to_file(OUTPUT_FILE, array, ARRAY_SIZE);
                print_statistics("Сортировка Шелла", comparisons, moves, (double)(end - start) / CLOCKS_PER_SEC);
                printf("Результат сохранён в %s\n\n", OUTPUT_FILE);
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
