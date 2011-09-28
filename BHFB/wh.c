/*
 * wh.c
 *
 *  Created on: Nov 1, 2010
 *      Author: Moises Osorio
 */

#include "wh.h"

int tmp[1 << MAX_N];

void getPolarityForm(int *booleanForm, int *polarityForm, int n)
{
	int i;
	for (i = 0; i < 1 << n; i++)
		polarityForm[i] = booleanForm[i]? -1 : 1;
}

void getBooleanForm(int *polarityForm, int *booleanForm, int n)
{
	int i;
	for (i = 0; i < 1 << n; i++)
		booleanForm[i] = polarityForm[i] > 0? 0 : 1;
}

void walshHadamardTransform(int *booleanFunction, int *whtransform, int n)
{
	int w, x, wx, f;
	for (w = 0; w < (1 << n); w++) {
		whtransform[w] = 0;
		for (x = 0; x < (1 << n); x++) {
			wx = bitcount(w & x) & 1; // dot product of w and x

			wx = wx? -1 : 1;
			f = booleanFunction[x]? -1 : 1;
			whtransform[w] += wx * f;
		}
	}
}

void inverseWalshHadamardTransform(int *whtransform, double* booleanFunction, int n) // Check result is integer
{
	int x, w, wx;
	for (x = 0; x < (1 << n); x++) {
		double px = 0;
		for (w = 0; w < (1 << n); w++) {
			wx = bitcount(w & x) & 1; // dot product of w and x
			px += wx & 1? -whtransform[w] : whtransform[w];
		}
		px /= 1 << n;

		booleanFunction[x] = px;
	}
}

int getNonLinearity(int *whtransform, int n)
{
	int whmax = whtransform[0], i;
	for (i = 0; i < 1 << n; i++)
		if (whmax < whtransform[i])
			whmax = whtransform[i];

	return ((1 << n) - whmax) / 2; // Check is integer division
}

int getCorrelationImmunity(int *whtransform, int n)
{
	unsigned int i;
	for (i = 1; i < n; i++)
		tmp[i] = 1;

	for (i = 1; i < 1 << n; i++)
		tmp[ bitcount(i) ] &= whtransform[i] == 0;

	for (i = 1; i < n; i++)
		if (!tmp[i])
			return i-1;

	return n-1;
}

int getNonLinearityDeviation(int *whtransform, int n, int nl)
{
	int nonLinearity = getNonLinearity(whtransform, n);
	return nonLinearity >= nl? 0 : nl - nonLinearity;
}

int getCorrelationImmunityDeviation(int *whtransform, int n, int m)
{
	unsigned int i;
	int dev = 0;
	for (i = 1; i < 1 << n; i++)
		if (bitcount(i) <= m && dev < abs(whtransform[i])) {
			//printf("traitor: %d %d\n", i, whtransform[i]);
			dev = abs(whtransform[i]);
		}

	return dev;
}

double getBooleanDeviation(int *whtransform, int n) // Check result is integer
{
	double dev = 0;
	int x, w;
	for (x = 0; x < (1 << n); x++) {
		double px = 0; // Inverse Walsh-Hadamard Transform
		for (w = 0; w < (1 << n); w++)
			px += (w*x) & 1? -whtransform[w] : whtransform[w];
		px /= 1 << n;

		double bx = -1;
		if (px > 0)
			bx = 1;

		dev += (px - bx) * (px - bx);
	}

	return dev;
}
