/*
 * wh.h
 *
 *  Created on: Nov 1, 2010
 *      Author: Moises Osorio
 */

#ifndef _WH_H_
#define _WH_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 12


// wh.c
void getPolarityForm(int* booleanForm, int* polarityForm, int n);
void getBooleanForm(int* polarityForm, int* booleanForm, int n);
void walshHadamardTransform(int *booleanFunction, int *whtransform, int n);
void inverseWalshHadamardTransform(int *whtransform, double* booleanFunction, int n);
int getNonLinearity(int *whtransform, int n);
int getCorrelationImmunity(int *whtransform, int n);
int getNonLinearityDeviation(int *whtransform, int n, int nl);
int getCorrelationImmunityDeviation(int *whtransform, int n, int m);
double getBooleanDeviation(int *whtransform, int n);


// utils.c
int bitcount(unsigned int n);
void printTransformToHex(int *whtransform, int n);
void printBooleanToHex(int *booleanFunction, int n);
void readBooleanInHex(int *booleanFunction, int n);


#endif /* _WH_H_ */
