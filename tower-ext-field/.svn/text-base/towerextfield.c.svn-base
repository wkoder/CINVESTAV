/*
 * towerextfield.c
 *
 *  Created on: Dec 5, 2010
 *      Author: Viridiana Ponce, Moises Osorio
 */

#include "towerextfield.h"

#define MAX_SIZE 256

fp_t P;
int T[MAX_SIZE];
int LEN_T = MAX_SIZE;
int T2[MAX_SIZE];
int LEN_T2 = MAX_SIZE;
int T3[MAX_SIZE];
int LEN_T3 = MAX_SIZE;
fp2_t GAMMA[3][5];

fp_t ZERO;
fp_t ONE;
fp2_t EPSILON;

fp_t s_2;
fp_t t_2;
fp_t d0_2;
fp_t d1_2;
fp_t d2_2;
fp_t t0_8;
fp_t t1_8;
fp_t tmp_8;
fp_t t_3;
fp_t d0_3;
fp_t d1_3;

fp2_t tmp_12;
fp2_t t0_9;
fp2_t t1_9;
fp2_t t0_13;
fp2_t t1_13;
fp2_t t2_13;
fp2_t tmp_13;
fp2_t tmpa_13;
fp2_t tmpb_13;
fp2_t e_13;
fp2_t c0_13;
fp2_t c1_13;
fp2_t tmp_16;
fp2_t c1_16;
fp2_t c2_16;
fp2_t c3_16;
fp2_t c4_16;
fp2_t c5_16;
fp2_t t0_17;
fp2_t t1_17;
fp2_t t2_17;
fp2_t t3_17;
fp2_t t4_17;
fp2_t t5_17;
fp2_t tmp_17;
fp2_t c0_17;
fp2_t c1_17;
fp2_t c2_17;
fp2_t t6_17;
fp6_t t0_20;
fp6_t t1_20;
fp6_t tmp_20;
fp6_t tmpa_20;
fp6_t tmpb_20;
fp6_t tmp_22;
fp6_t c3_22;
fp6_t c2_22;
fp6_t t0_23;
fp6_t t1_23;
fp6_t tmp_23;
fp12_t cc_25;
fp12_t ac_25;
fp2_t t2_28;
fp2_t t3_28;
fp2_t t4_28;
fp2_t t5_28;
fp2_t t6_28;
fp2_t t2_30;
fp2_t t3_30;
fp2_t t4_30;
fp2_t t5_30;
fp2_t t6_30;
fp12_t f_31;
fp12_t f1_31;
fp12_t f2_31;
fp12_t tmp_31;
fp12_t ft1_31;
fp12_t ft2_31;
fp12_t ft3_31;
fp12_t fp1_31;
fp12_t fp2_31;
fp12_t fp3_31;
fp12_t y0_31;
fp12_t y1_31;
fp12_t y2_31;
fp12_t y3_31;
fp12_t y4_31;
fp12_t y5_31;
fp12_t y6_31;
fp12_t t0_31;
fp12_t t1_31;
fp2_t c0_2;

void initFp(fp_t a)
{
	mpz_init2(a, 256);
}

void initFp2(fp2_t a)
{
	initFp(a[0]);
	initFp(a[1]);
}

void initFp6(fp6_t a)
{
	initFp2(a[0]);
	initFp2(a[1]);
	initFp2(a[2]);
}

void initFp12(fp12_t a)
{
	initFp6(a[0]);
	initFp6(a[1]);
}


/** Algorithms for Fp **/

void addFp(fp_t c, fp_t a, fp_t b)
{
	mpz_add(c, a, b);
}

void subFp(fp_t c, fp_t a, fp_t b)
{
	mpz_sub(c, a, b);
}

void multFp(fp_t c, fp_t a, fp_t b)
{
	mpz_mul(c, a, b);
}

void multConstantFp(fp_t c, fp_t a, long int b)
{
	mpz_mul_si(c, a, b);
}

