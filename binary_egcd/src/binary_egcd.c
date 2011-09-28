/*
 ============================================================================
 Name        : binary_egcd.c
 Author      : Moises Osorio
 Description : Binary Extended GCD algorithm
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

//#define TEST
#define BASE 16

long long getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000 + tv.tv_usec;
}

// Given x and y, calculates ax + by = v where v = GCD(x,y)
void egcd(mpz_t xx, mpz_t yy, mpz_t a, mpz_t b, mpz_t v) {
	mpz_t g, u, A, B, C, D, x, y;

	mpz_init_set(x, xx);
	mpz_init_set(y, yy);
	mpz_init_set_ui(g, 1);

	while (mpz_even_p(x) && mpz_even_p(y)) { // x%2 = y%2 = 0
		mpz_divexact_ui(x, x, 2);
		mpz_divexact_ui(y, y, 2);
		mpz_mul_ui(g, g, 2);
	}

	mpz_init_set(u, x); // u = x
	mpz_set(v, y); // v = y
	mpz_init_set_ui(A, 1);
	mpz_init_set_ui(B, 0);
	mpz_init_set_ui(C, 0);
	mpz_init_set_ui(D, 1);

	do {
		while (mpz_even_p(u)) { // u%2 = 0
			mpz_divexact_ui(u, u, 2);
			if (mpz_even_p(A) && mpz_even_p(B)) { // A%2 = B%2 = 0
				mpz_divexact_ui(A, A, 2); // A = A/2
				mpz_divexact_ui(B, B, 2); // B = B/2
			} else {
				mpz_add(A, A, y);
				mpz_cdiv_q_ui(A, A, 2); // A = (A+y)/2
				mpz_sub(B, B, x);
				mpz_cdiv_q_ui(B, B, 2); // B = (B-x)/2
			}
		}

		while (mpz_even_p(v)) { // v%2 = 0
			mpz_divexact_ui(v, v, 2);
			if (mpz_even_p(C) && mpz_even_p(D)) { // C%2 = D%2 = 0
				mpz_divexact_ui(C, C, 2); // C = C/2
				mpz_divexact_ui(D, D, 2); // D = D/2
			} else {
				mpz_add(C, C, y);
				mpz_cdiv_q_ui(C, C, 2); // C = (C+y)/2
				mpz_sub(D, D, x);
				mpz_cdiv_q_ui(D, D, 2); // D = (D-x)/2
			}
		}

		if (mpz_cmp(u, v) >= 0) { // u >= v
			mpz_sub(u, u, v); // u = u-v
			mpz_sub(A, A, C); // A = A-C
			mpz_sub(B, B, D); // B = B-D
		} else {
			mpz_sub(v, v, u); // v = v-u
			mpz_sub(C, C, A); // C = C-A
			mpz_sub(D, D, B); // D = D-B
		}
	} while (mpz_cmp_ui(u, 0) != 0); // u != 0

	mpz_set(a, C); // a = C
	mpz_set(b, D); // b = D
	mpz_mul(v, v, g); // v = v*g

	// Release memory
	mpz_clear(g);
	mpz_clear(u);
	mpz_clear(A);
	mpz_clear(B);
	mpz_clear(C);
	mpz_clear(D);
	mpz_clear(x);
	mpz_clear(y);
}

long long measureTime(mpz_t x, mpz_t y, mpz_t a, mpz_t b, mpz_t v)
{
	long long start = getTime();
	egcd(x, y, a, b, v);
	long long end = getTime();

	return end - start;
}

long long testPerformance(long long tests, int bit_count)
{
	gmp_randstate_t RAND;
	gmp_randinit_default(RAND);
	gmp_randseed_ui(RAND, getTime());

	mpz_t base;
	mpz_init_set_ui(base, 1);
	mpz_mul_2exp(base, base, bit_count-1); // base = 2^(bit_count-1)

	mpz_t x, y, a, b, v;
	mpz_init(x);
	mpz_init(y);
	mpz_init(a);
	mpz_init(b);
	mpz_init(v);
	long long time = 0;
	int test;
	for (test = 0; test < tests; test++) {
		mpz_urandomb(a, RAND, bit_count-1);
		mpz_add(a, a, base); // a has bit_count bits
		mpz_urandomb(b, RAND, bit_count-1);
		mpz_add(b, b, base); // b has bit_count bits

		time += measureTime(a, b, x, y, v);
	}

	// Release memory
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(v);
	mpz_clear(base);
	gmp_randclear(RAND);

	return time / tests; // Average
}

int main(void) {
#ifdef TEST
	FILE *fp;
	fp = freopen("binary_egcd_stats.dat", "w", stdout);

	long long bit_count;
	for (bit_count = 1; bit_count <= 9; bit_count++) {
		long long time = testPerformance(1000, 1 << bit_count);
		printf("%d %lld\n", 1 << bit_count, time);
	}
	fclose(fp);

	return 0;
#else
	mpz_t x, y, a, b, n, gcd, lcm, a1, b1;
	mpz_init(x);
	mpz_init(y);
	mpz_init(a);
	mpz_init(b);
	mpz_init(n);
	mpz_init(gcd);
	mpz_init(lcm);
	mpz_init(a1);
	mpz_init(b1);

	printf("A: ");
	if (mpz_inp_str(x, NULL, BASE) == 0) {
		printf("ERROR\n");
		return -1;
	}

	printf("B: ");
	if (mpz_inp_str(y, NULL, BASE) == 0) {
		printf("ERROR\n");
		return -2;
	}

	egcd(x, y, a, b, gcd);

	mpz_divexact(lcm, x, gcd);
	mpz_mul(lcm, lcm, y);

	printf("Greatest Common Divisor: ");
	mpz_out_str(NULL, BASE, gcd);
	printf("\nLeast Common Multiple: ");
	mpz_out_str(NULL, BASE, lcm);
	if (mpz_cmp_ui(gcd, 1) == 0) {
		printf("\nMultiplicative inverse of A: ");
		if (mpz_cmp_ui(a, 0) < 0)
			mpz_add(a, a, y);
		mpz_out_str(NULL, BASE, a);

		printf("\nMultiplicative inverse of B: ");
		if (mpz_cmp_ui(b, 0) < 0)
			mpz_add(b, b, x);
		mpz_out_str(NULL, BASE, b);
		printf("\n");
	} else
		printf("\nThere are no multiplicative inverses.\n");

	// Release memory
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(n);
	mpz_clear(gcd);
	mpz_clear(lcm);
	mpz_clear(a1);
	mpz_clear(b1);

	return 0;
#endif
}
