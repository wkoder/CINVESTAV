/*
 * arithlib64.h
 * Performs arithmetic functions over arbitrary integers using 64-bit length words.
 *
 *  Created on: Nov 6, 2010
 *      Authors: Viridiana Ponce, Moises Osorio
 */

//#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#include <string.h>
#include <stdio.h>
#include "arithlib64.h"

#define LOAD(x, a) x = _mm_load_si128((__m128i *) (a))
#define ADD(x, a, b) x = _mm_add_epi64(a, b)
#define STORE(x, r) _mm_store_si128((__m128i *) (x), r)

#define ADD256(c, a, b, carry) \
    asm ("movq %5, %0 \n\t" \
		 "addq %9, %0 \n\t" \
		 "movq %6, %1 \n\t" \
		 "adcq %10, %1 \n\t" \
		 "movq %7, %2 \n\t" \
		 "adcq %11, %2 \n\t" \
		 "movq %8, %3 \n\t" \
		 "adcq %12, %3 \n\t" \
		 "adcq $0x0, %4 \n\t" \
		: "+r"(*(c)),"+r"(*(c + 1)),"+r"(*(c + 2)),"+r"(*(c + 3)),"+r"(carry) \
		: "r"(*(a)),"r"(*(a + 1)),"r"(*(a + 2)),"r"(*(a + 3)),"r"(*(b)),"r"(*(b + 1)),"r"(*(b + 2)),"r"(*(b + 3)) : "cc")

#define SUB256(c, a, b, carry) \
    asm ("movq %5, %0 \n\t" \
		 "subq %9, %0 \n\t" \
		 "movq %6, %1 \n\t" \
		 "sbc %10, %1 \n\t" \
		 "movq %7, %2 \n\t" \
		 "sbc %11, %2 \n\t" \
		 "movq %8, %3 \n\t" \
		 "sbc %12, %3 \n\t" \
		 "adcq $0x0, %4 \n\t" \
		: "+r"(*(c)),"+r"(*(c + 1)),"+r"(*(c + 2)),"+r"(*(c + 3)),"+r"(carry) \
		: "r"(*(a)),"r"(*(a + 1)),"r"(*(a + 2)),"r"(*(a + 3)),"r"(*(b)),"r"(*(b + 1)),"r"(*(b + 2)),"r"(*(b + 3)) : "cc")

void addModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p)
{
#if WORD_LENGTH != 4
#error "Addition not supported for this number of words."
#endif
	uint64_t carry = 0;
	//ADD256(r, a, b, carry);
	if (carry) {
		//SUB256(r, r, p, carry);
	} else {
		int i, cmp = 1;
		for (i = WORD_LENGTH-1; i >= 0 && cmp; i--) {
			if (r[i] > p[i])
				cmp = 0;
			else if (r[i] < p[i])
				break;
		}

		if (cmp)
			;//SUB256(r, r, p, carry);
	}
}

void subtractModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p)
{
#if WORD_LENGTH != 4
#error "Addition not supported for this number of words."
#endif
	uint64_t carry = 0;
	//SUB256(r, a, b, carry);
	if (carry) {
		//ADD256(r, r, p, carry);
	}
}
