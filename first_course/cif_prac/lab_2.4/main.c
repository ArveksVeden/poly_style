#include <stdio.h>

int main() {
    int matrix[100][100], M = 0, N = 0, max_sum = -2147483648;

    scanf("%i %i", &M, &N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%i", &matrix[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        int cur_sum = 0;
        for (int j = 0; j < N; j++) {
            cur_sum += matrix[i][j];
        }
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
        }
    }

    printf("%i\n", max_sum);

    return 0;
}