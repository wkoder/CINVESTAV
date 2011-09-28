#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

#define maxValue 30;
extern int n,tam;
extern double *x;

extern double h, alfa, beta, ua, ub;

/**
 * function by calculate the matrix Q.
 */
double functionQ() {
	static int i = 0;
	double value;

	if (x[i] < -0.5 || x[i] > 0.5) {
		value = maxValue;
	} else
		value = 0;

//	if ((i == 0 || i == tam - 1) && (ua != 0 && ub != 0))
//		value /= 2;
	i++;

	return value;
}

/**
 * Function by calculate the diagonal down and up of a tridiagonal matrix T.
 */
double functionT() {
	return -1;
}

/**
 * Function by calculate diagonal principal of matrix T.
 */
double functionT2() {
	static int i = 0;
	double value;
	value = 2;

	if (i == 0 && ua != 0 && ub != 0)
		value = 2*((h / alfa) + 1);
	else if (i == tam - 1 && ua != 0 && ub != 0)
		value = 2*(1 - (h / beta));
	i++;

	return value;
}

/**
 * Function by calculate matrix M.
 */
double functionM() {
	static int i = 0;
	double values;
	values = 1;

	if ((i == 0 || i == tam - 1) && (ua != 0 && ub != 0))
		values = 0.5;
	i++;

	return values;
}

void matrixLU(int tam,double **matA, double **matLRes, double **matURes){
	int i;
	matLRes[0][0] = 1;

	matURes[0][0] = matA[0][0];
	matURes[0][1] = matA[0][1];

	for(i=1;i<tam;i++){
		matLRes[i][i-1] = (double)matA[i][i-1]/matURes[i-1][i-1];
		matURes[i][i] = matA[i][i] - matLRes[i][i-1] * matA[i-1][i];

		matLRes[i][i] = 1;
		matURes[i][i+1] = matA[i][i+1];
	}
}

void factorizeUL(int tam, double **matA, double *l, double **v){
	double **L, **U, **matAux, **UL;
	int i;

	if (!isSymmetricMatrix(matA, tam)) {
		printf("A is not symmetric\n");
		return;
	}

	createMatrix(&L,tam,tam);
	createMatrix(&U,tam,tam);
	createMatrix(&UL, tam, tam);
	createMatrix(&matAux, tam, tam);
	unitMatrix(tam, v);

	while (1) {
		// LU = A
		matrixLU(tam, matA, L, U);

		multiplicationMatrix(tam, tam, U, L, UL);

		// P = PL
		multiplicationMatrix(tam, tam, v, L, matAux);
		copyMatrix(tam, tam, matAux, v);

		if (isCeroDiagonalInf(UL, tam))
			break;


		copyMatrix(tam, tam, UL, matA);
	}

	for (i = 0; i < tam; i++)
		l[i] = UL[i][i];

	destroyMatrix(&L, tam, tam);
	destroyMatrix(&U, tam, tam);
	destroyMatrix(&UL, tam, tam);
	destroyMatrix(&matAux, tam, tam);

}

