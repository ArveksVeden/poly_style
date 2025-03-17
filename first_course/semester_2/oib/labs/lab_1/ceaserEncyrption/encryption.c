#include <stdio.h>
#include <string.h>
#include <locale.h>

void ceaserCipher(char *text, int shift)
{
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'a' && ch <= 'z') {
            text[i] = 'a' + (ch - 'a' + shift) % 26;
        } else if (ch >= 'A' && ch <= 'Z') {
            text[i] = 'A' + (ch - 'A' + shift) % 26;
        }
    }
}

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    char text[100];
    int shift = 0;

    printf("введите строку: ");
    fgets(text, sizeof(text) / sizeof(text[0]), stdin);
    text[strcspn(text, "\n")] = 0; // удаляем символ новой строки
    
    printf("введите сдвиг: ");
    scanf("%d", &shift);

    ceaserCipher(text, shift);
    printf("результат шифрования: %s\n", text);

    return 0;
}