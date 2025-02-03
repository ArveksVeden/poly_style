#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char month_data[12][12] = 
    {
        "january", "february", "march", "april", "may", 
        "june", "july", "august", "september", "october", 
        "november", "december"
    };

    short int m = 0;
    char data[11], month[3];
    fgets(data, sizeof(data), stdin);

    if (data[2] != '.' || data[5] != '.')
    {
        printf("incorrect\n");
        return 0;
    }

    *(month) = *(data + 3);
    *(month + 1) = *(data + 4);
    *(month + 2) = '\0';

    m = atoi(month);

    if (m <= 0 || m > 12)
    {
        printf("incorrect\n");
        return 0;
    }

    printf("%c%c.%s.%c%c%c%c\n", *(data), *(data + 1), month_data[m-1], *(data + 6), *(data + 7), *(data + 8), *(data + 9));

    return 0;
}