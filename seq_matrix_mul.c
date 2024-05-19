#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500


void initialize_matrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i;
            B[i][j] = j;
            C[i][j] = 0;
        }
    }
}

// Function to multiply two matrices
void multiplyMatrices(int A[N][N], int B[N][N], int result[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], result[N][N];
    clock_t start, end;
    double cpu_time_used;

    initialize_matrices(A, B, result);

    multiplyMatrices(A, B, result);

    return 0;

}
