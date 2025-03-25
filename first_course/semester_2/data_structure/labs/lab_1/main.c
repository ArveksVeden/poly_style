#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 300
#define INITIAL_BUFFER_SIZE 200

// функция для чтения слов из файла с динамическим выделением памяти
int read_words(FILE* file, char*** words) {
    size_t count = 0;
    *words = malloc(sizeof(char*) * MAX_WORDS); // выделяет память под массив из MAX_WORDS указателей на строки.

    char buffer[INITIAL_BUFFER_SIZE];
    while (fgets(buffer, INITIAL_BUFFER_SIZE, file) && count < MAX_WORDS) {
        size_t len = strlen(buffer);
        // убираем лишние пробельные символы
        while (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n' || buffer[len - 1] == ' ')) {
            buffer[--len] = '\0';
        }
        (*words)[count] = malloc(len + 1); // выделяем память под строку, учитывая \0 - len + 1
        strcpy((*words)[count], buffer); // копирование строки в выделенную память
        count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");
    FILE* words_file = fopen(argv[2], "r");
    FILE* replace_file = fopen(argv[3], "r");
    FILE* output_file = fopen(argv[4], "w");

    // указатель на указатель -> двумерный массив
    char** words_to_replace;
    char** replacement_words;
    int replace_count = read_words(words_file, &words_to_replace); // &words_to_replace - char***
    int replacement_count = read_words(replace_file, &replacement_words);

    int ch;
    char* buffer = malloc(INITIAL_BUFFER_SIZE); // считываемое слово
    size_t buf_size = INITIAL_BUFFER_SIZE;
    size_t index = 0; // текущая позиция с считываемом слове

    // считывание каждого символа до конца файла
    while ((ch = fgetc(input_file)) != EOF) {
        // построение слова из символов
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '-' || ch == '\'') {
            // 
            if (index >= buf_size - 1) {
                buf_size *= 2;
                buffer = realloc(buffer, buf_size);
                if (buffer == NULL) {
                    perror("memory allocation failed");
                    return EXIT_FAILURE;
                }
            }
            buffer[index++] = ch;
            buffer[index] = '\0';
        // окончание слова
        } else {
            if (index > 0) { // проверяем, есть ли слово в буфере
                int replaced = 0;
                for (int i = 0; i < replace_count; i++) {
                    if (strcmp(buffer, words_to_replace[i]) == 0) {
                        fprintf(output_file, "%s", replacement_words[i]);
                        replaced = 1;
                        break;
                    }
                }
                if (!replaced) {
                    fprintf(output_file, "%s", buffer);
                }
                index = 0;
            }
            fputc(ch, output_file);
        }
    }

    free(buffer);
    for (int i = 0; i < replace_count; i++) {
        free(words_to_replace[i]);
        free(replacement_words[i]);
    }
    free(words_to_replace);
    free(replacement_words);

    fclose(input_file);
    fclose(words_file);
    fclose(replace_file);
    fclose(output_file);

    printf("[the operation was successful]\n");
    return EXIT_SUCCESS;
}
