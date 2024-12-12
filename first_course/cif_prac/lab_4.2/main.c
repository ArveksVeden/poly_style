#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256

void process_file(const char *input_file, const char *output_file) {
    FILE *fi = fopen(input_file, "r");
    FILE *fo = fopen(output_file, "w");

    if (!fi) {
        fprintf(stderr, "Error: Cannot open input file %s\n", input_file);
        return;
    }
    if (!fo) {
        fprintf(stderr, "Error: Cannot open output file %s\n", output_file);
        fclose(fi);
        return;
    }

    int c, next;
    int in_string = 0;
    int in_char = 0;
    int in_comment = 0;

    while ((c = fgetc(fi)) != EOF) {
        if (in_comment) {
            if (c == '*' && (next = fgetc(fi)) == '/') {
                in_comment = 0;
            } else if (c == '\n' && next != EOF) {
                ungetc(next, fi);
            }
            continue;
        }

        if (in_string) {
            fputc(c, fo);
            if (c == '"' && (next = fgetc(fi)) != '\\') {
                in_string = 0;
                ungetc(next, fi);
            }
            continue;
        }

        if (in_char) {
            fputc(c, fo);
            if (c == '\'' && (next = fgetc(fi)) != '\\') {
                in_char = 0;
                ungetc(next, fi);
            }
            continue;
        }

        if (c == '"') {
            in_string = 1;
            fputc(c, fo);
            continue;
        }

        if (c == '\'') {
            in_char = 1;
            fputc(c, fo);
            continue;
        }

        if (c == '/' && (next = fgetc(fi)) == '*') {
            in_comment = 1;
            continue;
        }

        if (c == '/' && next == '/') {
            while ((c = fgetc(fi)) != EOF && c != '\n');
            if (c == '\n') {
                fputc(c, fo);
            }
            continue;
        }

        if (next != EOF) {
            ungetc(next, fi);
        }

        fputc(c, fo);
    }

    fclose(fi);
    fclose(fo);
}

int main() {
    FILE *project_file = fopen("project.txt", "r");
    if (!project_file) {
        fprintf(stderr, "Error: Cannot open project.txt\n");
        return EXIT_FAILURE;
    }

    int n;
    if (fscanf(project_file, "%d", &n) != 1) {
        fprintf(stderr, "Error: Cannot read the number of files\n");
        fclose(project_file);
        return EXIT_FAILURE;
    }

    char input_file[MAX_FILENAME_LEN];
    for (int i = 0; i < n; ++i) {
        if (fscanf(project_file, "%s", input_file) != 1) {
            fprintf(stderr, "Error: Cannot read file name from project.txt\n");
            fclose(project_file);
            return EXIT_FAILURE;
        }

        char output_file[MAX_FILENAME_LEN];
        snprintf(output_file, sizeof(output_file), "%s", input_file);
        size_t len = strlen(output_file);
        if (len > 2 && strcmp(&output_file[len - 2], ".c") == 0) {
            output_file[len - 2] = '\0'; // Убираем ".c"
        }
        strcat(output_file, ".wc");

        printf("Processing input file: %s\n", input_file);
        printf("Creating output file: %s\n", output_file);

        process_file(input_file, output_file);
    }

    fclose(project_file);
    return EXIT_SUCCESS;
}
