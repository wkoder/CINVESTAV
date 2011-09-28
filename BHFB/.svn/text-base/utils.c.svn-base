/*
 * utils.c
 *
 *  Created on: Nov 1, 2010
 *      Author: Moises Osorio
 */

#include "wh.h"

char tmp[1 << (MAX_N-2)];

int bitcount(unsigned int n)
{
   register unsigned int tmp;
   tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);

   return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}

void printTransformToHex(int *whtransform, int n)
{
	int i;
	for (i = 0; i < 1 << n; i++) {
		printf("%d", whtransform[i]);
		//if (whtransform[i] == 0xfffffff0) {
			printf("(%d) ", i);
		//}
	}
}

void printBooleanToHex(int *booleanFunction, int n)
{
	int i, j, h;
	for (i = 0; i < 1 << n; ) {
		h = 0;
		for (j = 0; j < 4; j++, i++)
			h = (h << 1) | booleanFunction[i];
		if (h < 0 || h >= 16)
			printf("PANIC with hexa!\n");
		printf("%x", h);
	}
}

void readBooleanInHex(int *booleanFunction, int n)
{
	int i, j, h, p;
	char ch;
	for (i = 0, p = 0; i < 1 << (n-2); i++) {
		scanf("%c", &ch);
		if (ch >= 'a')
			h = ch - 'a' + 10;
		else if (ch >= 'A')
			h = ch - 'A' + 10;
		else
			h = ch - '0';

		if (h < 0 || h >= 16)
			printf("PANIC with hexa!\n");

		for (j = 0; j < 4; j++, p++)
			booleanFunction[p] = (h >> (3 - j)) & 1;
	}
}