void multBeta(fp_t c, fp_t a)
{
	multConstantFp(c, a, -5);
}

void sqrFp(fp_t b, fp_t a)
{
	multFp(b, a, a);
}

void invFp(fp_t b, fp_t a)
{
	mpz_invert(b, a, P);
}

void modFp(fp_t b, fp_t a)
{
	mpz_mod(b, a, P);
}

void setFp(fp_t c, fp_t a)
{
	mpz_set(c, a);
}


/** Algorithms for Fp2 **/

// Algorithm 5
void addFp2(fp2_t c, fp2_t a, fp2_t b)
{
	addFp(c[0], a[0], b[0]);
	addFp(c[1], a[1], b[1]);

	modFp(c[0], c[0]);
	modFp(c[1], c[1]);
}

// Algorithm 6
void subFp2(fp2_t c, fp2_t a, fp2_t b)
{
	subFp(c[0], a[0], b[0]);
	subFp(c[1], a[1], b[1]);

	modFp(c[0], c[0]);
	modFp(c[1], c[1]);
}

// Algorithm 2
void multFp2(fp2_t c, fp2_t a, fp2_t b)
{
	addFp(s_2, a[0], a[1]);
	addFp(t_2, b[0], b[1]);
	multFp(d0_2, s_2, t_2);
	multFp(d1_2, a[0], b[0]);
	multFp(d2_2, a[1], b[1]);
	subFp(d0_2, d0_2, d1_2);
	subFp(d0_2, d0_2, d2_2);
	multConstantFp(d2_2, d2_2, 5);
	subFp(d1_2, d1_2, d2_2);

	modFp(c[1], d0_2);
	modFp(c[0], d1_2);
}

// Algorithm 8
void invFp2(fp2_t c, fp2_t a)
{
	sqrFp(t0_8, a[0]);
	sqrFp(t1_8, a[1]);
	multBeta(tmp_8, t1_8);
	subFp(t0_8, t0_8, tmp_8);
	invFp(t1_8, t0_8);
	multFp(c[0], a[0], t1_8);
	multFp(tmp_8, a[1], t1_8);
	multConstantFp(c[1], tmp_8, -1);

	modFp(c[0], c[0]);
	modFp(c[1], c[1]);
}

// Algorithm 3
void sqrFp2(fp2_t c, fp2_t a)
{
	addFp(t_3, a[1], a[1]);
	multFp(d1_3, t_3, a[0]);
	addFp(t_3, a[0], P);
	subFp(t_3, t_3, a[1]);
	multConstantFp(c[1], a[1], 5);
	addFp(c[1], c[1], a[0]);
	multFp(d0_3, t_3, c[1]);
	modFp(c[1], d1_3);

	addFp(d1_3, d1_3, d1_3);
	subFp(d0_3, d0_3, d1_3);
	modFp(c[0], d0_3);
}

void multConstantFp2(fp2_t c, fp2_t a, long int b)
{
	multConstantFp(c[0], a[0], b);
	multConstantFp(c[1], a[1], b);

	modFp(c[0], c[0]);
	modFp(c[1], c[1]);
}

void multEpsilon(fp2_t c, fp2_t a)
{
	multFp2(c, a, EPSILON);
}

void setFp2(fp2_t c, fp2_t a)
{
	setFp(c[0], a[0]);
	setFp(c[1], a[1]);
}

void conjugateFp2(fp2_t c, fp2_t a)
{
	setFp(c[0], a[0]);
	multConstantFp(c[1], a[1], -1);
	modFp(c[1], c[1]);
}

void expFp2(fp2_t c, fp2_t a, fp_t e) {
	int i;

	setFp2(c0_2, a);
	for (i = mpz_sizeinbase(e, 2)-2; i >= 0; i--) {
		sqrFp2(c0_2, c0_2);
		if (mpz_tstbit(e, i))
			multFp2(c0_2, c0_2, a);
	}

	setFp2(c, c0_2);
}


/** Algorithms for Fp4 **/

