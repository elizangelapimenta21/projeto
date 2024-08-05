#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int **mat1, int **mat2, int **result, int N) {
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = 0;
            for (k = 0; k < N; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void printMatrix(int **matrix, int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;
    scanf("%d", &N);
    
    int **mat1, **mat2, **result;
    int i, j;

    
    mat1 = (int **)malloc(N * sizeof(int *));
    mat2 = (int **)malloc(N * sizeof(int *));
    result = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++) {
        mat1[i] = (int *)malloc(N * sizeof(int));
        mat2[i] = (int *)malloc(N * sizeof(int));
        result[i] = (int *)malloc(N * sizeof(int));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    multiplyMatrices(mat1, mat2, result, N);

    printMatrix(result, N);

    for (i = 0; i < N; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(result[i]);
    }
    free(mat1);
    free(mat2);
    free(result);

    return 0;
}
