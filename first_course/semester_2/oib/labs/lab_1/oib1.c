#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#define KEY_SIZE 8
#define k 7
const long long Ng = 40003;
const long long Nc = 6;
const long long F3 = 5;
const long long B = 3042006;
/* алгоритм шифрования цезаря */
void cesar(char* name)
{
	int flag = 0;
	for (int i = 0; i < strlen(name); i++) {
		for (char j = 'А'; j <= 'Я'; j++) {
			if (name[i] == j) {
				if(name[i] == 'Ё')name[i] = 'К';
				else if (name[i] < 'Ж' && name[i]>'А') {
					if (name[i] == 'Б')name[i] = 'Ё';
					else name[i] = name[i] + k - 1;
				}
				else name[i] = name[i] + k;
				if (name[i] > 'Я' && name[i] != 'Ё') name[i] = 'А' + (name[i] - 'Я' - 1);
				flag = 1;
				break;
			}
		}
		if (flag == 1){
			flag = 0; 
			continue;
		}
		for (char j = 'а'; j <= 'я'; j++) {
			if (name[i] == j) {
				if (name[i] < 'ж' && name[i]>'а') {
					if (name[i] == 'б')name[i] = 'ё';
					else name[i] = name[i] + k - 1;
				}
				else if (name[i] == 'ё')name[i] = 'к';
				else name[i] = name[i] + k;
				if (name[i] > 'я' && name[i] != 'ё') name[i] = 'а' + (name[i] - 'я' - 1);
				break;
			}
		}
	}
}

/* алгоритм евклида - поиск НОД */
long long euclid(long long num1, long long num2) {
	while (num1 != 0 && num2 != 0) {
		printf("num1 = %lli, num2 = %lli\n", num1, num2);
		if (num1 > num2) {
			printf("%lli %% %lli = ", num1, num2);
			num1 %= num2; printf("%lli\n", num1);
		}
		else {
			printf("%lli %% %lli = ", num2, num1);
			num2 %= num1;
			printf("%lli\n", num2);
		}
	}
	if (num1 > 0)
    {
        return num1;
    } else {
        return num2;
    }
}

/* быстрое возведение в степень по модулю */
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {  // если степень нечётная
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // возводим base в квадрат
        exp /= 2;
    }
    return result;
}

/* функция проверки числа N на простоту с помощью теста Миллера-Рабина */
int miller(int N) {
    if (N == 2 || N == 3)  
        return 1;   // 2 и 3 - простые числа
    if (N < 2 || N % 2 == 0)  
        return 0;   // числа < 2 и чётные числа > 2 не являются простыми

    int stime;
    long ltime;
    
    unsigned long long s = 0, x = 0, t = N - 1, a = 0, n;
    
    // инициализация генератора случайных чисел
    ltime = time(NULL); // кол-во секунд с 1970 года 1-го января
    stime = (unsigned int)ltime / 2;
    srand(stime); // инициализация генератора

    // разложение N-1 в 2^s * t, где t - нечётное
    while (t % 2 == 0) {
        t /= 2;
        s += 1;
    }
    n = t; // запоминаем значение t

    // запускаем тест 50 раз для разных случайных чисел a
    for (int i = 50; i > 0; i--) {
        t = n;

        // генерируем случайное число a в диапазоне [2, N-2]
        do {
            a = rand() % (N - 2);
        } while (a < 2);

        // вычисляем x = a^t % N
        x = a % N;
        while (t > 1) {
            x = (x * a) % N;
            t--;
        }

        // если x = 1 или x = N - 1, переходим к следующей итерации
        if (x == 1 || x == N - 1)
        {
            continue;
        }
        // повторяем s-1 раз: проверяем x^(2^j) % N
        for (int j = 1; j < s; j++) 
        {
            x = powl(x, 2);
            x %= N;
            
            if (x == 1)
            {
                return 0;   // N составное, так как x^2 ? 1 (mod N)
            }
            
            if (x == N - 1)
            {
                break;  // выходим из цикла, если нашли -1
            }
        }

        // если после всех проверок x ? N-1, число N составное
        if (x != N - 1)
        {
            return 0;
        }
    }

    return 1;  // eсли прошли все тесты, число вероятно простое
}

/* пункт 2.1 - вычисление k = 7 */
void point_1()
{
    long long num = 0, res = 0;
    num = Ng + Nc; // основание

    res = (mod_pow(num, 11, 11) + F3) % 11; // (num^11 + F3) % 11
    
    printf("[ПУНКТ #1:]\n");
    printf("результаты вычисления: %d\n", res);
}

/* пункт 2.2 - шифр цезаря */
void point_2()
{
    char text[256] = "ВеденеевАртёмСергеевич";

    printf("[ПУНКТ #2]\n");
    printf("исходный текст: %s\n", text);
    cesar(text);
    printf("текст после шифрования: %s\n", text);
}

