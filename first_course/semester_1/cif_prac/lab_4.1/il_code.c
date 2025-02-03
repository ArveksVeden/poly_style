#include <stdio.h>
#pragma warning (disable:4996)

int boardSize, queensToPlace, placedQueens;
int totalSolutions;
int activeQueens;
int board[24][24];
FILE* input, *output;

void markQueen(int r, int c) 
{
    for (int i = 0; i < boardSize; i++) 
    {
        if (board[r][i] >= 0) 
        {
            board[r][i]++;
        }
        if (board[i][c] >= 0) 
        {
            board[i][c]++;
        }
    }
    for (int offset = -boardSize; offset < boardSize; offset++) 
    {
        if (r + offset >= 0 && r + offset < boardSize && c + offset >= 0 && c + offset < boardSize && board[r + offset][c + offset] >= 0) 
        {
            board[r + offset][c + offset]++;
        }
        if (r + offset >= 0 && r + offset < boardSize && c - offset >= 0 && c - offset < boardSize && board[r + offset][c - offset] >= 0) 
        {
            board[r + offset][c - offset]++;
        }
    }
    board[r][c] = -1;
}

void unmarkQueen(int r, int c) 
{
    for (int i = 0; i < boardSize; i++) 
    {
        if (board[r][i] > 0) 
        {
            board[r][i]--;
        }
        if (board[i][c] > 0) 
        {
            board[i][c]--;
        }
    }
    for (int offset = -boardSize; offset < boardSize; offset++) 
    {
        if (r + offset >= 0 && r + offset < boardSize && c + offset >= 0 && c + offset < boardSize && board[r + offset][c + offset] > 0) 
        {
            board[r + offset][c + offset]--;
        }
        if (r + offset >= 0 && r + offset < boardSize && c - offset >= 0 && c - offset < boardSize && board[r + offset][c - offset] > 0) 
        {
            board[r + offset][c - offset]--;
        }
    }
    board[r][c] = 0;
}

void saveSolution() 
{
    totalSolutions++;
    for (int i = 0; i < boardSize; i++) 
    {
        for (int j = 0; j < boardSize; j++) 
        {
            if (board[i][j] < 0) 
            {
                fprintf(output, "(%d,%d) ", i, j);
            }
        }
    }
    fprintf(output, "\n");
}

void exploreSolutions(int start) 
{
    for (int pos = start; pos < boardSize * boardSize; pos++) 
    {
        int row = pos / boardSize;
        int col = pos % boardSize;

        if (board[row][col] == 0) 
        {
            markQueen(row, col);
            activeQueens++;

            if (activeQueens == queensToPlace) 
            {
                saveSolution();
            } else {
                exploreSolutions(pos + 1);
            }

            unmarkQueen(row, col);
            activeQueens--;
        }
    }
}

int main(void) 
{
    totalSolutions = 0;
    activeQueens = 0;

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    fscanf(input, "%d %d %d", &boardSize, &queensToPlace, &placedQueens);

    for (int i = 0; i < boardSize; i++) 
    {
        for (int j = 0; j < boardSize; j++) 
        {
            board[i][j] = 0;
        }
    }

    if (placedQueens != 0) 
    {
        for (int i = 0; i < placedQueens; i++) 
        {
            int x, y;
            fscanf(input, "%d %d\n", &x, &y);
            markQueen(x, y);
            board[x][y] = -2;
        }
    }

    exploreSolutions(0);

    if (totalSolutions == 0) 
    {
        fprintf(output, "no solutions");
    }

    fclose(input);
    fclose(output);

    return 0;
}