// Algorithm 9
void sqrFp4(fp4_t c, fp4_t a)
{
	sqrFp2(t0_9, a[0]);
	sqrFp2(t1_9, a[1]);

	addFp2(c[1], a[0], a[1]);

	multEpsilon(c[0], t1_9);
	addFp2(c[0], c[0], t0_9);

	sqrFp2(c[1], c[1]);
	subFp2(c[1], c[1], t0_9);
	subFp2(c[1], c[1], t1_9);
}


/** Algorithms for Fp6 **/

// Algorithm 10
void addFp6(fp6_t c, fp6_t a, fp6_t b)
{
	addFp2(c[0], a[0], b[0]);
	addFp2(c[1], a[1], b[1]);
	addFp2(c[2], a[2], b[2]);
}

// Algorithm 11
void subFp6(fp6_t c, fp6_t a, fp6_t b)
{
	subFp2(c[0], a[0], b[0]);
	subFp2(c[1], a[1], b[1]);
	subFp2(c[2], a[2], b[2]);
}

// Algorithm 12
void multGAMMA(fp6_t c, fp6_t a)
{
	setFp2(tmp_12, a[0]);
	multEpsilon(c[0], a[2]);

	setFp2(c[2], a[1]);
	setFp2(c[1], tmp_12);
}

// Algorithm 13
void multFp6(fp6_t c, fp6_t a, fp6_t b)
{
	multFp2(t0_13, a[0], b[0]);
	multFp2(t1_13, a[1], b[1]);
	multFp2(t2_13, a[2], b[2]);

	addFp2(tmpa_13, a[1], a[2]);
	addFp2(tmpb_13, b[1], b[2]);
	multFp2(tmp_13, tmpa_13, tmpb_13);
	subFp2(tmp_13, tmp_13, t1_13);
	subFp2(tmp_13, tmp_13, t2_13);
	multEpsilon(tmp_13, tmp_13);
	addFp2(c0_13, tmp_13, t0_13);

	addFp2(tmpa_13, a[0], a[1]);
	addFp2(tmpb_13, b[0], b[1]);
	multFp2(tmp_13, tmpa_13, tmpb_13);
	subFp2(tmp_13, tmp_13, t0_13);
	subFp2(tmp_13, tmp_13, t1_13);
	multEpsilon(e_13, t2_13);
	addFp2(c1_13, tmp_13, e_13);

	addFp2(tmpa_13, a[0], a[2]);
	addFp2(tmpb_13, b[0], b[2]);
	multFp2(tmp_13, tmpa_13, tmpb_13);
	subFp2(tmp_13, tmp_13, t0_13);
	subFp2(tmp_13, tmp_13, t2_13);

	setFp2(c[0], c0_13);
	setFp2(c[1], c1_13);
	addFp2(c[2], tmp_13, t1_13);
}

// Algorithm 16
void sqrFp6(fp6_t c, fp6_t a)
{
	multFp2(tmp_16, a[0], a[1]);
	addFp2(c4_16, tmp_16, tmp_16);

	sqrFp2(c5_16, a[2]);

	multEpsilon(tmp_16, c5_16);
	addFp2(c1_16, tmp_16, c4_16);

	subFp2(c2_16, c4_16, c5_16);
	sqrFp2(c3_16, a[0]);

	subFp2(tmp_16, a[0], a[1]);
	addFp2(c4_16, tmp_16, a[2]);

	multFp2(tmp_16, a[1], a[2]);
	addFp2(c5_16, tmp_16, tmp_16);

	sqrFp2(c4_16, c4_16);

	setFp2(c[1], c1_16);

	multEpsilon(tmp_16, c5_16);
	addFp2(c[0], tmp_16, c3_16);

	addFp2(tmp_16, c2_16, c4_16);
	addFp2(tmp_16, tmp_16, c5_16);
	subFp2(c[2], tmp_16, c3_16);
}

