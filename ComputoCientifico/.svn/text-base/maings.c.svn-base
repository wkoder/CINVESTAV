#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "include/matrix.h"
#include "include/simplecenterdiff.h"
#include "include/gram_schmidt.h"

/*
 * main.c
 *
 *  Created on: Jun 19, 2011
 *      Author: Viridiana Ponce, Alexis de la Cruz, Moises Osorio
 */
extern int n, tam, a, b, a1, a2, b1, b2;
double ua, ub;
extern double *x;

int main() {
	int i, j;
	double **K, **M, **Q, **T, **aux, **InverseM;
	double **A, **Q2, **R;
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
	
	createVector(&eigenValues, tam);
	createMatrix(&eigenVectors, tam, tam);
	
	funcT = functionT;
	funcT2 = functionT2;
	
	funcQ = functionQ;
	funcM = functionM;
	
	triDiagonalMatrix(tam, funcT, funcT2, funcT, T);
	diagonalMatrix(tam, funcQ, Q);
//	diagonalMatrix(tam, funcM, M);
//	inverseMatrix(tam, M, InverseM);
	
//	printf("T? %d\n", isSymmetricMatrix(T, tam));
//	printf("Q? %d\n", isSymmetricMatrix(Q, tam));
//	printf("M? %d\n", isSymmetricMatrix(M, tam));
//	printf("M^-1? %d\n", isSymmetricMatrix(InverseM, tam));
	
	escaleByMatrix(tam, tam, 1.0/pow(h, 2), T, aux);
//	printf("aux? %d\n", isSymmetricMatrix(aux, tam));
//	addMatrix(tam, tam, aux, Q, K);
	addMatrix(tam, tam, aux, Q, A);
//	printf("K? %d\n", isSymmetricMatrix(K, tam));
//	multiplicationMatrix(tam, tam, InverseM, K, A);
//	printf("M^-1:\n");
//	printMatrix(tam, tam, InverseM);
//	printf("K:\n");
//	printMatrix(tam, tam, K);
//	printf("A:\n");
//	printMatrix(tam, tam, A);
//	printf("A? %d\n", isSymmetricMatrix(A, tam));

	if (RQP(tam, A, eigenValues, eigenVectors)) {
//		for (i = 0; i < tam; i++) {
//			printf("%f %f\n", x[i], eigenValues[i]);
//		}
		
//		double **Y, **X;
//		createMatrix(&Y, 1, tam);
//		createMatrix(&X, 1, tam);
//		for (i = 0; i < tam; i++)
//			X[0][i] = x[i];
//		multiplyMatrix(1, tam, tam, X, eigenVectors, Y);
//		for (i = 0; i < tam; i++)
//			printf("%f %f\n", X[0][i], Y[0][i]);
//		destroyMatrix(&Y, 1, tam);
		
//		printf("Eigenvalues:\n");
//		printVector(tam, eigenValues);
//		printf("\nEigenvectors:\n");
		printVector(tam, x);
		printMatrix(tam,tam, eigenVectors);
		
//		for (i = 0; i < tam; i++) {
////			printf("%f", x[i]);
//			for (j = 0; j < tam; j++)
//				printf("%f %f\n", x[j], eigenVectors[i][j]);
////				printf(" %f", eigenVectors[i][j]);
////			printf("\n");
//		}
	}

	destroyMatrix(&K, tam, tam);
	destroyMatrix(&M, tam, tam);
	destroyMatrix(&InverseM, tam, tam);
	destroyMatrix(&Q, tam, tam);
	destroyMatrix(&T, tam, tam);
	destroyMatrix(&aux, tam, tam);
	destroyMatrix(&A, tam, tam);
	destroyMatrix(&Q2, tam, tam);
	destroyMatrix(&R, tam, tam);
	destroyVector(&x, tam);
	
	destroyVector(&eigenValues, tam);
	destroyMatrix(&eigenVectors, tam, tam);

	return 0;
}
