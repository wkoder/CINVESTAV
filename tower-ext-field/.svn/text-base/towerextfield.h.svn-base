/*
 * towerextfield.h
 *
 *  Created on: Dec 5, 2010
 *      Author: Viridana Ponce, Moises Osorio
 */

#ifndef TOWEREXTFIELD_H_
#define TOWEREXTFIELD_H_

#include <stdio.h>
#include <gmp.h>

typedef mpz_t fp_t;
typedef fp_t fp2_t[2];
typedef fp2_t fp4_t[2];
typedef fp2_t fp6_t[3];
typedef fp6_t fp12_t[2];

void initFp(fp_t a);
void initFp12(fp12_t a);
void readFp(fp_t a);
void readFp12(fp12_t a);
void printFp12(fp12_t a);

void init(fp_t p, int *tt1, int lentt1, int *tt2, int lentt2, int *tt3, int lentt3);
void finalExponentiation(fp12_t c, fp12_t f0);

#endif /* TOWEREXTFIELD_H_ */
