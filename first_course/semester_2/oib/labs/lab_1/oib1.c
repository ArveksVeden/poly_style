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
/* �������� ���������� ������ */
void cesar(char* name)
{
	int flag = 0;
	for (int i = 0; i < strlen(name); i++) {
		for (char j = '�'; j <= '�'; j++) {
			if (name[i] == j) {
				if(name[i] == '�')name[i] = '�';
				else if (name[i] < '�' && name[i]>'�') {
					if (name[i] == '�')name[i] = '�';
					else name[i] = name[i] + k - 1;
				}
				else name[i] = name[i] + k;
				if (name[i] > '�' && name[i] != '�') name[i] = '�' + (name[i] - '�' - 1);
				flag = 1;
				break;
			}
		}
		if (flag == 1){
			flag = 0; 
			continue;
		}
		for (char j = '�'; j <= '�'; j++) {
			if (name[i] == j) {
				if (name[i] < '�' && name[i]>'�') {
					if (name[i] == '�')name[i] = '�';
					else name[i] = name[i] + k - 1;
				}
				else if (name[i] == '�')name[i] = '�';
				else name[i] = name[i] + k;
				if (name[i] > '�' && name[i] != '�') name[i] = '�' + (name[i] - '�' - 1);
				break;
			}
		}
	}
}

/* �������� ������� - ����� ��� */
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

/* ������� ���������� � ������� �� ������ */
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {  // ���� ������� ��������
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // �������� base � �������
        exp /= 2;
    }
    return result;
}

/* ������� �������� ����� N �� �������� � ������� ����� �������-������ */
int miller(int N) {
    if (N == 2 || N == 3)  
        return 1;   // 2 � 3 - ������� �����
    if (N < 2 || N % 2 == 0)  
        return 0;   // ����� < 2 � ������ ����� > 2 �� �������� ��������

    int stime;
    long ltime;
    
    unsigned long long s = 0, x = 0, t = N - 1, a = 0, n;
    
    // ������������� ���������� ��������� �����
    ltime = time(NULL); // ���-�� ������ � 1970 ���� 1-�� ������
    stime = (unsigned int)ltime / 2;
    srand(stime); // ������������� ����������

    // ���������� N-1 � 2^s * t, ��� t - ��������
    while (t % 2 == 0) {
        t /= 2;
        s += 1;
    }
    n = t; // ���������� �������� t

    // ��������� ���� 50 ��� ��� ������ ��������� ����� a
    for (int i = 50; i > 0; i--) {
        t = n;

        // ���������� ��������� ����� a � ��������� [2, N-2]
        do {
            a = rand() % (N - 2);
        } while (a < 2);

        // ��������� x = a^t % N
        x = a % N;
        while (t > 1) {
            x = (x * a) % N;
            t--;
        }

        // ���� x = 1 ��� x = N - 1, ��������� � ��������� ��������
        if (x == 1 || x == N - 1)
        {
            continue;
        }
        // ��������� s-1 ���: ��������� x^(2^j) % N
        for (int j = 1; j < s; j++) 
        {
            x = powl(x, 2);
            x %= N;
            
            if (x == 1)
            {
                return 0;   // N ���������, ��� ��� x^2 ? 1 (mod N)
            }
            
            if (x == N - 1)
            {
                break;  // ������� �� �����, ���� ����� -1
            }
        }

        // ���� ����� ���� �������� x ? N-1, ����� N ���������
        if (x != N - 1)
        {
            return 0;
        }
    }

    return 1;  // e��� ������ ��� �����, ����� �������� �������
}

/* ����� 2.1 - ���������� k = 7 */
void point_1()
{
    long long num = 0, res = 0;
    num = Ng + Nc; // ���������

    res = (mod_pow(num, 11, 11) + F3) % 11; // (num^11 + F3) % 11
    
    printf("[����� #1:]\n");
    printf("���������� ����������: %d\n", res);
}

/* ����� 2.2 - ���� ������ */
void point_2()
{
    char text[256] = "���������������������";

    printf("[����� #2]\n");
    printf("�������� �����: %s\n", text);
    cesar(text);
    printf("����� ����� ����������: %s\n", text);
}

/* ����� 2.3 - ���������� A � ���(A, B) */
void point_3()
{
    long long A = powl((Ng * (8 + (Nc % 7))), 2);
    printf("[����� #3:]\n");
    printf("���������� A: %lli\n", A);

    // ���������� B � GCD
	long long B1 = (B % 95) + 900;
	long long B2 = ((B + 50) % 97) + 700;
	long long B3 = ((B + 20) % 101) + 1500;
	long long B4 = ((B - 40) % 103) + 2500;
	printf("���(A, B(mod 95)+900):\n");
	printf("���(A, B(mod 95)+900) = %lli\n", euclid(A, B1));
	printf("���(A, (B+50)(mod 97)+700):\n");
	printf("���(A, (B+50)(mod 97)+700) = %lli\n", euclid(A, B2));
	printf("���(A, (B+20)(mod 101)+1500, (B-40)(mod 103)+2500):\n");
	B3 = euclid(A, B3);
	printf("���(A, (B+20)(mod 101)+1500, (B-40)(mod 103)+2500) = %lli\n\n\n", euclid(B3, B4));
}

