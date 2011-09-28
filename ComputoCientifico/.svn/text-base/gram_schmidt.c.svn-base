/*
 * gram_schmidt.c
 *
 *  Created on: Jun 19, 2011
 *      Author: viri
 */

#include "matrix.h"

/**
 * Compute the matrix Q with the method of Gram Schmidt
 * @attribute n, number of rows and columns of A and Q.
 * @attribute A, matrix A.
 * @attribute Q, matrix Q.
 */
void matrixQ(int n, double **A, double **Q) {
	int i, j, tam;
	double *vectorA, *vectorE, *vectorU, *vectorAux;
	
	createVector(&vectorA, n);
	createVector(&vectorE, n);
	createVector(&vectorU, n);
	createVector(&vectorAux, n);
	for (i = 0; i < n; i++)
		vectorA[i] = A[i][0];
	
	vectore(n, vectorA, vectorE);
	for (i = 0; i < n; i++)
		Q[i][0] = vectorE[i];
	
	tam = 1;
	for (j = 1; j < n; j++) {
		for (i = 0; i < n; i++)
			vectorA[i] = A[i][j];
		
		vectoru(n, tam, Q, vectorA, vectorAux);
		vectore(n, vectorAux, vectorE);
		for (i = 0; i < n; i++)
			Q[i][j] = vectorE[i];
		tam++;
	}

	destroyVector(&vectorA, n);
	destroyVector(&vectorE, n);
	destroyVector(&vectorU, n);
	destroyVector(&vectorAux, n);
}

/**
 * Compute the matrix R with the method Gram Schmidt
 * @attribute n, number of rows and columns of Q, A and R.
 * @attribute Q, matrix Q.
 * @attribute A, matrix A.
 * @attribute R, matrix R.
 */
void matrixR(int n, double **Q, double **A, double **R) {
	double **QTrans;
	createMatrix(&QTrans, n, n);
	
	transposedMatrix(n, n, Q, QTrans);
	multiplicationMatrix(n, n, QTrans, A, R);
	
	destroyMatrix(&QTrans, n, n);
}
