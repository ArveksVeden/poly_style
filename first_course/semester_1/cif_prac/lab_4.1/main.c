#include <stdio.h>
#pragma warning (disable:4996)

int sizeOfBoard, numberOfRooksToPlace, initialNumberOfRooks;
int solutionCounter;
int currentRookCount;
int chessBoard[24][24];
FILE* inputFile;
FILE* outputFile; 

void placeRook(int row, int column) 
{
    // Помечаем клетки в строке и столбце, что они под боем
    for (int i = 0; i < sizeOfBoard; i++) 
    {
        if (chessBoard[row][i] >= 0) 
        {
            chessBoard[row][i]++;
        }
        if (chessBoard[i][column] >= 0) 
        {
            chessBoard[i][column]++;
        }
    }
    chessBoard[row][column] = -1; // Ладья заняла эту клетку
}

void removeRook(int row, int column) {
    // Убираем пометки с клеток, которые были под боем этой ладьи
    for (int i = 0; i < sizeOfBoard; i++) 
    {
        if (chessBoard[row][i] > 0) 
        {
            chessBoard[row][i]--;
        }
        if (chessBoard[i][column] > 0) 
        {
            chessBoard[i][column]--;
        }
    }
    chessBoard[row][column] = 0;
}

void writeSolution() {
    solutionCounter++; 
    for (int i = 0; i < sizeOfBoard; i++) 
    {
        for (int j = 0; j < sizeOfBoard; j++) 
        {
            if (chessBoard[i][j] < 0) 
            {
                fprintf(outputFile, "(%d,%d) ", i, j);
            }
        }
    }
    fprintf(outputFile, "\n");
}

void findSolutions(int startCellIndex) 
{
    for (int cellIndex = startCellIndex; cellIndex < sizeOfBoard * sizeOfBoard; cellIndex++) 
    {
        int currentRow = cellIndex % sizeOfBoard;
        int currentColumn = cellIndex / sizeOfBoard;

        if (chessBoard[currentRow][currentColumn] == 0) 
        {
            placeRook(currentRow, currentColumn);
            currentRookCount++;

            if (currentRookCount == numberOfRooksToPlace) 
            {
                writeSolution();
            } else {
                findSolutions(cellIndex + 1);
            }

            removeRook(currentRow, currentColumn);
            currentRookCount--;
        }
    }
}

int main(void) 
{
    solutionCounter = 0;
    currentRookCount = 0;

    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    fscanf(inputFile, "%d %d %d", &sizeOfBoard, &numberOfRooksToPlace, &initialNumberOfRooks);

    for (int i = 0; i < sizeOfBoard; i++) 
    {
        for (int j = 0; j < sizeOfBoard; j++) 
        {
            chessBoard[i][j] = 0;
        }
    }

    if (initialNumberOfRooks != 0) 
    {
        for (int i = 0; i < initialNumberOfRooks; i++) 
        {
            int row, column;
            fscanf(inputFile, "%d %d\n", &row, &column);
            placeRook(row, column);
            chessBoard[row][column] = -2; // Помечаем клетки, занятые изначально
        }
    }

    findSolutions(0);

    if (solutionCounter == 0) 
    {
        fprintf(outputFile, "no solutions");
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}