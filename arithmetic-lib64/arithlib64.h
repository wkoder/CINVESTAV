/*
 * arithlib64.h
 * Performs arithmetic functions over arbitrary integers using 64-bit length words.
 *
 *  Created on: Nov 6, 2010
 *      Authors: Viridiana Ponce, Moises Osorio
 */

// Number of bits this library supports
#define BIT_LENGTH 256
// Number of words
#define WORD_LENGTH BIT_LENGTH / 64 + (BIT_LENGTH % 64 > 0)

// 64-bit unsigned integer
#define uint64_t unsigned long long
// Big number declaration
typedef __attribute__ ((aligned(16))) uint64_t bigint_t[WORD_LENGTH];

// Arithmetics
void addModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p);
void subtractModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p);
void multClassicBarretModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p);
void multMontgomeryModP(bigint_t r, bigint_t a, bigint_t b, bigint_t p);
void reductionModP192(bigint_t r, bigint_t a);
void reductionModP224(bigint_t r, bigint_t a);
void reductionModP256(bigint_t r, bigint_t a);
void reductionModP384(bigint_t r, bigint_t a);
void reductionModP521(bigint_t r, bigint_t a);
void squareRootModP(bigint_t r, bigint_t a, bigint_t p);
void multTrinomialMod2(bigint_t r, bigint_t a, bigint_t b);
void multPentanomialMod2(bigint_t r, bigint_t a, bigint_t b);
void squareMod2(bigint_t r, bigint_t a);
void squareRootMod2(bigint_t r, bigint_t a);

void expBinaryLR(bigint_t r, bigint_t a);
void expBinaryRL(bigint_t r, bigint_t a);
void expBinarySideChannelProtection(bigint_t r, bigint_t a);
void expFixedWindow(bigint_t r, bigint_t a);
void expSlidingWindow(bigint_t r, bigint_t a);

// Utilities
int readBigInt(bigint_t a);
void printBigInt(bigint_t a);