/* пункт 2.3 - вычисление A и НОД(A, B) */
void point_3()
{
    long long A = powl((Ng * (8 + (Nc % 7))), 2);
    printf("[ПУНКТ #3:]\n");
    printf("вычисление A: %lli\n", A);

    // вычисление B и GCD
	long long B1 = (B % 95) + 900;
	long long B2 = ((B + 50) % 97) + 700;
	long long B3 = ((B + 20) % 101) + 1500;
	long long B4 = ((B - 40) % 103) + 2500;
	printf("НОД(A, B(mod 95)+900):\n");
	printf("НОД(A, B(mod 95)+900) = %lli\n", euclid(A, B1));
	printf("НОД(A, (B+50)(mod 97)+700):\n");
	printf("НОД(A, (B+50)(mod 97)+700) = %lli\n", euclid(A, B2));
	printf("НОД(A, (B+20)(mod 101)+1500, (B-40)(mod 103)+2500):\n");
	B3 = euclid(A, B3);
	printf("НОД(A, (B+20)(mod 101)+1500, (B-40)(mod 103)+2500) = %lli\n\n\n", euclid(B3, B4));
}

/* пункт 2.4 - проверка числа на простоту методом миллера */
void point_4()
{
    int N = 16784, N1 = 601, x = 0;
	x = miller(N);
	if (x == 0)
    {
        printf("число %d составное\n", N);
    } else {
        printf("число %d простое\n", N);
    }
	x = miller(N1);
	if (x == 0)
    {
        printf("число %d составное\n", N1);
    } else {
        printf("число %d простое\n", N1);
    }
}

/* пункт 2.5 - генерация открытого и закрытого ключей RSA с использованием алгоритма Евклида */
void point_5()
{
    long long p = 587, q = 743;
    long long n = 0, f = 0, e = 0, d = 0;
    n = p * q;
    printf("n = %lli\n", n);
    f = (p - 1) * (q - 1);
    printf("fi = %lli\n", f);
    
    // условие на e: 1 < e < ?(n)
    // gcd(e,?(n)) = 1, то есть ee должно быть взаимно простым с функцией Эйлера ?(n).
    for (e = 2; e < p; e++) 
    {
		if (euclid(e, p - 1) == euclid(e, q - 1) && euclid(e, p - 1) == 1) 
        {
			break;
		}
	}
	printf("e = %llu\n", e);

    // условие на d: d * e ? 1(mod?(n)): (e * d) % f = 1.
    for (d = f/e;;d++) 
    {
		if (((e * d) % f) == 1)
        {
            break;
        }
	}
    printf("d = %llu\n", d);
}

/* пункт 2.6 - реализация RSA-шифрования в ASCII */
void point_6()
{
    long long p = 587, q = 743;
    long long n = 436141, f = 434812;
    long long e = 3; // открытая экспонента - публичный ключ
    long long d = 289875; // закрытая экспонента - приватный ключ

    char text[256] = "RSA text"; // исходный текст
    char deciphered[256]; // расшифрованный текст
    long long cipher_num[256]; // массив чисел, представляющих зашифрованные символы
    long long t = 0;
    int i = 0, j = 0;

    printf("исходный текст: %s\n", text);
    // шифрование текста
    // преобразование каждого символа в число для cipher_num
    for (i = 0; text[i] != '\0'; i++) {
		if (text[i] != '\0')
        {
            // выводим символ в ASCII коде
            printf("%c = %d\n", text[i], text[i]);
        }

		t = text[i] % n;
        
        // возведение в степень e по модулю n через алг. быстрого в. в степ.
		for (long long b = 2; b <= e; b++) {
			t = (t * text[i]) % n; // % n - помогает избежать переполнение
		}

		cipher_num[i] = t;
		printf("x^e(mod n) для %c = %lli\n", text[i], t);
	}

    cipher_num[i] = 0;

    // расшифрование текста
    for (j = 0; cipher_num[j] != 0; j++) {
		t = cipher_num[j] % n;
        // t = y**d (mod n) -- обратная операция к x^e \mod n (шифрование).
		for (long long b = 2; b <= d; b++) {
			t = (t * cipher_num[j]) % n;
		}
		deciphered[j] = t; // исходный x
		printf("y^d(mod n) для %c = %lli\n", text[j], t);
	}
	deciphered[j] = '\0';
	printf("Расшифрованный текст: %s\n", deciphered);
}