// Algorithm 17
void invFp6(fp6_t c, fp6_t a)
{
	sqrFp2(t0_17, a[0]);
	sqrFp2(t1_17, a[1]);
	sqrFp2(t2_17, a[2]);
	multFp2(t3_17, a[0], a[1]);
	multFp2(t4_17, a[0], a[2]);
	multFp2(t5_17, a[1], a[2]);

	multEpsilon(tmp_17, t5_17);
	subFp2(c0_17, t0_17, tmp_17);

	multEpsilon(tmp_17, t2_17);
	subFp2(c1_17, tmp_17, t3_17);

	subFp2(c2_17, t1_17, t4_17);
	multFp2(t6_17, a[0], c0_17);

	multEpsilon(tmp_17, a[2]);
	multFp2(tmp_17, tmp_17, c1_17);
	addFp2(t6_17, t6_17, tmp_17);

	multEpsilon(tmp_17, a[1]);
	multFp2(tmp_17, tmp_17, c2_17);
	addFp2(t6_17, t6_17, tmp_17);

	invFp2(t6_17, t6_17);

	multFp2(c[0], c0_17, t6_17);
	multFp2(c[1], c1_17, t6_17);
	multFp2(c[2], c2_17, t6_17);
}

void multConstantFp6(fp6_t c, fp6_t a, long int b)
{
	multConstantFp2(c[0], a[0], b);
	multConstantFp2(c[1], a[1], b);
	multConstantFp2(c[2], a[2], b);
}

void setFp6(fp6_t c, fp6_t a)
{
	setFp2(c[0], a[0]);
	setFp2(c[1], a[1]);
	setFp2(c[2], a[2]);
}


/** Algorithms for Fp12 **/

// Algorithm 18
void addFp12(fp12_t c, fp12_t a, fp12_t b)
{
	addFp6(c[0], a[0], b[0]);
	addFp6(c[1], a[1], b[1]);
}

// Algorithm 19
void subFp12(fp12_t c, fp12_t a, fp12_t b)
{
	subFp6(c[0], a[0], b[0]);
	subFp6(c[1], a[1], b[1]);
}

// Algorithm 20
void multFp12(fp12_t c, fp12_t a, fp12_t b)
{
	multFp6(t0_20, a[0], b[0]);
	multFp6(t1_20, a[1], b[1]);

	addFp6(tmpa_20, a[0], a[1]);
	addFp6(tmpb_20, b[0], b[1]);

	multGAMMA(tmp_20, t1_20);
	addFp6(c[0], t0_20, tmp_20);

	multFp6(tmp_20, tmpa_20, tmpb_20);
	subFp6(tmp_20, tmp_20, t0_20);
	subFp6(c[1], tmp_20, t1_20);
}

// Algorithm 22
void sqrFp12(fp12_t c, fp12_t a)
{
	multGAMMA(tmp_22, a[1]);
	subFp6(c3_22, a[0], tmp_22);

	multFp6(c2_22, a[0], a[1]);

	subFp6(c[0], a[0], a[1]);
	multFp6(tmp_22, c[0], c3_22);
	addFp6(c[0], tmp_22, c2_22);

	addFp6(c[1], c2_22, c2_22);
	multGAMMA(c2_22, c2_22);
	addFp6(c[0], c[0], c2_22);
}

// Algorithm 23
void invFp12(fp12_t c, fp12_t a)
{
	sqrFp6(t0_23, a[0]);
	sqrFp6(t1_23, a[1]);
	multGAMMA(tmp_23, t1_23);
	subFp6(t0_23, t0_23, tmp_23);
	invFp6(t1_23, t0_23);
	multFp6(c[0], a[0], t1_23);
	multFp6(c[1], a[1], t1_23);
	multConstantFp6(c[1], c[1], -1);
}

