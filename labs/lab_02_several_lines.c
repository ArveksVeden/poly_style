////test = 11.4*9.29314 ans = 105.941796
////01.5*5.55000 = ?

//==================================================
//lab2_3
//==================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
  int inFirst = 1, postDot = 0, firstNum = 0, scndNum = 0,
    ans = 0, toNextDigit = 0, pastZeroes = 0, cntZeroes = 0;
  unsigned long long int firstNumAr[3], scndNumAr[6], tableAr[3][20], resAr[20];
  char str[13];

  gets(str);
  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < 20; i++)
    {
      tableAr[j][i] = 0;
      resAr[i] = 0;
    }
  }
  for (int i = 0; i < 12; i++)
  {
    if (str[i] == '*')
    {
      inFirst = 0;
      postDot = 0;
      continue;
    }
    if (str[i] == '.')
    {
      postDot = 1;
      continue;
    }
    if (inFirst && !postDot)
      firstNumAr[i] = str[i] - '0';
    if (!inFirst && !postDot)
      scndNumAr[i - 5] = str[i] - '0';
    if (inFirst && postDot)
      firstNumAr[2] = str[i] - '0';
    if (!inFirst && postDot)
      scndNumAr[i - 6] = str[i] - '0';
  }

  //
  //for (int i = 0; i < 3; i++)
  //{
  //  printf("%d ", firstNumAr[i]);
  //}
  //printf("\n");

  //for (int i = 0; i < 6; i++)
  //{
  //  printf("%d ", scndNumAr[i]);
  //}
  //printf("\n");
  //printf("%d \n", (firstNumAr[2] * scndNumAr[5] + toNextDigit));

  //
  //make table
  //
  int flag = 0;
  for (int i = 2; i >= 0; i--)
  {
    for (int j = 5; j >= 0; j--)
    {
      tableAr[2 - i][20 - 1 + j - 5 + i - 2] += (firstNumAr[i] * scndNumAr[j]);
      if (tableAr[2 - i][20 - 1 + j - 5 + i - 2] >= 10)
        tableAr[2 - i][20 - 1 + j - 5 + i - 3] = (tableAr[2 - i][20 - 1 + j - 5 + i - 2]) / 10;
      //|| tableAr[2 - i][20 - 1 + j - 5 + i - 2] == 0
      if ((tableAr[2 - i][20 - 1 + j - 5 + i - 2] == 10 ) && !flag)
      {
        cntZeroes++;
      }
      if (tableAr[2 - i][20 - 1 + j - 5 + i - 2] != 10 && tableAr[2 - i][20 - 1 + j - 5 + i - 2] != 0)
      {

        flag = 1;
      }
      tableAr[2 - i][20 - 1 + j - 5 + i - 2] %= 10;

    }
  }
  //check the table
/*  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      printf("%d ", tableAr[i][j]);
    }
    printf("\n");
  }  */
  //findSum
  toNextDigit = 0;
  pastZeroes = 0;
  int sdv = 0;
  for (int i = 1; i < 20; i++)
  {
    if (tableAr[0][20 - i] +
      tableAr[1][20 - i] +
      tableAr[2][20 - i] == 0 && !pastZeroes && sdv < 6)
    {
      sdv++;
      continue;
    }
    else
    {
      pastZeroes = 1;
    }
    resAr[20 - i + sdv] += ((tableAr[0][20 - i] +
      tableAr[1][20 - i] +
      tableAr[2][20 - i] + toNextDigit) % 10);

    if ((tableAr[0][20 - i] + tableAr[1][20 - i] + tableAr[2][20 - i] + toNextDigit) >= 10)
      toNextDigit = ((tableAr[0][20 - i] +
        tableAr[1][20 - i] +
        tableAr[2][20 - i] +
        toNextDigit)) / 10;
    else
      toNextDigit = 0;
  }
  if (toNextDigit != 0)
  {
    for (int j = 0; resAr[20] == 0; j++)
    {
      if (resAr[j + 1 + sdv] != 0)
      {
        resAr[j + sdv] = toNextDigit;
      }
    }
    toNextDigit = 0;
  }
  //cnt zeroes
  pastZeroes = 0;
  for (int i = 2; i >= 0; i--)
  {
    if (!pastZeroes && firstNumAr[i] == 0)
    {
      cntZeroes++;
    }
    if (firstNumAr[i] != 0)
    {
      pastZeroes = 1;
    }
  }
  if (cntZeroes == 3)
  {
    printf("0");
    return 1;
  }
  toNextDigit = cntZeroes;
  pastZeroes = 0;
  for (int i = 5; i >= 0; i--)
  {
    if (!pastZeroes && scndNumAr[i] == 0)
    {
      cntZeroes++;
    }
    if (scndNumAr[i] != 0)
    {
      pastZeroes = 1;
    }
    if (cntZeroes - toNextDigit  == 6)
    {
      printf("0");
      return 1;
    }
  }
  //printf("\n%d\n", cntZeroes);
  //for (int i = 0; i < 20; i++)
  //{
  //  printf("%d", resAr[i]);
  //  if (i == 19 + cntZeroes - 6)
  //  {
  //    printf(".");
  //  }
  //}
  //printf("\n");

  //output
  pastZeroes = 0;
  for (int i = 0; i < 20; i++)
  {
    if ((int)resAr[i + 1] != 0 && !pastZeroes)
    {
      pastZeroes = 1;
      if ((int)resAr[i + 1] < 0)
      {
        printf("%d", resAr[i]);
        break;
      }
      //i++;
      if (i < 19 + cntZeroes - 6)
      {
        i++;
      }
    }
    if (i == 19 + cntZeroes - 6 && !pastZeroes)
    {
      pastZeroes = 1;
    }
    if (pastZeroes)
    {
      printf("%d", resAr[i]);
      if (i == 19 + cntZeroes - 6 && i + 1 < 20)
      {
        printf(".");
      }
    }
  }

}