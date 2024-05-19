#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500

void initialize_matrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = i;
            B[i][j] = j;
            C[i][j] = 0.0;
        }
    }
}

void multiply_matrices(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; ++i) {
        #pragma omp parallel for
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    double start_time, end_time;


    initialize_matrices(A, B, C);

    multiply_matrices(A, B, C);
    
    return 0;
}

