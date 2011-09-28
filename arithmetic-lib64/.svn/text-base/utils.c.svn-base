/*
 * utils.c
 *
 *  Created on: Nov 6, 2010
 *      Author: Viridiana Ponce, Moises Osorio
 */

#include "arithlib64.h"
#include <stdio.h>

#define NIBBLES BIT_LENGTH / 4

char temp[NIBBLES * 10];

int readBigInt(bigint_t a)
{
	int i;
	uint64_t val;

	scanf("%s", temp);
	for (i = 0, val = 0; i < NIBBLES && temp[i] > 0; i++) {
		int x;
		if (temp[i] >= 'a')
			x = temp[i] - 'a' + 10;
		else if (temp[i] >= 'A')
			x = temp[i] - 'A' + 10;
		else
			x = temp[i] - '0';

		val = (val << 4) | x;
		if ((i & 0xF) == 0xF) { // i % 16 == 15
			a[(NIBBLES - i) >> 4] = val; // a[i / 16] = val
			val = 0;
		}
	}

	return i == NIBBLES;
}

void printBigInt(bigint_t a)
{
	int i, j;
	for (i = WORD_LENGTH-1; i >= 0; i--)
		for (j = 0; j < 16; j++)
			printf("%X", (unsigned int)((a[i] >> ((15 - j) << 2)) & 0xF));
}
