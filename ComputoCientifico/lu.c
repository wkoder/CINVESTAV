#include <stdio.h>

#include "matrix.h"

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

	while (!isCeroDiagonalInf(matA, tam)) {
//	while (!isUpperTriangular(tam, matA)) {
		// LU = A
		matrixLU(tam, matA, L, U);

		multiplicationMatrix(tam, tam, U, L, UL);

		// P = PL
		multiplicationMatrix(tam, tam, v, L, matAux);
		copyMatrix(tam, tam, matAux, v);

		copyMatrix(tam, tam, UL, matA);
	}

	for (i = 0; i < tam; i++)
		l[i] = UL[i][i];

	destroyMatrix(&L, tam, tam);
	destroyMatrix(&U, tam, tam);
	destroyMatrix(&UL, tam, tam);
	destroyMatrix(&matAux, tam, tam);

}

