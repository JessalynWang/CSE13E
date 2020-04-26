// file for all the functions of a matrix calculator
// Libraries included here
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MatrixMath.h"
#include "BOARD.h"

/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(float mat[DIM][DIM]) {


    // row, col used for iterating; negflag to tell if the value is negative
    // spaces will he how the numbers in the matrix need to be spaced
    int row, col, negflag = 0, spaces = 0;
    // the maximum value needs to be found to determine the spacing of the matrix
    for (row = 0; row < DIM; row++) { // iterates through the rows of the matrix
        for (col = 0; col < DIM; col++) { // iterates through the columns of the matrix
            int value = (int) mat[row][col];
            // based on what value is, this chain of ifs will assign the # of spaces needed for printing
            if (value < 0) {
                if (-value < 10) {
                    if (spaces <= 1) {
                        spaces = 1;
                        negflag = 1;
                    }
                } else if (-value < 100) {
                    if (spaces <= 2) {
                        spaces = 2;
                        negflag = 1;
                    }
                } else {
                    if (spaces <= 3) {
                        spaces = 3;
                        negflag = 1;
                    }
                }
            } else {
                if (value < 10) {
                    if (spaces < 1) {
                        spaces = 1;
                        negflag = 0;
                    }
                } else if (value < 100) {
                    if (spaces < 2) {
                        spaces = 2;
                        negflag = 0;
                    }
                } else {
                    if (spaces < 3) {
                        spaces = 3;
                        negflag = 0;
                    }
                }
            }
        }
    }
    // totalspaces stores the total width of the float printed
    int iter, totalspaces = negflag + spaces + 3;
    // below prints the matrix
    // first prints the line on top, then all of the values and their dividers
    printf(" ________");
    for (iter = 0; iter < (totalspaces) * 3; iter++) {
        printf("_");
    }
    printf("\n");

    for (row = 0; row < DIM; row++) {
        printf("|");
        for (col = 0; col < DIM; col++) {
            printf(" %*.2f |", totalspaces, mat[row][col]);
        }
        printf("\n --------");
        for (iter = 0; iter < (totalspaces) * 3; iter++) {
            printf("-");
        }
        printf("\n");
    }
}

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of the corresponding element of mat2,  otherwise return FALSE
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(float mat1[DIM][DIM], float mat2[DIM][DIM]) {

    // Checks for equality between two matrices
    // Returns 0 for false and 1 for true
    int row, col;

    // iterates through the each value in the matrix
    for (row = 0; row < DIM; row++) {
        for (col = 0; col < DIM; col++) {
            // if the two numbers subtracted are not within the margin of error, return false
            float value = mat1[row][col] - mat2[row][col]; // subtracts the values
            // bellow makes sure that they are in range of FP_DELTA
            if (!(((value >= 0) && (value <= FP_DELTA))
                    || ((value < 0) && (value >= -FP_DELTA)))) {
                // returns false if a number is not in range
                return FALSE;
            }
        }
    }

    //returns true if all the numbers are equal
    return TRUE;
}

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(float mat1[DIM][DIM], float mat2[DIM][DIM], float result[DIM][DIM]) {

    //Adds values of a matrix and stores in result
    int row, col;

    //iterates through the input matrices
    for (row = 0; row < DIM; row++) {
        for (col = 0; col < DIM; col++) {
            // adds the two values of the input together and stores them in the result matrix
            result[row][col] = mat1[row][col] + mat2[row][col];
        }
    }
}

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(float mat1[DIM][DIM], float mat2[DIM][DIM], float result[DIM][DIM]) {

    int row, col, inrow;
    float adder;

    // iterates through the matrices
    for (row = 0; row < DIM; row++) {
        for (col = 0; col < DIM; col++) {
            // stores the values of that row in matrix1 in an array
            float rowvals[DIM] = {mat1[row][0], mat1[row][1], mat1[row][2]};
            adder = 0.0;
            // iterates through the rows if matrix2
            // adds the value from rowvals * mat2 and stores it in result
            for (inrow = 0; inrow < DIM; inrow++) {
                adder += mat2[inrow][col] * rowvals[inrow];
                result[row][col] = adder;
            }
        }
    }
}

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(float x, float mat[DIM][DIM], float result[DIM][DIM]) {

    int row, col;
    // iterates through the matrix
    for (row = 0; row < DIM; row++) {
        for (col = 0; col < DIM; col++) {
            // adds each value of the matrix with the scalar and stores it in result
            result[row][col] = mat[row][col] + x;
        }
    }

}