/*
// Algorithm 24
void sqrFp12(fp12_t c, fp12_t f)
{
	fp4_t x;
	fp4_t t0011;
	fp4_t t1201;
	fp4_t t02aux;
	fp2_t tmpa;
	fp2_t tmpb;

	x[0] = f[0][0];
	x[1] = f[1][1];
	sqrFp4(t0011, x);

	x[0] = f[1][0];
	x[1] = f[0][2];
	sqrFp4(t1201, x);

	x[0] = f[0][1];
	x[1] = f[1][2];
	sqrFp4(t02aux, x);

	multEpsilon(t10, t02aux[1]);

	multConstantFp2(tmpa, -2, f[0][0]);
	multConstantFp2(tmpb, 3, t0011[0]);
	addFp2(c[0][0], tmpa, tmpb);

	multConstantFp2(tmpa, -2, f[0][1]);
	multConstantFp2(tmpb, 3, t1201[1]);
	addFp2(c[0][1], tmpa, tmpb);

	multConstantFp2(tmpa, -2, f[0][2]);
	multConstantFp2(tmpb, 3, t02aux[0]);
	addFp2(c[0][2], tmpa, tmpb);

	multConstantFp2(tmpa, 2, f[1][0]);
	multConstantFp2(tmpb, 3, t10);
	addFp2(c[1][0], tmpa, tmpb);

	multConstantFp2(tmpa, 2, f[1][1]);
	multConstantFp2(tmpb, 3, t0011[1]);
	addFp2(c[1][1], tmpa, tmpb);

	multConstantFp2(tmpa, 2, f[1][2]);
	multConstantFp2(tmpb, 3, t1201[0]);
	addFp2(c[1][2], tmpa, tmpb);
}
*/

void setFp12(fp12_t c, fp12_t a)
{
	setFp6(c[0], a[0]);
	setFp6(c[1], a[1]);
}

// Algorithm 25
void expFp12(fp12_t c, fp12_t a, int *e, int L)
{
	int i;

	setFp12(cc_25, a);
	invFp12(ac_25, a);
	for (i = L-2; i >= 0; i--) {
		sqrFp12(cc_25, cc_25);
		if (e[i]) {
			if(e[i] > 0)
				multFp12(cc_25, cc_25, a);
			else
				multFp12(cc_25, cc_25, ac_25);
		}
	}

	setFp12(c, cc_25);
}

void conjugateFp12(fp12_t c, fp12_t a)
{
	setFp6(c[0], a[0]);
	multConstantFp6(c[1], a[1], -1);
}


/** Algorithms for Final exponentiation **/

// Algorithm 28
void frobeniusP(fp12_t c, fp12_t f)
{
	conjugateFp2(c[0][0], f[0][0]);
	conjugateFp2(t2_28, f[1][0]);
	conjugateFp2(t3_28, f[0][1]);
	conjugateFp2(t4_28, f[1][1]);
	conjugateFp2(t5_28, f[0][2]);
	conjugateFp2(t6_28, f[1][2]);

	multFp2(c[1][0], t2_28, GAMMA[0][0]);
	multFp2(c[0][1], t3_28, GAMMA[0][1]);
	multFp2(c[1][1], t4_28, GAMMA[0][2]);
	multFp2(c[0][2], t5_28, GAMMA[0][3]);
	multFp2(c[1][2], t6_28, GAMMA[0][4]);
}

// Algorithm 29
void frobeniusP2(fp12_t c, fp12_t f)
{
	setFp2(c[0][0], f[0][0]);
	multFp2(c[1][0], f[1][0], GAMMA[1][0]);
	multFp2(c[0][1], f[0][1], GAMMA[1][1]);
	multFp2(c[1][1], f[1][1], GAMMA[1][2]);
	multFp2(c[0][2], f[0][2], GAMMA[1][3]);
	multFp2(c[1][2], f[1][2], GAMMA[1][4]);
}

