/*
 * notes.h
 *
 *  Created on: Jul 29, 2011
 *      Author: Moises Osorio
 */

#ifndef NOTES_H_
#define NOTES_H_

double *unitMatrix_create(int n);
void unitMatrix_free(double *a);
double *tridiagonalMatrix_DF(int n);

#endif /* NOTES_H_ */