/* ����� 2.4 - �������� ����� �� �������� ������� ������� */
void point_4()
{
    int N = 16784, N1 = 601, x = 0;
	x = miller(N);
	if (x == 0)
    {
        printf("����� %d ���������\n", N);
    } else {
        printf("����� %d �������\n", N);
    }
	x = miller(N1);
	if (x == 0)
    {
        printf("����� %d ���������\n", N1);
    } else {
        printf("����� %d �������\n", N1);
    }
}

/* ����� 2.5 - ��������� ��������� � ��������� ������ RSA � �������������� ��������� ������� */
void point_5()
{
    long long p = 587, q = 743;
    long long n = 0, f = 0, e = 0, d = 0;
    n = p * q;
    printf("n = %lli\n", n);
    f = (p - 1) * (q - 1);
    printf("fi = %lli\n", f);
    
    // ������� �� e: 1 < e < ?(n)
    // gcd(e,?(n)) = 1, �� ���� ee ������ ���� ������� ������� � �������� ������ ?(n).
    for (e = 2; e < p; e++) 
    {
		if (euclid(e, p - 1) == euclid(e, q - 1) && euclid(e, p - 1) == 1) 
        {
			break;
		}
	}
	printf("e = %llu\n", e);

    // ������� �� d: d * e ? 1(mod?(n)): (e * d) % f = 1.
    for (d = f/e;;d++) 
    {
		if (((e * d) % f) == 1)
        {
            break;
        }
	}
    printf("d = %llu\n", d);
}

/* ����� 2.6 - ���������� RSA-���������� � ASCII */
void point_6()
{
    long long p = 587, q = 743;
    long long n = 436141, f = 434812;
    long long e = 3; // �������� ���������� - ��������� ����
    long long d = 289875; // �������� ���������� - ��������� ����

    char text[256] = "RSA text"; // �������� �����
    char deciphered[256]; // �������������� �����
    long long cipher_num[256]; // ������ �����, �������������� ������������� �������
    long long t = 0;
    int i = 0, j = 0;

    printf("�������� �����: %s\n", text);
    // ���������� ������
    // �������������� ������� ������� � ����� ��� cipher_num
    for (i = 0; text[i] != '\0'; i++) {
		if (text[i] != '\0')
        {
            // ������� ������ � ASCII ����
            printf("%c = %d\n", text[i], text[i]);
        }

		t = text[i] % n;
        
        // ���������� � ������� e �� ������ n ����� ���. �������� �. � ����.
		for (long long b = 2; b <= e; b++) {
			t = (t * text[i]) % n; // % n - �������� �������� ������������
		}

		cipher_num[i] = t;
		printf("x^e(mod n) ��� %c = %lli\n", text[i], t);
	}

    cipher_num[i] = 0;

    // ������������� ������
    for (j = 0; cipher_num[j] != 0; j++) {
		t = cipher_num[j] % n;
        // t = y**d (mod n) -- �������� �������� � x^e \mod n (����������).
		for (long long b = 2; b <= d; b++) {
			t = (t * cipher_num[j]) % n;
		}
		deciphered[j] = t; // �������� x
		printf("y^d(mod n) ��� %c = %lli\n", text[j], t);
	}
	deciphered[j] = '\0';
	printf("�������������� �����: %s\n", deciphered);
}

/* ����� 2.7 - �������� ������� � �������� � ������� RSA */
void point_7()
{
    char text[256] = "RSA text"; // �������� �����
    long long n = 436141, f = 434812;
    long long e = 3; // �������� ���������� - ��������� ����
    long long d = 289875; // �������� ���������� - ��������� ����
    long long t = 0, i = 0;

    long long sign[1000];
    // �������� �������� �������
	printf("�������� �������:\n");
	for (i = 0; text[i] != '\0'; i++) 
    {
		t = text[i] % n;
        // t = (text_x[i])^d mod n - ���������� �������
		for (long long b = 2; b <= d; b++) 
        {
			t = (t * text[i]) % n;
		}
		sign[i] = t;
		printf("��� %c = %d s = %lli\n", text[i], text[i], t);
	}
	sign[i] = 0;
    // �������� �������
	printf("�������� ��������������:\n");
	for (i = 0; sign[i] != 0; i++) 
    {
		t = sign[i] % n; // ������������� ������������
        // x = s^e mod n - �������������� ������������� ���������
		for (long long b = 2; b <= e; b++) 
        {
			t = (t * sign[i]) % n;
		}
		text[i] = t; // ������ �������� �������� ������, ���� ������� �����.
		printf("s = %lli, x = %d\n", sign[i], text[i]);
	}
	printf("����� ��������� ��������������: %s\n", text);
}