// ALgorithm 30
void frobeniusP3(fp12_t c, fp12_t f)
{
	conjugateFp2(c[0][0], f[0][0]);
	conjugateFp2(t2_30, f[1][0]);
	conjugateFp2(t3_30, f[0][1]);
	conjugateFp2(t4_30, f[1][1]);
	conjugateFp2(t5_30, f[0][2]);
	conjugateFp2(t6_30, f[1][2]);

	multFp2(c[1][0], t2_30, GAMMA[2][0]);
	multFp2(c[0][1], t3_30, GAMMA[2][1]);
	multFp2(c[1][1], t4_30, GAMMA[2][2]);
	multFp2(c[0][2], t5_30, GAMMA[2][3]);
	multFp2(c[1][2], t6_30, GAMMA[2][4]);
}

// Algorithm 31
void finalExponentiation(fp12_t c, fp12_t f0)
{
	setFp12(f_31, f0);
	conjugateFp12(f1_31, f_31);
	invFp12(f2_31, f_31);
	multFp12(f_31, f1_31, f2_31);

	frobeniusP2(tmp_31, f_31);
	multFp12(f_31, f_31, tmp_31);

	expFp12(ft1_31, f_31, T, LEN_T);
	expFp12(ft2_31, f_31, T2, LEN_T2);
	expFp12(ft3_31, f_31, T3, LEN_T3);

	frobeniusP(fp1_31, f_31);
	frobeniusP2(fp2_31, f_31);
	frobeniusP3(fp3_31, f_31);

	multFp12(y0_31, fp1_31, fp2_31);
	multFp12(y0_31, y0_31, fp3_31);
	conjugateFp12(y1_31, f_31);

	frobeniusP2(y2_31, ft2_31);

	frobeniusP(y3_31, ft1_31);
	conjugateFp12(y3_31, y3_31);

	frobeniusP(y4_31, ft2_31);
	multFp12(y4_31, y4_31, ft1_31);
	conjugateFp12(y4_31, y4_31);

	conjugateFp12(y5_31, ft2_31);

	frobeniusP(y6_31, ft3_31);
	multFp12(y6_31, y6_31, ft3_31);
	conjugateFp12(y6_31, y6_31);

	sqrFp12(t0_31, y6_31);
	multFp12(t0_31, t0_31, y4_31);
	multFp12(t0_31, t0_31, y5_31);

	multFp12(t1_31, y3_31, y5_31);
	multFp12(t1_31, t1_31, t0_31);

	multFp12(t0_31, t0_31, y2_31);

	sqrFp12(t1_31, t1_31);
	multFp12(t1_31, t1_31, t0_31);
	sqrFp12(t1_31, t1_31);

	multFp12(t0_31, t1_31, y1_31);

	multFp12(t1_31, t1_31, y0_31);

	sqrFp12(t0_31, t0_31);

	multFp12(c, t0_31, t1_31);
}

// Library initialization

