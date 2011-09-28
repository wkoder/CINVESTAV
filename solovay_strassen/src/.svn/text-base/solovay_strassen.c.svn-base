/*
 ============================================================================
 Name        : solovay_strassen.c
 Author      : Moises Osorio
 Description : Solovoy-Streaasen algorithm
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

//#define TEST

#define BASE 16
#define REPETITIONS 50
#define MAX_PRIME 1000000

long long primes[MAX_PRIME+1];
long long primes_count = 0;

long long getTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000 + tv.tv_usec; // Microsecond precision
}

void calculateSmallPrimes() // Sieve of Eratosthenes
{
	int is_prime[MAX_PRIME+1];
	long long i, j;
	for (i = 0; i <= MAX_PRIME; i++)
		is_prime[i] = 1;
	is_prime[0] = is_prime[1] = 0;
	for (i = 4; i <= MAX_PRIME; i += 2)
		is_prime[i] = 0;
	primes[primes_count] = 2;
	primes_count++;
	for (i = 3; i <= MAX_PRIME; i += 2)
		if (is_prime[i]) {
			primes[primes_count] = i;
			primes_count++;

			for (j = i+i; j <= MAX_PRIME; j += i)
				is_prime[j] = 0;
		}
}

int jacobi(mpz_t aa, mpz_t nn) // Generalization of Legendre's symbol.
{
	mpz_t a, n, n2;
	mpz_init_set(a, aa);
	mpz_init_set(n, nn);
	mpz_init(n2);

	if (mpz_divisible_p(a, n))
		return 0; // (0/n) = 0

	int ans = 1;
	if (mpz_cmp_ui(a, 0) < 0) {
		mpz_neg(a, a); // (a/n) = (-a/n)*(-1/n)
		if (mpz_congruent_ui_p(n, 3, 4)) // if n%4 == 3
			ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
	}

	if (mpz_cmp_ui(a, 1) == 0) {
		mpz_clear(a);
		mpz_clear(n);
		mpz_clear(n2);

		return ans; // (1/n) = 1
	}

	while (mpz_cmp_ui(a, 0) != 0) {
		if (mpz_cmp_ui(a, 0) < 0) {
			mpz_neg(a, a); // (a/n) = (-a/n)*(-1/n)
			if (mpz_congruent_ui_p(n, 3, 4)) // if n%4 == 3
				ans = -ans; // (-1/n) = -1 if n = 3 ( mod 4 )
		}

		while (mpz_divisible_ui_p(a, 2)) {
			mpz_divexact_ui(a, a, 2); // a = a/2
			if (mpz_congruent_ui_p(n, 3, 8) || mpz_congruent_ui_p(n, 5, 8)) // n%8==3 || n%8==5
				ans = -ans;
		}

		mpz_swap(a, n); // (a,n) = (n,a)
		if (mpz_congruent_ui_p(a, 3, 4) && mpz_congruent_ui_p(n, 3, 4)) // a%4==3 && n%4==3
			ans = -ans;

		mpz_mod(a, a, n); // because (a/p) = (a%p / p ) and a%pi = (a%n)%pi if n % pi = 0
		mpz_cdiv_q_ui(n2, n, 2);
		if (mpz_cmp(a, n2) > 0) // a > n/2
			mpz_sub(a, a, n); // a = a-n
	}

	int cmp = mpz_cmp_ui(n, 1);
	mpz_clear(a);
	mpz_clear(n);
	mpz_clear(n2);

	if (cmp == 0)
		return ans;
	return 0;
}

int solovay_strassen(mpz_t n, int k)
{
	int i;
	for (i = 0; i < primes_count && mpz_cmp_si(n, primes[i]*primes[i]) >= 0; i++)
		if (mpz_divisible_ui_p(n, primes[i])) // Check if current prime divides n
			return 0;

	if (mpz_cmp_si(n, 2) < 0)
		return 0;
	if (mpz_cmp_si(n, 2) == 0)
		return 1;
	if (mpz_divisible_ui_p(n, 2))
		return 0;

	gmp_randstate_t RAND;
	gmp_randinit_default(RAND);

	mpz_t a, jac, mod, exp, n1;
	mpz_init(a);
	mpz_init(jac);
	mpz_init(mod);
	mpz_init(exp);
	mpz_init(n1);
	mpz_sub_ui(n1, n, 1);
	while (k > 0) {
		k--;
		mpz_urandomm(a, RAND, n1);
		mpz_add_ui(a, a, 1);

		int j = jacobi(a, n);
		if (j == -1) { // jac = n + jac(a,n)
			mpz_sub_ui(jac, n, 1);
		} else if (j == 1)
			mpz_set_si(jac, j);

		mpz_divexact_ui(exp, n1, 2); // exp = (n-1)/2
		mpz_powm(mod, a, exp, n); // mod = a^((n-1)/2) % n
		if (mpz_cmp_ui(jac, 0) == 0 || mpz_cmp(mod, jac) != 0) { // Is it a liar?
			mpz_clear(a);
			mpz_clear(jac);
			mpz_clear(mod);
			mpz_clear(exp);
			mpz_clear(n1);

			return 0;
		}
	}

	mpz_clear(a);
	mpz_clear(jac);
	mpz_clear(mod);
	mpz_clear(exp);
	mpz_clear(n1);

	return 1;
}

long long measureTime(mpz_t n, int repetitions)
{
	long long start = getTime();
	solovay_strassen(n, repetitions);
	long long end = getTime();

	return end - start; // Time in microseconds
}

long long testPerformance(long long tests, int bit_count, int repetitions)
{
	gmp_randstate_t RAND;
	gmp_randinit_default(RAND);
	gmp_randseed_ui(RAND, getTime());

	mpz_t base;
	mpz_init_set_ui(base, 1);
	mpz_mul_2exp(base, base, bit_count-1); // base = 2^(bit_count-1)

	mpz_t n;
	mpz_init(n);
	long long time = 0;
	int test;
	for (test = 0; test < tests; test++) {
		mpz_urandomb(n, RAND, bit_count-1);
		mpz_add(n, n, base); // n has bit_count bits

		time += measureTime(n, repetitions);
	}
	mpz_clear(n);
	mpz_clear(base);
	gmp_randclear(RAND);

	return time / tests; // Average
}

int main(void)
{
	calculateSmallPrimes(); // Calculate primes smaller than 10^6 to speed up primality test.
#ifdef TEST
	FILE *fp;
	fp = freopen("solovay_strassen_stats.dat", "w", stdout);

	long long bit_count, rep;
	for (bit_count = 1; bit_count <= 9; bit_count++) { // Test bit counts of 2, 4, ..., 256, 512
		printf("%d", 1 << bit_count);
		for (rep = 10; rep <= 100; rep += 10) {
			long long time = testPerformance(1000, 1 << bit_count, rep);
			printf(" %lld", time);
		}
		printf("\n");
	}
	fclose(fp);

	return 0;
#else
	mpz_t n;
	mpz_init(n);

	printf("N: ");
	if (mpz_inp_str(n, NULL, BASE) == 0) {
		printf("ERROR\n");
		return -1;
	}

	int probably_prime = solovay_strassen(n, REPETITIONS);
	printf("%s\n", probably_prime? "It's probably prime." : "It's composite.");

	return 0;
#endif
}