/**
 * MatrixScalarAdd performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(float x, float mat[DIM][DIM], float result[DIM][DIM]) {

    int row, col;

    // iterates through the matrix
    for (row = 0; row < DIM; row++) {
        for (col = 0; col < DIM; col++) {
            // multiplies each value of the matrix with the scalar and stores it in result
            result[row][col] = mat[row][col] * x;
        }
    }
}

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
float MatrixTrace(float mat[DIM][DIM]) {

    int row, col;
    float sum = 0;

    // iterates over the matrix
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            if (row == col) {
                // if the row and col are equal (a diagonal value), add the value into sum
                sum += mat[row][col];
            }
        }
    }

    return sum;
}

/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[DIM][DIM], float result[DIM][DIM]) {

    int row, col;
    // iterates through the matrix column, row style
    for (col = 0; col < DIM; col++) {
        for (row = 0; row < DIM; row++) {
            // stores the value of mat in into result in column major order
            result[col][row] = mat[row][col];
        }
    }
}

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[DIM][DIM], float result[2][2]) {

    // result_row and result_col are the indexes of the result matrix
    // movecounter is a flag that indicates when result_row needs to be incremented
    int row, col, result_row, result_col, movecounter;
    result_row = 0;
    movecounter = 0;
    // iterates through the input matrix
    for (row = 0; row < DIM; row++) {
        // since result_col will either have 0 or 2 values for every row,
        // we can reset it every iteration of the loop
        result_col = 0;
        for (col = 0; col < DIM; col++) {
            if (row != i && col != j) {
                // if the numbers are not the row and col that are striked out, 
                // we add the value to result
                result[result_row][result_col] = mat[row][col];
                result_col++;
                movecounter++;
            }
        }
        // if move counter is 2 (2 entries have been put into result), increment result_row
        if ((movecounter == 2) && (result_row == 0)) {
            result_row = 1;
        }
    }
}

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[DIM][DIM]) {

    // sub and col: sub will be used to take the submatrix
    //              col will be used to iterate through the first row of mat
    float sub[2][2] = {
        {},
        {}
    };
    int col;
    float value = 0.0; // number where determinant will be stored
    // iterates through the first row of mat
    for (col = 0; col < DIM; col++) {
        // finds the submatrix and stores it in sub
        MatrixSubmatrix(0, col, mat, sub);
        // the below if statement calculates part of the determinant accordingly and adds it into value
        if (col == 1) {
            value -= mat[0][col] * (sub[0][0] * sub[1][1] - sub[0][1] * sub[1][0]);
        } else {
            value += mat[0][col] * (sub[0][0] * sub[1][1] - sub[0][1] * sub[1][0]);
        }
    }

    return value;
}

/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: none
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[DIM][DIM], float result[DIM][DIM]) {

    // odd keeps track of whether or not row + col is odd (0 = even, 1 = odd))
    // subrc will be used to find submatrices
    // detr is the scalar that the matrix needs to be multiplied by to get the inverse
    int row1, col1, odd = 0;
    float subrc[2][2] = {
        {},
        {}
    };
    float detr = 1.0 / MatrixDeterminant(mat);

    // iterates through mat
    for (row1 = 0; row1 < DIM; row1++) {
        for (col1 = 0; col1 < DIM; col1++) {
            // finds the submatrix for a given value of mat
            MatrixSubmatrix(col1, row1, mat, subrc);
            // calculates the value and changes sign based on odd/even-ness
            float value = (subrc[0][0] * subrc[1][1]) - (subrc[0][1] * subrc[1][0]);
            if (odd) {
                value = -value;
            }
            // multiplies the value by the scalar and stores it in the result
            result[row1][col1] = value * detr;
            // changes odd from odd or even to the other
            if (odd) {
                odd = 0;
            } else {
                odd = 1;
            }
        }
    }
}