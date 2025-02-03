#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 33

typedef int bool;
#define true 1
#define false 0

void strip_comments(FILE *src, FILE *dst) {
    char ch, next;
    bool inside_string = false;
    bool inside_char = false;
    bool single_line_comment = false;
    bool multi_line_comment = false;
    bool is_escaped = false;

    while ((ch = fgetc(src)) != EOF) {
        if (inside_string) {
            fputc(ch, dst);
            if (ch == '"' && !is_escaped) {
                inside_string = false;
            }
            is_escaped = (ch == '\\') ? !is_escaped : false;
        } else if (inside_char) {
            fputc(ch, dst);
            if (ch == '\'' && !is_escaped) {
                inside_char = false;
            }
            is_escaped = (ch == '\\') ? !is_escaped : false;
        } else if (single_line_comment) {
            if (ch == '\\') {
                next = fgetc(src);
                if (next == '\n') {
                    continue; // Игнорируем перенос строки
                }
                if (next != EOF) {
                    ungetc(next, src);
                }
            } else if (ch == '\n') {
                single_line_comment = false;
                fputc(ch, dst);
            }
        } else if (multi_line_comment) {
            if (ch == '*') {
                next = fgetc(src);
                if (next == '/') {
                    multi_line_comment = false;
                } else if (next != EOF) {
                    ungetc(next, src);
                }
            }
        } else {
            if (ch == '"') {
                inside_string = true;
                fputc(ch, dst);
            } else if (ch == '\'') {
                inside_char = true;
                fputc(ch, dst);
            } else if (ch == '/' && (next = fgetc(src)) == '/') {
                single_line_comment = true;
            } else if (ch == '/' && next == '*') {
                multi_line_comment = true;
            } else {
                fputc(ch, dst);
                if (ch == '/' && next != EOF) {
                    ungetc(next, src);
                }
            }
        }
    }
}

void handle_file(const char *src_name, const char *dst_name) {
    FILE *src = fopen(src_name, "r");
    if (!src) {
        fprintf(stderr, "Error: Cannot open source file %s\n", src_name);
        return;
    }

    FILE *dst = fopen(dst_name, "w");
    if (!dst) {
        fclose(src);
        fprintf(stderr, "Error: Cannot create destination file %s\n", dst_name);
        return;
    }

    strip_comments(src, dst);

    fclose(src);
    fclose(dst);
}

int main() {
    FILE *proj_file = fopen("project.txt", "r");
    if (!proj_file) {
        fprintf(stderr, "Error: Cannot open project.txt\n");
        return 1;
    }

    int file_count;
    if (fscanf(proj_file, "%d", &file_count) != 1) {
        fprintf(stderr, "Error: Invalid project.txt format\n");
        fclose(proj_file);
        return 1;
    }

    char src_name[MAX_NAME_LEN];
    for (int i = 0; i < file_count; ++i) {
        if (fscanf(proj_file, "%s", src_name) != 1) {
            fprintf(stderr, "Error: Invalid file name in project.txt\n");
            break;
        }

        char dst_name[MAX_NAME_LEN];
        strncpy(dst_name, src_name, MAX_NAME_LEN);
        char *dot = strrchr(dst_name, '.');
        if (dot) {
            strcpy(dot, ".wc");
        } else {
            fprintf(stderr, "Error: Invalid file name format: %s\n", src_name);
            continue;
        }

        handle_file(src_name, dst_name);
    }

    fclose(proj_file);
    return 0;
}
