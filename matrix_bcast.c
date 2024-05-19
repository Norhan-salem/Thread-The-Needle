
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int n = 3;
    float **matrix;

    // Allocate memory for the matrix on all processes
    matrix = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (float *)malloc(n * sizeof(float));
    }

    // Root process initializes the matrix
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rank + i * n + j; 
            }
        }
    }

    // Create a derived datatype for one row of the matrix
    MPI_Datatype row_type;
    MPI_Type_contiguous(n, MPI_FLOAT, &row_type);
    MPI_Type_commit(&row_type);

    // Broadcast each row of the matrix
    for (int i = 0; i < n; i++) {
        MPI_Bcast(matrix[i], 1, row_type, 0, MPI_COMM_WORLD);
    }

    // Print the matrix on each process
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            printf("Process %d:\n", rank);
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    printf("%f ", matrix[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    // Free the datatype and the matrix
    MPI_Type_free(&row_type);
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    MPI_Finalize();
    return 0;
}