/* ����� 2.8 - ������������� ������������ ���������� ����� �� ����� �����-��������. */
void point_8()
{
    long long a = 5; // ���������, ����� ��� ���� ����������
    long long y = 0; // ��������� ����� ������� ���������
    long long A_key, B_key; // ����������� ��������� ����� ���������� A � B
    long long xy;
    long long mod_xy; // a^(xy) (mod n)
    long long mod_x_y1, mod_y_x1, mod_x_y2, mod_y_x2; // ������������� ���������� ��� �������� ������� ���������� � �������.
    long long x = 0; // ��������� ����� ������� ���������

    char text[256] = "RSA text"; // �������� �����
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

    // ���������� ������ �����: Akey? = B^x (mod n)
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
        printf("����� �����\n");
    }

    // �������� ������� ���������� � ������� �� ������
    // a^(xy) (mod n) = (a^x)^y (mod n) = (a^y)^x (mod n)
	xy = x * y;
    // ���������� (a^x)^y mod n = mod_x_y2
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
    // ���������� (a^y)^x mod n = mod_y_x2
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


/* ����� 2.9 - ���������� ������� ���������� � ������������ � ������� ��������� ������-��������. */
// ������� ��� ���������� ����������� ������ �������� (���)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ������� ��� ���������� ��������� �������� �� ������ (����������� �������� �������)
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // e��� ��������� �������� �� ����������
}

// ��������� ��������� ����� (����������������� ������������������, ������ � ���������)
void generate_private_key(int w[KEY_SIZE], int *n, int *e) {
    srand(time(NULL)); // ������������� ���������� ��������� �����
    int sum = 0;
    printf("��������� ��������� ����� �� �������:\n");
    printf("w[i] = sum(w[0]...w[i-1]) + ���������_��������\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        w[i] = sum + (rand() % 10 + 1); // ������ ����������������� ������������������
        sum += w[i];
        printf("w[%d] = %d\n", i, w[i]);
    }
    *n = sum + (rand() % 10 + 1); // �������� ������ n
    printf("n = sum(w) + ���������_�������� = %d\n", *n);
    
    do {
        *e = rand() % (*n - 1) + 1; // �������� ���������� e
    } while (gcd(*e, *n) != 1); // ���������, ����� e � n ���� ������� ��������
    
    printf("e = %d (��� � n = %d)\n", *e, gcd(*e, *n));
}

// ��������� ��������� ����� (�������������� ��������� �����)
void generate_public_key(int w[KEY_SIZE], int n, int e, int beta[KEY_SIZE]) {
    printf("��������� ��������� ����� �� �������:\n");
    printf("beta[i] = (w[i] * e) mod n\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        beta[i] = (w[i] * e) % n; // ����������� �������� ��������� �����
        printf("beta[%d] = %d\n", i, beta[i]);
    }
}

// ���������� ���������
int encrypt(int message[KEY_SIZE], int beta[KEY_SIZE]) {
    int c = 0;
    printf("���������� �� �������:\n");
    printf("c = sum(message[i] * beta[i])\n");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("message[%d] = %d, beta[%d] = %d, ������������ = %d\n", i, message[i], i, beta[i], message[i] * beta[i]);
        c += message[i] * beta[i];
    }
    return c;
}

// ������������ ���������
void decrypt(int c, int w[KEY_SIZE], int n, int e) {
    int d = mod_inverse(e, n); // ��������� d � �������� ������� � e �� ������ n
    printf("������������ �� �������:\n");
    printf("s = (c * d) mod n\n");
    int s = (c * d) % n;
    printf("s = %d\n", s);
    
    int decrypted[KEY_SIZE]; // ������ ��� ��������������� ���������
    printf("����� ��������� ���������, ������� w[i] �� s\n");
    for (int i = KEY_SIZE - 1; i >= 0; i--) {
        if (s >= w[i]) {
            decrypted[i] = 1;
            s -= w[i];
        } else {
            decrypted[i] = 0;
        }
        printf("s = %d, w[%d] = %d, decrypted[%d] = %d\n", s, i, w[i], i, decrypted[i]);
    }
    
    // ����� ��������������� ���������
    printf("�������������� ���������: ");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%d", decrypted[i]);
    }
    printf("\n");
}

/* ����� 2.9 - 2.9	���������� ������� ���������� � ������������ � ������� ��������� ������-��������. */
void point_9()
{
    int w[KEY_SIZE], n, e;
    generate_private_key(w, &n, &e);
    
    int beta[KEY_SIZE];
    generate_public_key(w, n, e, beta);
    
    int message[KEY_SIZE] = {1, 0, 1, 1, 0, 0, 1, 0}; // �������� ���������
    printf("�������� ���������: ");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%d", message[i]);
    }
    printf("\n");
    
    int c = encrypt(message, beta);
    printf("������������� ���������: %d\n", c);
    
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