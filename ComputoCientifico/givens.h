/*
 * givens.h
 *
 *  Created on: Aug 18, 2011
 *      Author: Moises Osorio
 */

#ifndef GIVENS_H_
#define GIVENS_H_

void givens(double **A, double *l, double **v, int n);
void givensFactorization(double **A, double **Q, double **R, int n);

#endif /* GIVENS_H_ */
