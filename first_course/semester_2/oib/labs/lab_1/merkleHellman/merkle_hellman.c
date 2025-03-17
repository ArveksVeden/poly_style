#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY_SIZE 8 // размер ключа

// функция для вычисления наибольшего общего делителя (НОД)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// функция для вычисления обратного элемента по модулю (расширенный алгоритм Евклида)
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // eсли обратного элемента не существует
}

// генерация закрытого ключа (сверхвозрастающая последовательность, модуль и множитель)
void generate_private_key(int w[KEY_SIZE], int *n, int *e) {
    srand(time(NULL)); // инициализация генератора случайных чисел
    int sum = 0;
    printf("Генерация закрытого ключа по формуле:\n");
    printf("w[i] = sum(w[0]...w[i-1]) + случайное_значение\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        w[i] = sum + (rand() % 10 + 1); // создаём сверхвозрастающую последовательность
        sum += w[i];
        printf("w[%d] = %d\n", i, w[i]);
    }
    *n = sum + (rand() % 10 + 1); // Выбираем модуль n
    printf("n = sum(w) + случайное_значение = %d\n", *n);
    
    do {
        *e = rand() % (*n - 1) + 1; // выбираем экспоненту e
    } while (gcd(*e, *n) != 1); // проверяем, чтобы e и n были взаимно простыми
    
    printf("e = %d (НОД с n = %d)\n", *e, gcd(*e, *n));
}

// генерация открытого ключа (преобразование закрытого ключа)
void generate_public_key(int w[KEY_SIZE], int n, int e, int beta[KEY_SIZE]) {
    printf("Генерация открытого ключа по формуле:\n");
    printf("beta[i] = (w[i] * e) mod n\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        beta[i] = (w[i] * e) % n; // преобразуем элементы закрытого ключа
        printf("beta[%d] = %d\n", i, beta[i]);
    }
}

// шифрование сообщения
int encrypt(int message[KEY_SIZE], int beta[KEY_SIZE]) {
    int c = 0;
    printf("Шифрование по формуле:\n");
    printf("c = sum(message[i] * beta[i])\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("message[%d] = %d, beta[%d] = %d, произведение = %d\n", i, message[i], i, beta[i], message[i] * beta[i]);
        c += message[i] * beta[i];
    }
    return c;
}

// дешифрование сообщения
void decrypt(int c, int w[KEY_SIZE], int n, int e) {
    int d = mod_inverse(e, n); // вычисляем d — обратный элемент к e по модулю n
    printf("дешифрование по формуле:\n");
    printf("s = (c * d) mod n\n");
    int s = (c * d) % n;
    printf("s = %d\n", s);
    
    int decrypted[KEY_SIZE]; // массив для расшифрованного сообщения
    printf("поиск исходного сообщения, вычитая w[i] из s\n");
    for (int i = KEY_SIZE - 1; i >= 0; i--) {
        if (s >= w[i]) {
            decrypted[i] = 1;
            s -= w[i];
        } else {
            decrypted[i] = 0;
        }
        printf("s = %d, w[%d] = %d, decrypted[%d] = %d\n", s, i, w[i], i, decrypted[i]);
    }
    
    // вывод расшифрованного сообщения
    printf("расшифрованное сообщение: ");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%d", decrypted[i]);
    }
    printf("\n");
}

int main(void) {
    int w[KEY_SIZE], n, e;
    generate_private_key(w, &n, &e);
    
    int beta[KEY_SIZE];
    generate_public_key(w, n, e, beta);
    
    int message[KEY_SIZE] = {1, 0, 1, 1, 0, 0, 1, 0}; // исходное сообщение
    printf("исходное сообщение: ");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%d", message[i]);
    }
    printf("\n");
    
    int c = encrypt(message, beta);
    printf("зашифрованное сообщение: %d\n", c);
    
    decrypt(c, w, n, e);
    
    return 0;
}
