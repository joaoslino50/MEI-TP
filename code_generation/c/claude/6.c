#include <stdio.h>
#include <stdbool.h>

// Function to multiply two 3x3 matrices
// result = matrixA * matrixB
void multiplyMatrices3x3(const int matrixA[3][3], const int matrixB[3][3], int result[3][3]) {
    // Initialize result matrix to zeros
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
        }
    }
    
    // Perform matrix multiplication
    // result[i][j] = sum over k of (A[i][k] * B[k][j])
    for (int i = 0; i < 3; i++) {           // Row of first matrix
        for (int j = 0; j < 3; j++) {       // Column of second matrix
            for (int k = 0; k < 3; k++) {   // Inner dimension
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Alternative: Function with double precision floating point
void multiplyMatrices3x3Double(const double matrixA[3][3], const double matrixB[3][3], double result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Function to multiply and return via pointer (different approach)
void multiplyMatrices3x3Ptr(int (*matrixA)[3], int (*matrixB)[3], int (*result)[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

// Utility function to print a 3x3 matrix
void printMatrix3x3(const int matrix[3][3], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < 3; i++) {
        printf("  [");
        for (int j = 0; j < 3; j++) {
            printf("%4d", matrix[i][j]);
            if (j < 2) printf(", ");
        }
        printf("]\n");
    }
}

// Print double matrix
void printMatrix3x3Double(const double matrix[3][3], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < 3; i++) {
        printf("  [");
        for (int j = 0; j < 3; j++) {
            printf("%6.1f", matrix[i][j]);
            if (j < 2) printf(", ");
        }
        printf("]\n");
    }
}

// Function to demonstrate step-by-step multiplication
void multiplyWithSteps(const int matrixA[3][3], const int matrixB[3][3], int result[3][3]) {
    printf("\nStep-by-step matrix multiplication:\n\n");
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            printf("result[%d][%d] = ", i, j);
            
            for (int k = 0; k < 3; k++) {
                int term = matrixA[i][k] * matrixB[k][j];
                result[i][j] += term;
                
                printf("%d*%d", matrixA[i][k], matrixB[k][j]);
                if (k < 2) printf(" + ");
                else printf(" = %d", result[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    // Test case 1: Simple integer matrices
    int A[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int B[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    
    int result[3][3];
    
    printf("Matrix Multiplication (3x3)\n");
    printf("===========================\n\n");
    
    printMatrix3x3(A, "Matrix A");
    printMatrix3x3(B, "Matrix B");
    
    // Perform multiplication
    multiplyMatrices3x3(A, B, result);
    printMatrix3x3(result, "Result (A * B)");
    
    // Test case 2: Identity matrix multiplication
    int I[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    
    int identityResult[3][3];
    multiplyMatrices3x3(A, I, identityResult);
    
    printf("\n");
    printMatrix3x3(I, "Identity Matrix I");
    printf("\nA * I = \n");
    printMatrix3x3(identityResult, "Result");
    
    // Test case 3: Step-by-step demonstration
    int C[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int D[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    
    int stepResult[3][3];
    multiplyWithSteps(C, D, stepResult);
    
    // Test case 4: Double precision matrices
    double E[3][3] = {
        {1.5, 2.5, 3.5},
        {4.5, 5.5, 6.5},
        {7.5, 8.5, 9.5}
    };
    
    double F[3][3] = {
        {0.5, 0, 0},
        {0, 0.5, 0},
        {0, 0, 0.5}
    };
    
    double doubleResult[3][3];
    multiplyMatrices3x3Double(E, F, doubleResult);
    
    printf("\nDouble Precision Matrices:\n");
    printMatrix3x3Double(E, "Matrix E");
    printMatrix3x3Double(F, "Matrix F");
    printMatrix3x3Double(doubleResult, "Result (E * F)");
    
    // Test case 5: Verification of matrix multiplication properties
    printf("\n\nMatrix Multiplication Properties:\n");
    printf("=================================\n");
    
    int X[3][3] = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };
    
    int Y[3][3] = {
        {2, 1, 0},
        {1, 3, 1},
        {0, 4, 2}
    };
    
    int XY[3][3], YX[3][3];
    
    multiplyMatrices3x3(X, Y, XY);
    multiplyMatrices3x3(Y, X, YX);
    
    printMatrix3x3(X, "Matrix X");
    printMatrix3x3(Y, "Matrix Y");
    printMatrix3x3(XY, "X * Y");
    printMatrix3x3(YX, "Y * X");
    
    // Check if X*Y equals Y*X (usually not true for matrices)
    bool equal = true;
    for (int i = 0; i < 3 && equal; i++) {
        for (int j = 0; j < 3 && equal; j++) {
            if (XY[i][j] != YX[i][j]) {
                equal = false;
            }
        }
    }
    
    printf("\nMatrix multiplication is %scommutative (X*Y == Y*X)\n", 
           equal ? "" : "NOT ");
    
    // Performance note
    printf("\nImplementation Notes:\n");
    printf("- Time Complexity: O(n³) where n=3 → 27 multiplications\n");
    printf("- Space Complexity: O(1) additional space\n");
    printf("- The order matters: A*B ≠ B*A in general\n");
    
    return 0;
}