/* пункт 2.7 - цифровая подпись и проверка с помощью RSA */
void point_7()
{
    char text[256] = "RSA text"; // исходный текст
    long long n = 436141, f = 434812;
    long long e = 3; // открытая экспонента - публичный ключ
    long long d = 289875; // закрытая экспонента - приватный ключ
    long long t = 0, i = 0;

    long long sign[1000];
    // создание цифровой подписи
	printf("цифровая подпись:\n");
	for (i = 0; text[i] != '\0'; i++) 
    {
		t = text[i] % n;
        // t = (text_x[i])^d mod n - реализация подписи
		for (long long b = 2; b <= d; b++) 
        {
			t = (t * text[i]) % n;
		}
		sign[i] = t;
		printf("Для %c = %d s = %lli\n", text[i], text[i], t);
	}
	sign[i] = 0;
    // проверка подписи
	printf("обратное преобразование:\n");
	for (i = 0; sign[i] != 0; i++) 
    {
		t = sign[i] % n; // предотвращаем переполнение
        // x = s^e mod n - восстановление оригинального сообщения
		for (long long b = 2; b <= e; b++) 
        {
			t = (t * sign[i]) % n;
		}
		text[i] = t; // теперь содержит исходный символ, если подпись верна.
		printf("s = %lli, x = %d\n", sign[i], text[i]);
	}
	printf("после обратного преобразования: %s\n", text);
}

/* пункт 2.8 - Моделирование установления сеансового ключа по схеме Диффи-Хеллмана. */
void point_8()
{
    long long a = 5; // генератор, общий для всех участников
    long long y = 0; // секретное число второго участника
    long long A_key, B_key; // вычисленный секретные ключи участников A и B
    long long xy;
    long long mod_xy; // a^(xy) (mod n)
    long long mod_x_y1, mod_y_x1, mod_x_y2, mod_y_x2; // промежуточные вычисления для проверки свойств возведения в степень.
    long long x = 0; // секретное число первого участника

    char text[256] = "RSA text"; // исходный текст
    long long n = 436141, f = 434812;
    long long i = 0, A = 0, B = 0;

	x = rand() % f;
	printf("x = %d\n", x);

    // A = a^x (mod n)
	A = a % n;
	for (i = 2; i <= x; i++) {
		A = (A * a) % n;
	}

	y = rand() % f;
	printf("y = %lli\n", y);

    // B = a^y (mod n)
	B = a % n;
	for (i = 2; i <= y; i++) {
		B = (B * a) % n;
	}

	printf("A = a^x(mod n) = %lli\n", A);
	printf("B = a^y(mod n) = %lli\n", B);

    // вычисление общего ключа: Akey? = B^x (mod n)
	A_key = B % n;
	for (i = 2; i <= x; i++) {
		A_key = (B * A_key) % n;
	}

    // B_key = (A^y mod n)
	B_key = A % n;
	for (i = 2; i <= y; i++) {
		B_key = (A * B_key) % n;
	}
	printf("B^x(mod n) = %lli\n", A_key);
	printf("A^y(mod n) = %lli\n", B_key);

	if (A_key == B_key)
    {
        printf("Ключи равны\n");
    }

    // проверка свойств возведения в степень по модулю
    // a^(xy) (mod n) = (a^x)^y (mod n) = (a^y)^x (mod n)
	xy = x * y;
    // вычисление (a^x)^y mod n = mod_x_y2
	mod_xy = a % n;
	for (i = 2; i <= xy; i++) {
		mod_xy = (mod_xy * a) % n;
	}
	mod_x_y1 = a % n;
	for (i = 2; i <= x; i++) {
		mod_x_y1 = (mod_x_y1 * a) % n;
	}
	mod_x_y2 = mod_x_y1 % n;
	for (i = 2; i <= y; i++) {
		mod_x_y2 = (mod_x_y2 * mod_x_y1) % n;
	}
    // вычисление (a^y)^x mod n = mod_y_x2
	mod_y_x1 = a % n;
	for (i = 2; i <= x; i++) {
		mod_y_x1 = (mod_y_x1 * a) % n;
	}
	mod_y_x2 = mod_y_x1 % n;
	for (i = 2; i <= y; i++) {
		mod_y_x2 = (mod_y_x2 * mod_y_x1) % n;
	}
	printf("axy(mod n) = %lli\n(ax)y(mod n) = %lli\n(ay)x(mod n) = %lli\n\n\n", mod_xy,mod_x_y2,mod_y_x2);
}


/* пункт 2.9 - Реализация утилиты шифрования и дешифрования с помощью алгоритма Меркля-Хеллмана. */
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

/* пункт 2.9 - 2.9	Реализация утилиты шифрования и дешифрования с помощью алгоритма Меркля-Хеллмана. */
void point_9()
{
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
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    //point_1();
    //point_2();
    //point_3();
    //point_4();
    //point_5();
    //point_6();
    //point_7();
    //point_8();
    point_9();

    return 0;
}