void init(fp_t p, int *tt1, int lentt1, int *tt2, int lentt2, int *tt3, int lentt3)
{
	int i, j;
	fp_t exp;
	fp2_t tmp;

	initFp(P);
	mpz_init_set_ui(ZERO, 0);
	mpz_init_set_ui(ONE, 1);
	initFp2(EPSILON);
	setFp(EPSILON[0], ZERO);
	setFp(EPSILON[1], ONE);

	setFp(P, p);

	LEN_T = lentt1;
	for (i = 0; i < LEN_T; i++)
		T[i] = tt1[LEN_T - 1 - i];
	LEN_T2 = lentt2;
	for (i = 0; i < LEN_T2; i++)
		T2[i] = tt2[LEN_T2 - 1 - i];
	LEN_T3 = lentt3;
	for (i = 0; i < LEN_T3; i++)
		T3[i] = tt3[LEN_T3 - 1 - i];

	// Initialize all temporal variables
	initFp(s_2);
	initFp(t_2);
	initFp(d0_2);
	initFp(d1_2);
	initFp(d2_2);
	initFp(t0_8);
	initFp(t1_8);
	initFp(tmp_8);
	initFp(t_3);
	initFp(d0_3);
	initFp(d1_3);

	initFp2(tmp_12);
	initFp2(t0_9);
	initFp2(t1_9);
	initFp2(t0_13);
	initFp2(t1_13);
	initFp2(t2_13);
	initFp2(tmp_13);
	initFp2(tmpa_13);
	initFp2(tmpb_13);
	initFp2(e_13);
	initFp2(c0_13);
	initFp2(c1_13);
	initFp2(tmp_16);
	initFp2(c1_16);
	initFp2(c2_16);
	initFp2(c3_16);
	initFp2(c4_16);
	initFp2(c5_16);
	initFp2(t0_17);
	initFp2(t1_17);
	initFp2(t2_17);
	initFp2(t3_17);
	initFp2(t4_17);
	initFp2(t5_17);
	initFp2(tmp_17);
	initFp2(c0_17);
	initFp2(c1_17);
	initFp2(c2_17);
	initFp2(t6_17);
	initFp6(t0_20);
	initFp6(t1_20);
	initFp6(tmp_20);
	initFp6(tmpa_20);
	initFp6(tmpb_20);
	initFp6(tmp_22);
	initFp6(c3_22);
	initFp6(c2_22);
	initFp6(t0_23);
	initFp6(t1_23);
	initFp6(tmp_23);
	initFp12(cc_25);
	initFp12(ac_25);
	initFp2(t2_28);
	initFp2(t3_28);
	initFp2(t4_28);
	initFp2(t5_28);
	initFp2(t6_28);
	initFp2(t2_30);
	initFp2(t3_30);
	initFp2(t4_30);
	initFp2(t5_30);
	initFp2(t6_30);
	initFp12(f_31);
	initFp12(f1_31);
	initFp12(f2_31);
	initFp12(tmp_31);
	initFp12(ft1_31);
	initFp12(ft2_31);
	initFp12(ft3_31);
	initFp12(fp1_31);
	initFp12(fp2_31);
	initFp12(fp3_31);
	initFp12(y0_31);
	initFp12(y1_31);
	initFp12(y2_31);
	initFp12(y3_31);
	initFp12(y4_31);
	initFp12(y5_31);
	initFp12(y6_31);
	initFp12(t0_31);
	initFp12(t1_31);
	initFp2(c0_2);

	// Calculate GAMMA constants
	for (i = 0; i < 3; i++)
		for (j = 0; j < 5; j++)
			initFp2(GAMMA[i][j]);

	initFp(exp);
	subFp(exp, p, ONE);
	mpz_div_ui(exp, exp, 6); // exp = (p-1)/6

	expFp2(GAMMA[0][0], EPSILON, exp);
	for (i = 1; i < 5; i++)
		multFp2(GAMMA[0][i], GAMMA[0][i-1], GAMMA[0][0]);

	initFp2(tmp);
	for (i = 0; i < 5; i++) {
		conjugateFp2(tmp, GAMMA[0][i]);
		multFp2(GAMMA[1][i], GAMMA[0][i], tmp);
	}

	for (i = 0; i < 5; i++)
		multFp2(GAMMA[2][i], GAMMA[0][i], GAMMA[1][i]);
}

void readFp(fp_t a)
{
	mpz_inp_str(a, 0, 16);
}

void readFp2(fp2_t a)
{
	readFp(a[0]);
	readFp(a[1]);
}

void readFp6(fp6_t a)
{
	readFp2(a[0]);
	readFp2(a[1]);
	readFp2(a[2]);
}

void readFp12(fp12_t a)
{
	readFp6(a[0]);
	readFp6(a[1]);
}

void printFp(fp_t a)
{
	mpz_out_str(0, 16, a);
}

void printFp2(fp2_t a)
{
	printFp(a[0]);
	printf("\n");
	printFp(a[1]);
}

void printFp6(fp6_t a)
{
	printFp2(a[0]);
	printf("\n");
	printFp2(a[1]);
	printf("\n");
	printFp2(a[2]);
}

void printFp12(fp12_t a)
{
	printFp6(a[0]);
	printf("\n");
	printFp6(a[1]);
}
