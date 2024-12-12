#pragma warning(disable : 4996)  
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

void flip(char* s) {
    char tmp;
    for (int i = 0; i < strlen(s) / 2; i++) {
        tmp = s[i];
        s[i] = s[strlen(s) - 1 - i];
        s[strlen(s) - 1 - i] = tmp;
    }
}
void addition(char* s1, char* s2, char* ans) {
    int tek1, tek2, flag = 0;
    if (strlen(s1) > strlen(s2)) {
        flip(s1); flip(s2);
        for (int i = 0; i < strlen(s2); i++) {
            tek1 = s1[i] - '0' + flag;
            tek2 = s2[i] - '0';
            if ((tek1 + tek2) / 10 == 1) {
                ans[i] = (tek1 + tek2) % 10 + '0';
                flag = 1;
            }
            else {
                ans[i] = (tek1 + tek2) % 10 + '0';
                flag = 0;
            }
        }
        tek1 = (s1[strlen(s2)] - '0' + flag);
        ans[strlen(s2)] = tek1 + '0';
        for (int i = strlen(s2) + 1; i < strlen(s1); i++) {
            ans[i] = s1[i];
        }
        ans[strlen(s1)] = '\0';
        flip(ans); flip(s1); flip(s2);
    }
    else if (strlen(s1) == strlen(s2)) {
        flip(s1); flip(s2);
        for (int i = 0; i < strlen(s2); i++) {
            tek1 = s1[i] - '0' + flag;
            tek2 = s2[i] - '0';
            if ((tek1 + tek2) / 10 == 1) {
                ans[i] = (tek1 + tek2) % 10 + '0';
                flag = 1;
            }
            else {
                ans[i] = (tek1 + tek2) % 10 + '0';
                flag = 0;
            }
        }
        if (flag == 1) {
            ans[strlen(s2)] = '1';
            ans[strlen(s2) + 1] = '\0';
        }
        else ans[strlen(s2)] = '\0';
        flip(ans); flip(s1); flip(s2);
    }
    else if (strlen(s1) < strlen(s2)) addition(s2, s1, ans);

}
void subtruction(char* s1, char* s2, char* ans) {
    int tek1, tek2, flag = 0;
    if (strlen(s1) > strlen(s2)) {
        flip(s1); flip(s2);
        for (int i = 0; i < strlen(s2); i++) {
            tek1 = s1[i] - '0' - flag;
            tek2 = s2[i] - '0';
            if (tek1 - tek2 < 0) {
                tek1 += 10;
                ans[i] = (tek1 - tek2) + '0';
                flag = 1;
            }
            else {
                ans[i] = (tek1 - tek2) + '0';
                flag = 0;
            }
        }
        tek1 = s1[strlen(s2)] - '0' - flag;
        if (tek1 >= 0) {
            ans[strlen(s2)] = tek1 + '0';
            for (int i = strlen(s2) + 1; i < strlen(s1); i++) {
                ans[i] = s1[i];
            }
            if (ans[strlen(s1) - 1] == '0') {
                int i = strlen(s1) - 1;
                while (ans[i] == '0') i -= 1;
                ans[i + 1] = '\0';
            }
            else ans[strlen(s1)] = '\0';
            flip(ans);
        }
        else {
            int j = strlen(s2);
            while (tek1 < 0) {
                tek1 += 10;
                ans[j] = tek1 + '0';
                tek1 = s1[j + 1] - '0' - 1;
                j += 1;
            }
            if (j == strlen(s1)) {
                ans[j] = '\0';
            }
            else {
                ans[j] = tek1 + '0';
                for (int i = j + 1; i < strlen(s1); i++) {
                    ans[i] = s1[i];
                }
                ans[strlen(s1)] = '0';
            }
            if (ans[strlen(s1) - 1] == '0') {
                int i = strlen(s1) - 1;
                while (ans[i] == '0') i -= 1;
                ans[i + 1] = '\0';
            }
            else ans[strlen(s1)] = '\0';
            flip(ans);
        }
    }
    else if (strlen(s1) < strlen(s2)) {
        subtruction(s2, s1, ans);
        flip(ans);
        int i = strlen(ans);
        ans[i] = '-';
        ans[i + 1] = '\0';
        flip(ans);
    }
    else if (strlen(s1) == strlen(s2)) {
        if (strcmp(s1, s2) > 0) {
            flip(s1); flip(s2);
            for (int i = 0; i < strlen(s2); i++) {
                tek1 = s1[i] - '0' - flag;
                tek2 = s2[i] - '0';
                if (tek1 - tek2 < 0) {
                    tek1 += 10;
                    ans[i] = (tek1 - tek2) + '0';
                    flag = 1;
                }
                else {
                    ans[i] = (tek1 - tek2) + '0';
                    flag = 0;
                }
            }
            tek1 = s1[strlen(s2)] - '0' - flag;
            ans[strlen(s2)] = tek1 + '0';
            for (int i = strlen(s2) + 1; i < strlen(s1); i++) {
                ans[i] = s1[i];
            }
            if (ans[strlen(s1) - 1] == '0') {
                int i = strlen(s1) - 1;
                while (ans[i] == '0') i -= 1;
                ans[i + 1] = '\0';
            }
            else ans[strlen(s1)] = '\0';
            flip(ans);
        }
        else if (strcmp(s1, s2) == 0) {
            ans[0] = '0';
            ans[1] = '\0';
        }
        else if (strcmp(s1, s2) < 0) {
            subtruction(s2, s1, ans);
            flip(ans);
            int i = strlen(ans);
            ans[i] = '-';
            ans[i + 1] = '\0';
            flip(ans);
        }
    }
}
void multiplication(char* s1, char* s2, char* ans) {
    if (s1[0] == '0' || s2[0] == '0') {
        ans[0] = '0';
        ans[1] = '\0';
    }
    else if (strlen(s1) >= strlen(s2)) {
        char m1[10000], m2[10000], m3[10000], m4[10000], m5[10000], m6[10000], m7[10000], m8[10000], m9[10000], m0[] = "0";
        strcpy(m1, s1);
        addition(m1, s1, m2); addition(m2, s1, m3); addition(m3, s1, m4); addition(m4, s1, m5); addition(m5, s1, m6); addition(m6, s1, m7); addition(m7, s1, m8); addition(m8, s1, m9);
        flip(s1); flip(s2);
        char nolik[10000]; nolik[0] = '\0';
        char tmp[10000], tmp1[10000] = "0";
        for (int i = 0; i < strlen(s2); i++) {
            if (i != 0) strcpy(tmp1, ans);
            if (s2[i] == '0') {
                strcpy(tmp, m0);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '1') {
                strcpy(tmp, m1);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '2') {
                strcpy(tmp, m2);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '3') {
                strcpy(tmp, m3);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '4') {
                strcpy(tmp, m4);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '5') {
                strcpy(tmp, m5);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '6') {
                strcpy(tmp, m6);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '7') {
                strcpy(tmp, m7);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '8') {
                strcpy(tmp, m8);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
            else if (s2[i] == '9') {
                strcpy(tmp, m9);
                strcat(tmp, nolik);
                addition(tmp1, tmp, ans);
                strcat(nolik, "0");
            }
        }
        flip(s1); flip(s2);
    }
    else if (strlen(s1) < strlen(s2)) multiplication(s2, s1, ans);
}
void from_to(char* s1, char* s2, char* ans) {
    if (s1[0] != '-' && s2[0] != '-') {
        char odin[] = "1", tmp[10000] = "0", tmp2[10000];
        while (strcmp(s2, s1) != -1) {
            addition(tmp, s2, ans);
            strcpy(tmp, ans);
            subtruction(s2, odin, tmp2);
            strcpy(s2, tmp2);
        }
    }
    else if (s1[0] == '-' && s2[0] == '-') {
        flip(s1);
        s1[strlen(s1) - 1] = '\0';
        flip(s1);
        flip(s2);
        s2[strlen(s2) - 1] = '\0';
        flip(s2);
        from_to(s2, s1, ans);
        flip(ans);
        int dora = strlen(ans);
        ans[dora] = '-';
        ans[dora + 1] = '\0';
        flip(ans);
    }
    else if (s1[0] == '-' && s2[0] != '-') {
        char lena[] = "-1", lenb[] = "0", mp1[10000], mp2[10000];
        from_to(s1, lena, mp1);
        from_to(lenb, s2, mp2);
        flip(mp1);
        mp1[strlen(mp1) - 1] = '\0';
        flip(mp1);
        subtruction(mp2, mp1, ans);
    }
}
int strcompare(char* s1, char* s2) {
    while (*s1++ && *s2++) {
        if (*s1 > *s2) return 1;
        else if (*s2 > *s1) return -1;
        else if (*s1 == '\0') return 0;
    }
}
void delenie(char* s, char* ans) { 
    ans[0] = '0';
    ans[1] = '.';
    int lena = 2;
    int leni = strlen(s);
    char odin[10000] = "1";
    char tmp[10000];
    strcpy(tmp, odin);
    while (strcmp(odin, "0") != 0) {
        int len1 = strlen(odin);
        strcat(odin, "0");
        int mnoz = 1;
        strcpy(tmp, odin);
        char prom[10000];
        strcpy(prom, s);
        for (mnoz = 1; mnoz < 10; mnoz++) {
            char prom2[10000];
            char mnozs[10000];
            mnozs[0] = mnoz + '0';
            mnozs[1] = '\0';
            multiplication(s, mnozs, prom2);
            char ostal[10000];
            if (strcompare(prom2, odin) == 0) {
                break;
            }
            else {
                subtruction(odin, prom2, ostal);
                flip(prom2);
                flip(odin);
                if (ostal[0] == '-') {
                    mnoz--;
                    break;
                }
            }
        }
        if (mnoz == 0) {
            ans[lena] = mnoz + '0';
            lena++;
            if (lena == 10) break;
            continue;
        }
        char mnozs[10000];
        mnozs[0] = mnoz + '0';
        mnozs[1] = '\0';
        multiplication(s, mnozs, prom);
        char ost[10000];
        if (strcompare(odin, prom) == 0) strcpy(ost, "0");
        else subtruction(odin, prom, ost);
        strcpy(odin, ost);
        ans[lena] = mnoz + '0';
        lena++;
        if (lena == 10) break;
    }
    ans[lena] = '\0';
}



int main(void) {
    char znak[10], s1[10000], s2[10000], ans[10000];
    printf("Select an arithmetic operation: \n");
    printf("1. addition\n2. subtraction\n3. multiplication\n4. factorization\n5. factorial\n6. addition from to\n");
    int oper;
    scanf("%d", &oper);
    if (oper == 1) {
        printf("Enter the expression: number + number\n");
        scanf("%s", s1); scanf("%s", znak); scanf("%s", s2);
        if (s1[0] == '-' && s2[0] != '-') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            subtruction(s2, s1, ans);
            printf("%s", ans);
        }
        else if (s1[0] != '-' && s2[0] == '-') {
            flip(s2);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            subtruction(s1, s2, ans);
            printf("%s", ans);
        }
        else if (s1[0] == '-' && s2[0] == '-') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            flip(s2);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            addition(s1, s2, ans);
            int dora = strlen(ans);
            flip(ans); ans[dora] = '-'; ans[dora + 1] = '\0'; flip(ans);
            printf(ans);
        }
        else {
            addition(s1, s2, ans);
            printf("%s", ans);
        }
    }
    if (oper == 2) {
        printf("Enter the expression: number - number\n");
        scanf("%s", s1); scanf("%s", znak); scanf("%s", s2);
        if (s1[0] == '-' && s2[0] != '-') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            addition(s1, s2, ans);
            int dora = strlen(ans);
            flip(ans); ans[dora] = '-'; ans[dora + 1] = '\0'; flip(ans);
            printf(ans);
        }
        else if (s1[0] != '-' && s2[0] == '-') {
            flip(s2);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            addition(s1, s2, ans);
            printf(ans);
        }
        else if (s1[0] == '-' && s2[0] == '-') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            flip(s2);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            subtruction(s2, s1, ans);
            printf("%s", ans);
        }
        else {
            subtruction(s1, s2, ans);
            printf("%s", ans);
        }
    }
    if (oper == 3) {
        printf("Enter the expression: number * number\n");
        scanf("%s", s1); scanf("%s", znak); scanf("%s", s2);
        if (s1[0] == '-' && s2[0] == '(') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            s2[strlen(s2) - 2] = '\0';
            flip(s2);
            multiplication(s1, s2, ans);
            printf("%s", ans);
        }
        else if (s1[0] == '-' && s2[0] != '(') {
            flip(s1);
            s1[strlen(s1) - 1] = '\0';
            flip(s1);
            multiplication(s1, s2, ans);
            int dora = strlen(ans);
            flip(ans); ans[dora] = '-'; ans[dora + 1] = '\0'; flip(ans);
            printf("%s", ans);
        }
        else if (s1[0] != '-' && s2[0] == '(') {
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            s2[strlen(s2) - 2] = '\0';
            flip(s2);
            multiplication(s1, s2, ans);
            int dora = strlen(ans);
            flip(ans); ans[dora] = '-'; ans[dora + 1] = '\0'; flip(ans);
            printf("%s", ans);
        }
        else if (s1[0] != '-' && s2[0] != '(') {
            multiplication(s1, s2, ans);
            printf("%s", ans);
        }
    }
    if (oper == 4) {
        printf("Enter the expression: number ^ number\n");
        scanf("%s", s1); scanf("%s", znak); scanf("%s", s2);
        if (strcmp(s2, "0") == 0) printf("1");
        else if (s2[0] != '-') {
            if (strcmp(s2, "1") == 0) printf("%s", s1);
            else if (s1[0] == '-' && (s2[strlen(s2) - 1] == '1' || s2[strlen(s2) - 1] == '3' || s2[strlen(s2) - 1] == '5' || s2[strlen(s2) - 1] == '7' || s2[strlen(s2) - 1] == '9')) {
                flip(s1);
                s1[strlen(s1) - 1] = '\0';
                flip(s1);
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                printf("-%s", ans);
            }
            else if (s1[0] != '-') {
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                printf("%s", ans);
            }
            else if (s1[0] == '-' && (s2[strlen(s2) - 1] == '0' || s2[strlen(s2) - 1] == '2' || s2[strlen(s2) - 1] == '4' || s2[strlen(s2) - 1] == '6' || s2[strlen(s2) - 1] == '8')) {
                flip(s1);
                s1[strlen(s1) - 1] = '\0';
                flip(s1);
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                printf("%s", ans);
            }
        }
        else {
            flip(s2);
            s2[strlen(s2) - 1] = '\0';
            flip(s2);
            if (strcmp(s2, "1") == 0) {
                if (s1[0] == '-') {
                    flip(s1);
                    s1[strlen(s1) - 1] = '\0';
                    flip(s1);
                    char del[10000];
                    delenie(s1, del);
                    printf("-%s", del);
                }
                else {
                    char del[10000];
                    delenie(s1, del);
                    printf("%s", del);
                }
            }
            else if (s1[0] == '-' && (s2[strlen(s2) - 1] == '1' || s2[strlen(s2) - 1] == '3' || s2[strlen(s2) - 1] == '5' || s2[strlen(s2) - 1] == '7' || s2[strlen(s2) - 1] == '9')) {
                flip(s1);
                s1[strlen(s1) - 1] = '\0';
                flip(s1);
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                char del[10000];
                delenie(ans, del);
                printf("-%s", del);
            }
            else if (s1[0] != '-') {
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                char del[10000];
                delenie(ans, del);
                printf("%s", del);
            }
            else if (s1[0] == '-' && (s2[strlen(s2) - 1] == '0' || s2[strlen(s2) - 1] == '2' || s2[strlen(s2) - 1] == '4' || s2[strlen(s2) - 1] == '6' || s2[strlen(s2) - 1] == '8')) {
                flip(s1);
                s1[strlen(s1) - 1] = '\0';
                flip(s1);
                char odin[] = "1", tmp[10000] = "1", tmp2[10000];
                while (strcmp(s2, "0") != 0) {
                    multiplication(tmp, s1, ans);
                    strcpy(tmp, ans);
                    subtruction(s2, odin, tmp2);
                    strcpy(s2, tmp2);
                }
                char del[10000];
                delenie(ans, del);
                printf("%s", del);
            }
        }
 }
 if (oper == 5) {
     printf("Enter the expression: number !\n");
     scanf("%s", s1); scanf("%s", znak);
     char odin[] = "1", tmp[10000] = "1", tmp2[10000];
     while (strcmp(s1, "1") != 0) {
         multiplication(tmp, s1, ans);
         strcpy(tmp, ans);
         subtruction(s1, odin, tmp2);
         strcpy(s1, tmp2);
     }
     printf("%s", ans);
 }
if (oper == 6) {
     printf("Enter the expression: number to number\n");
     scanf("%s", s1); scanf("%s", znak); scanf("%s", s2);
     from_to(s1, s2, ans);
     printf("%s", ans);
 }

 return 0;
}