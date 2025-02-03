#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char data[110], ch;
    short int N = 0;
    scanf("%hd\n", &N);
    fgets(data, sizeof(data), stdin);

    short int cout = 1;
    for (int i = 0; data[i] != '\0'; i++)
    {
        if (*(data + i) != ' ')
        {
            ch = *(data + i);
            if ((cout == N) && ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')))
            {
                *(data + i) = toupper(ch);
            }
            cout++;
        } else {
            cout = 1;
        }
        printf("%c", *(data + i));
    }
    return 0;
}