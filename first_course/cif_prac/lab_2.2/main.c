#include <stdio.h>

int main(void)
{
    short data_range = 0, max_len = 1, cur_len = 1;
    int prev_num = 0, cur_num = 0;

    scanf("%hd", &data_range);
    scanf("%i", &prev_num);

    for (short i = 1; i < data_range; i++)
    {
        scanf("%i", &cur_num);
        if (cur_num > prev_num && cur_num != prev_num)
        {
            cur_len++;
        } else {
            if (cur_len > max_len)
            {
                max_len = cur_len;
            }
            cur_len = 1;
        }
        prev_num = cur_num;
    }

    printf("%hd", max_len);

    return 0;
}