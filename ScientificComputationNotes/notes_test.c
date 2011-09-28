/*
 * notes.c
 *
 *  Created on: Jul 29, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>

#include "notes.h"

int main(int argc, char **argv) {
	double *a;
	int n;
	
	n = 5;
	
	a = unitMatrix_create(n);
	unitMatrix_free(a);
	a = tridiagonalMatrix_DF(n);
	unitMatrix_free(a);
	
	printf("Done!\n");
	
	return EXIT_SUCCESS;
}
