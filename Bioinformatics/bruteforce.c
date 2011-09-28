/*
 * bruteforce.c
 *
 *  Created on: Jun 8, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1001
#define ALPHA_SIZE 26
#define ALPHA_BASE 'a'
#define INF 1<<30

char string[MAX_SIZE];
char suffix[MAX_SIZE];

int main(int argc, char **argv) {
	char s2[MAX_SIZE];
	int i, j, k, n, minsize;
	char *match;
	while (scanf("%s", string) != EOF) {
		n = strlen(string);
		minsize = INF;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n-i && j+1 <= minsize; j++) {
				s2[j] = string[i+j];
				s2[j+1] = 0;
				if (j+1 == minsize && strcmp(s2, suffix) >= 0)
					continue;
				
				match = strstr(string, s2);
//				printf("match at %s of %s\n", match, s2);
				match = strstr(match+1, s2);
				if (match == NULL) {
					minsize = j+1;
					for (k = 0; k <= j+1; k++)
						suffix[k] = s2[k];
				}
			}
		}
		
		printf("%s\n", suffix);
	}
	
	return EXIT_SUCCESS;
}
