#include "utilis.h"

void gaussianElimination(double **A, double *B, double *X, const short size) 
{
    int i, j, k;

    // Forward Elimination (Convert A into upper triangular form)
    for (i = 0; i < size - 1; i++) 
    {
        // Partial Pivoting (Find max element in column i)
        int maxRow = i;
        for (k = i + 1; k < size; k++) 
        {
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        }

        // Swap rows if needed
        if (maxRow != i) 
        {
            for (j = 0; j < size; j++) 
            {
                double temp = A[i][j];
                A[i][j] = A[maxRow][j];
                A[maxRow][j] = temp;
            }
            double tempB = B[i];
            B[i] = B[maxRow];
            B[maxRow] = tempB;
        }

        // Perform elimination
        for (k = i + 1; k < size; k++) 
        {
            double factor = A[k][i] / A[i][i];
            for (j = i; j < size; j++)
                A[k][j] -= factor * A[i][j];

            B[k] -= factor * B[i];
        }
    }

    // Back Substitution (Solve for X)
    for (i = size - 1; i >= 0; i--) 
    {
        X[i] = B[i];
        for (j = i + 1; j < size; j++)
            X[i] -= A[i][j] * X[j];

        X[i] /= A[i][i];
    }
}