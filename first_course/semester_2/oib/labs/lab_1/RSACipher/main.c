#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// функция возведения в степень по модулю
long long simple_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    for (long long i = 0; i < exp; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// функция для шифрования строки
void encrypt(char *text, long long e, long long n) {
    printf("encrypted: ");
    for (int i = 0; i < strlen(text); i++) {
        long long encrypted_char = simple_pow((long long)text[i], e, n);
        printf("%lld ", encrypted_char);
    }
    printf("\n");
}

// функция для расшифрования массива чисел
void decrypt(long long *encrypted_text, int length, long long d, long long n) {
    printf("decrypted: ");
    for (int i = 0; i < length; i++) {
        char decrypted_char = (char)simple_pow(encrypted_text[i], d, n);
        printf("%c", decrypted_char);
    }
    printf("\n");
}

int main() {
    long long p = 587, q = 743;
    long long n = p * q; // 436141
    long long e = 29;
    long long d = 404825;
    char text[] = "RSA test";
    
    printf("original text: %s\n", text);
    
    // шифрование
    long long encrypted_text[strlen(text)];
    printf("encrypted: ");
    for (int i = 0; i < strlen(text); i++) {
        encrypted_text[i] = simple_pow((long long)text[i], e, n);
        printf("%lld ", encrypted_text[i]);
    }
    printf("\n");
    
    // расшифрование
    decrypt(encrypted_text, strlen(text), d, n);
    
    return 0;
}
