#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 80

int main() {
    char input[MAX_LENGTH + 1];
    int counts[256] = {0}; // всего 256 символов

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1; // обезопасили себя, родной
    }

    // вот тут считаем
    for (size_t i = 0; i < strlen(input); ++i) {
        unsigned char c = (unsigned char)input[i];
        counts[c]++;
    }

    for (int i = 0; i < 256; ++i) {
        if (counts[i] > 0) {
            printf("%c=%d\n", i, counts[i]);
        }
    }

    return 0;
}