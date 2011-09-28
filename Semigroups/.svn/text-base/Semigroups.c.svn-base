/*
 *  Created on: Nov 1, 2010
 *      Authors: Viridiana Ponce, Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//#define BY_BRUTE_FORCE
#define MAX_N 10

int matrix[MAX_N][MAX_N]; // Construccion del semigrupo actual
int references[MAX_N][MAX_N*MAX_N*2]; // Pares (a . b) que producen el valor x
int referenceCount[MAX_N]; // Numero de pares (a . b) que producen el valor x

long long getTime() { // Calcula el numero de microsegundos desde la epoca
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000LL + tv.tv_usec;
}

void countSemigroupsByBruteForce(int size, int row, int col, long long *count, long long *countWithLeftIdentity, long long *countWithRightIdentity) {
	if (row == size) { // Caso base, solo queda verificar
		int i, j, k;
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				for (k = 0; k < size; k++)
					if (matrix[ matrix[i][j] ][ k ] != matrix[ i ][ matrix[j][k] ])
						return; // No es asociativo!

		(*count)++; // Es un semigrupo!

		int hasLeftIdentity = 0;
		for (i = 0; i < size; i++) { // Vemos si hay identidad izquierda
			hasLeftIdentity = 1;
			for (j = 0; j < size && hasLeftIdentity; j++)
				hasLeftIdentity &= matrix[i][j] == j;

			if (hasLeftIdentity) // Si la tiene asi que dejamos de buscar
				break;
		}

		int hasRightIdentity = 0;
		for (i = 0; i < size; i++) { // Vemos si hay identidad derecha
			hasRightIdentity = 1;
			for (j = 0; j < size && hasRightIdentity; j++)
				hasRightIdentity &= matrix[j][i] == j;

			if (hasRightIdentity) // Si la tiene, asi que dejamos de buscar
				break;
		}

		if (hasLeftIdentity)
			(*countWithLeftIdentity)++;
		if (hasRightIdentity)
			(*countWithRightIdentity)++;

		return;
	}

	if (col == size) {// Terminamos una fila, la que sigue!
		countSemigroupsByBruteForce(size, row + 1, 0, count, countWithLeftIdentity, countWithRightIdentity);
		return;
	}

	int i;
	for (i = 0; i < size; i++) {
		matrix[row][col] = i; // Prueba cada posibilidad
		countSemigroupsByBruteForce(size, row, col + 1, count, countWithLeftIdentity, countWithRightIdentity);
	}
}

void countSemigroupsByLayers(int size, int n, int a, int b, long long *count, long long *countWithLeftIdentity, long long *countWithRightIdentity) {
	if (a == -1) { // Terminamos una capa
		countSemigroupsByLayers(size, n+1, n+1, 0, count, countWithLeftIdentity, countWithRightIdentity); // Llenamos la siguiente capa
		return;
	}

	if (n == size) { // Encontramos un semigrupo
		(*count)++;

		int hasLeftIdentity = 0, i, j;
		for (i = 0; i < size; i++) { // Vemos si hay identidad izquierda
			hasLeftIdentity = 1;
			for (j = 0; j < size && hasLeftIdentity; j++)
				hasLeftIdentity &= matrix[i][j] == j;

			if (hasLeftIdentity) // Si la tiene, asi que dejamos de buscar
				break;
		}

		int hasRightIdentity = 0;
		for (i = 0; i < size; i++) { // Vemos si hay identidad derecha
			hasRightIdentity = 1;
			for (j = 0; j < size && hasRightIdentity; j++)
				hasRightIdentity &= matrix[j][i] == j;

			if (hasRightIdentity) // Si la tiene asi que dejamos de buscar
				break;
		}

		if (hasLeftIdentity)
			(*countWithLeftIdentity)++;
		if (hasRightIdentity)
			(*countWithRightIdentity)++;

		return;
	}

	int a2 = a, b2 = b;
	if (b2 == n)
		a2--; // Se mueve una celda hacia arriba
	else
		b2++; // Se mueve una celda hacia la derecha

	int x, y, c, ok, i;
	for (x = 0; x < size; x++) { // Probamos cada valor de X
		matrix[a][b] = x;

		ok = 1; // Nos dice si sigue existiendo la propiedad de asociatividad
		for (c = 0; c <= n; c++) {
			y = matrix[b][c];
			if (y >= 0 && matrix[x][c] >= 0 && matrix[a][y] >= 0 && matrix[x][c] != matrix[a][y]) {
				ok = 0;
				break;
			}

			y = matrix[c][a];
			if (y >= 0 && matrix[c][x] >= 0 && matrix[y][b] >= 0 && matrix[c][x] != matrix[y][b]) {
				ok = 0;
				break;
			}
		}

		for (i = 0; i < referenceCount[a] && ok; i += 2) {
			int a0 = references[a][i];
			int b0 = references[a][i + 1];
			int c0 = b;

			y = matrix[b0][c0];
			if (y >= 0 && matrix[a0][y] >= 0 && x != matrix[a0][y]) {
				ok = 0;
				break;
			}
		}

		for (i = 0; i < referenceCount[b] && ok; i += 2) {
			int a0 = a;
			int b0 = references[b][i];
			int c0 = references[b][i + 1];

			y = matrix[a0][b0];
			if (y >= 0 && matrix[y][c0] >= 0 && x != matrix[y][c0]) {
				ok = 0;
				break;
			}
		}

		if (ok) { // Sigue siendo transitivo
			references[x][referenceCount[x]] = a;
			references[x][referenceCount[x] + 1] = b;
			referenceCount[x] += 2; // (a . b) producen x

			countSemigroupsByLayers(size, n, a2, b2, count, countWithLeftIdentity, countWithRightIdentity);

			referenceCount[x] -= 2; // Eliminamos (a . b) como productores de x
		}
	}

	matrix[a][b] = -1; // Regresamos al estado original
}

void countSemigroups(int size, long long *count, long long *countWithLeftIdentity, long long *countWithRightIdentity) {
	int i, j;
	for (i = 0; i < size; i++) // Inicializamos la matriz
		for (j = 0; j < size; j++)
			matrix[i][j] = -1;

#ifdef BY_BRUTE_FORCE
	countSemigroupsByBruteForce(size, 0, 0, count, countWithLeftIdentity, countWithRightIdentity);
#else
	for (i = 0; i < size; i++) // Al inicio no hay referencias
		referenceCount[i] = 0;
	countSemigroupsByLayers(size, 0, 0, 0, count, countWithLeftIdentity, countWithRightIdentity);
#endif
}

int main() {
	printf("Conteo de Semigrupos:\n");
	int size;
	for (size = 1; size <= 6; size++) {
		long long count = 0;
		long long countWithLeftIdentity = 0;
		long long countWithRightIdentity = 0;

		long long time = getTime();
		countSemigroups(size, &count, &countWithLeftIdentity, &countWithRightIdentity);
		time = (getTime() - time) / 1000;

		printf("\nTamaño: %d\n", size);
		printf("Total: %lld\n", count);
		printf("Con identidad izquierda: %lld\n", countWithLeftIdentity);
		printf("Con identidad derecha: %lld\n", countWithRightIdentity);
		printf("Calculado en %lld ms\n", time);
	}
	return 0;
}
