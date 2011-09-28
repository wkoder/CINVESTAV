/*
 * testarithlib64.c
 *
 *  Created on: Nov 6, 2010
 *      Author: Viridiana Ponce, Moises Osorio
 */

#include "arithlib64.h"

int main()
{
	bigint_t a, b, c, p;
	readBigInt(a);
	readBigInt(b);

	addModP(c, a, b, p);

	printBigInt(c);

	return 0;
}
