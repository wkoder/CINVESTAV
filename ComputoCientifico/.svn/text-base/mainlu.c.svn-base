#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "include/matrix.h"
#include "include/LU.h"

/*
 * main.c
 *
 *  Created on: Jun 27, 2011
 *      Author: Viridiana Ponce, Alexis de la Cruz, Moises Osorio
 */
extern int n, tam, a, b, a1, a2, b1, b2;
double ua, ub;
extern double *x;

int main() {
	int i;
	double **K, **M, **Q, **T, **aux, **InverseM;
	double **A, **Q2, **R;
	double **L, **U;
	double *eigenValues, **eigenVectors;

	int aux2;

	h = (double) (b - a) / n;
	alfa = (double) a2 / a1;
	beta = (double) b2 / b1;

	if (ua == 0 && ub == 0) {
		tam = n - 1;
		aux2 = 1;
	} else {
		tam = n + 1;
		aux2 = 0;
	}

	createVector(&x, tam);
	x[0] = a + (h * aux2);
	for (i = 1; i < tam; i++)
		x[i] = x[i - 1] + h;

	createMatrix(&K, tam, tam);
	createMatrix(&M, tam, tam);
	createMatrix(&InverseM, tam, tam);
	createMatrix(&Q, tam, tam);
	createMatrix(&T, tam, tam);
	createMatrix(&aux, tam, tam);

	createMatrix(&A, tam, tam);
	createMatrix(&Q2, tam, tam);
	createMatrix(&R, tam, tam);

	createMatrix(&L, tam, tam);
	createMatrix(&U, tam, tam);

	createVector(&eigenValues, tam);
	createMatrix(&eigenVectors, tam, tam);

	funcT = functionT;
	funcT2 = functionT2;

	funcQ = functionQ;
	funcM = functionM;

	triDiagonalMatrix(tam, funcT, funcT2, funcT, T);
	diagonalMatrix(tam, funcQ, Q);
	diagonalMatrix(tam, funcM, M);
	//inverseMatrix(tam, M, InverseM);

	escaleByMatrix(tam, tam, 1.0/pow(h, 2), T, aux);
	addMatrix(tam, tam, aux, Q, K);
	copyMatrix(tam,tam,K,A);
	//multiplicationMatrix(tam, tam, InverseM, K, A);
	/*matrixLU(tam, A, L, U);
	printMatrix(tam, tam, A);
	printf("\n");
	printMatrix(tam, tam, L);
	printf("\n");
	L[0][0] = 0;
	L[0][1] = 0;
	L[1][0] = 0;
	L[1][1] = 0;
	printf("%d\n", isCeroDiagonalInf(L,tam));
	printMatrix(tam, tam, U);*/
	factorizeUL(tam,A,eigenValues,eigenVectors);

	printf("Eigenvalues:\n");
	printVector(tam, eigenValues);
	printf("\nEigenvectors:\n");
	printMatrix(tam,tam, eigenVectors);


	destroyMatrix(&K, tam, tam);
	destroyMatrix(&M, tam, tam);
	destroyMatrix(&InverseM, tam, tam);
	destroyMatrix(&Q, tam, tam);
	destroyMatrix(&T, tam, tam);
	destroyMatrix(&aux, tam, tam);
	destroyMatrix(&A, tam, tam);
	destroyMatrix(&Q2, tam, tam);
	destroyMatrix(&R, tam, tam);
	destroyMatrix(&L, tam, tam);
	destroyMatrix(&U, tam, tam);
	destroyVector(&x, tam);


	destroyVector(&eigenValues, tam);
	destroyMatrix(&eigenVectors, tam, tam);

	return 0;
}
