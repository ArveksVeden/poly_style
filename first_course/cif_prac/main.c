#include <stdio.h>

void trans(long long num, int base)
{
	char numsys_dic[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	char res[65];
	short index = 0;

	if (num < 0)
	{
		printf("%c", '-');
		num *= -1;
	}

	while (num > 0)
	{
		res[index] = numsys_dic[num % base];
		num /= base;
		index++;
	}

	for (int i = index - 1; i >= 0; i--)
	{
		printf("%c", res[i]);
	}
}

int main(void)
{
	short s = -0xaa2; // -2722 в 10-й СС
	int i = -0x21ab0802; // -564856834 в 10-й СС
	unsigned int ui = 0x5f04c788; // 1594148744 в 10-й СС
	long l = 0x3bcea81e; // 1003399198 в 10-й CC
	unsigned long ul = 0x843cbb50; // 2218572624 в 10-й СС

	printf("short;-aa2=", s);
	trans(s, 34);
	printf(";34\n");

	printf("int;-21ab0802=", i);
	trans(i, 6);
	printf(";6\n");

	printf("unsigned int;%x=", ui);
	trans(ui, 31);
	printf(";31\n");

	printf("long;%x=", l);
	trans(l, 7);
	printf(";7\n");

	printf("unsigned long;%x=", ul);
	trans(ul, 15);
	printf(";15\n");

	return 0;
}