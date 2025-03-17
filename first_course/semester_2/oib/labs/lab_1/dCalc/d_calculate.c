#include <stdio.h>
#include <locale.h>

// функция для расширенного алгоритма Евклида
int gcd_extended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// функция для нахождения обратного элемента по модулю
int mod_inverse(int e, int phi) {
    int x, y;
    int gcd = gcd_extended(e, phi, &x, &y);
    if (gcd != 1) {
        return -1; // обратного элемента не существует
    } else {
        return (x % phi + phi) % phi; // обратный элемент
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int p = 587, q = 743;
    int n = p * q; // 436141
    int phi_n = (p - 1) * (q - 1); // 434812
    int e = 29;
    
    int d = mod_inverse(e, phi_n);
    if (d != -1) {
        printf("Обратный элемент d: %d\n", d);
    } else {
        printf("Обратного элемента не существует.\n");
    }
    
    return 0;
}
