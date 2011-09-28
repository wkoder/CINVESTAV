/*
 * suffixarray.c
 *
 *  Created on: Jun 8, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100100
#define ALPHA_SIZE 256
#define MAX_DEPTH 10
#define FIRST_LEXICO 0

#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

int B[MAX_DEPTH][ALPHA_SIZE+1];
unsigned char T[MAX_DEPTH][MAX_SIZE / 8 + 1];
unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

// find the start or end of each bucket
void getBuckets(unsigned char *s, int *bkt, int n, int K, int cs, int end) {
	int i, sum = 0;
	for (i = 0; i <= K; i++)
		bkt[i] = 0; // clear all buckets
	for (i = 0; i < n; i++)
		bkt[chr(i)]++; // compute the size of each bucket
	for (i = 0; i <= K; i++) {
		sum += bkt[i];
		bkt[i] = end ? sum : sum - bkt[i];
	}
}

// compute SAl
void induceSAl(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n,
		int K, int cs, int end) {
	int i, j;
	getBuckets(s, bkt, n, K, cs, end); // find starts of buckets
	for (i = 0; i < n; i++) {
		j = SA[i] - 1;
		if (j >= 0 && !tget(j))
			SA[bkt[chr(j)]++] = j;
	}
}

// compute SAs
void induceSAs(unsigned char *t, int *SA, unsigned char *s, int *bkt, int n,
		int K, int cs, int end) {
	int i, j;
	getBuckets(s, bkt, n, K, cs, end); // find ends of buckets
	for (i = n - 1; i >= 0; i--) {
		j = SA[i] - 1;
		if (j >= 0 && tget(j))
			SA[--bkt[chr(j)]] = j;
	}
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n-1]=0 (the sentinel!), n>=2
// use a working space (excluding s and SA) of at most 2.25n+O(1) for a constant alphabet
void SA_IS(unsigned char *s, int *SA, int n, int K, int cs, int depth) {
	int i, j, n1, name, prev, pos, diff, d;
	int *SA1, *s1, *bkt;
	unsigned char *t;
	t = T[depth];
	bkt = B[depth];
	
	// Classify the type of each character
	tset(n-2, 0);
	tset(n-1, 1); // the sentinel must be in n-1, important!!!
	for (i = n - 3; i >= 0; i--)
		tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);
	
	// stage 1: reduce the problem by at least 1/2
	// sort all the S-substrings
	getBuckets(s, bkt, n, K, cs, 1); // find ends of buckets
	for (i = 0; i < n; i++)
		SA[i] = -1;
	for (i = 1; i < n; i++)
		if (isLMS(i))
			SA[--bkt[chr(i)]] = i;
	induceSAl(t, SA, s, bkt, n, K, cs, 0);
	induceSAs(t, SA, s, bkt, n, K, cs, 1);
	
	// compact all the sorted substrings into the first n1 items of SA
	// 2*n1 must be not larger than n (proveable)
	n1 = 0;
	for (i = 0; i < n; i++)
		if (isLMS(SA[i]))
			SA[n1++] = SA[i];
	
	// find the lexicographic names of all substrings
	for (i = n1; i < n; i++)
		SA[i] = -1; // init the name array buffer
	
	name = 0, prev = -1;
	for (i = 0; i < n1; i++) {
		pos = SA[i];
		diff = 0;
		for (d = 0; d < n; d++)
			if (prev == -1 || chr(pos+d) != chr(prev+d) || tget(pos+d)
					!=tget(prev+d)) {
				diff = 1;
				break;
			} else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d)))
				break;
		
		if (diff) {
			name++;
			prev = pos;
		}
		
		pos = (pos % 2 == 0) ? pos / 2 : (pos - 1) / 2;
		SA[n1 + pos] = name - 1;
	}
	
	for (i = n - 1, j = n - 1; i >= n1; i--)
		if (SA[i] >= 0)
			SA[j--] = SA[i];
	
	// stage 2: solve the reduced problem
	// recurse if names are not yet unique
	SA1 = SA;
	s1 = SA + n - n1;
	if (name < n1)
		SA_IS((unsigned char*) s1, SA1, n1, name - 1, sizeof(int), depth+1);
	else // generate the suffix array of s1 directly
		for (i = 0; i < n1; i++)
			SA1[s1[i]] = i;
	
	// stage 3: induce the result for the original problem
	// put all left-most S characters into their buckets
	getBuckets(s, bkt, n, K, cs, 1); // find ends of buckets
	for (i = 1, j = 0; i < n; i++)
		if (isLMS(i))
			s1[j++] = i; // get p1
	
	for (i = 0; i < n1; i++)
		SA1[i] = s1[SA1[i]]; // get index in s
	
	for (i = n1; i < n; i++)
		SA[i] = -1; // init SA[n1..n-1]
	
	for (i = n1 - 1; i >= 0; i--) {
		j = SA[i];
		SA[i] = -1;
		SA[--bkt[chr(j)]] = j;
	}
	
	induceSAl(t, SA, s, bkt, n, K, cs, 0);
	induceSAs(t, SA, s, bkt, n, K, cs, 1);
}

int inv[MAX_SIZE];

/**
 * Gets the LCP of the given suffix array.
 */
void lcpa(int *a, unsigned char *s, int *lcp, int n) {
	int i, h, x, j;
	unsigned char *p0, *p1;
	
	for (i = 0; i < n; i++)
		inv[a[i]] = i;
	
	h = 0; /* visit in string order */
	for (i = 0; i < n - 1; i++) { /* omit last, least suff */
		x = inv[i]; /* i,j,x,h as in intro */
		j = a[x - 1];
		p1 = s + i + h;
		p0 = s + j + h;
		while (*p1++ == *p0++)
			h++;
		lcp[x] = h;
		if (h > 0)
			h--;
	}
	
	lcp[0] = 0; /* least suffix has no predecessor */
}

int suffixArray[MAX_SIZE];
int lcp[MAX_SIZE];

/**
 * Gets the shortes non-repeated substring of the given string.
 */
int getShortestNonRepeatedSubstring(unsigned char *string, unsigned char *suffix) {
	int n, best, bestsize, i, len, len2;
	n = strlen((char *)string) + 1;
	
	if (n == 2) {
		suffix[0] = string[0];
		suffix[1] = 0;
		return 1;
	}
	
	// Get suffix array
	SA_IS(string, suffixArray, n, ALPHA_SIZE, sizeof(unsigned char), 0);
	// Get LCP of suffix array
	lcpa(suffixArray, string, lcp, n);
	
	// Solve
	best = suffixArray[n-1];
	bestsize = lcp[n-1] + 1;
	for (i = 1; i < n; i++) {
		len = lcp[i];
		if (len < n-1-suffixArray[i-1]) {
			len2 = lcp[i-1];
			if (len2 > len)
				len = len2;
			len++;
#if FIRST_LEXICO
			if (len < bestsize || (len == bestsize && memcmp(string + suffixArray[i], string + best, bestsize) < 0)) {
#else
			if (len < bestsize) {
#endif				
				best = suffixArray[i-1];
				bestsize = len;
			}
		}
	}
	
	for (i = 0; i < bestsize; i++)
		suffix[i] = string[best + i];
	suffix[bestsize] = 0;
	
	return bestsize;
}
	
int X[MAX_SIZE];

/*
 * KMP helper
 */
void kmp_table(unsigned char *ptr_i, unsigned char *ptr_m, int word_length, int sentence_length) {
	int i, j;
	i = 2;
	j = 0;
	X[0] = -1;
	X[1] = 0;
	for (; i < word_length;) {
		if (*(ptr_i + i - 1) == *(ptr_i + j)) {
			X[i] = j + 1;
			i = i + 1;
			j = j + 1;
		} else if (j > 0) {
			j = X[j];
		} else {
			X[i] = 0;
			i = i + 1;
		}
	}
}
	
/*
 * Knuth-Morris-Pratt algorithm
 */
int kmp(unsigned char *ptr_i, unsigned char *ptr_m, int word_length, int sentence_length) {
	int m, i, count;
	
	kmp_table(ptr_i, ptr_m, word_length, sentence_length);
	for (i = 0, m = 0, count = 0; m < sentence_length;) {
		if (*(ptr_i + i) == *(ptr_m + m + i)) {
			i = i + 1;
			if (i == word_length) {
				m -= word_length-1;
				count++;
			}
		} else {
			m = m + i - X[i];
			if (i > 0)
				i = X[i];
		}
	}
	
	return count;
}

unsigned char string[MAX_SIZE];
unsigned char suffix[MAX_SIZE];

/**
 * Entry point
 */
int main(int argc, char **argv) {
	int type, i, size, line;
	char *word;
	FILE *infile, *outfile;
	if (argc < 4) {
		printf("Missing parameters\n");
		return EXIT_FAILURE;
	}
	
	type = atoi(argv[1]);
	infile = fopen(argv[2], "r");
	if (!infile) {
		printf("Cannot open input file %s\n", argv[2]);
		return EXIT_FAILURE;
	}
	
	outfile = fopen(argv[3], "w");
	if (!outfile) {
		printf("Cannot open output file %s\n", argv[3]);
		return EXIT_FAILURE;
	}
		
	if (type == 1) {
		i = 0;
		while (fscanf(infile, "%s", string) != EOF) {
			// Get the shortest non-repeated substring
			size = getShortestNonRepeatedSubstring(string, suffix);
//			fprintf(outfile, "%s\n", suffix);
			fprintf(outfile, "%d,%s,%d,Moises Osorio\n", ++i, suffix, size);
		}
	} else if (type == 2) {
		if (argc < 6) {
			printf("Missing parameters\n");
			return EXIT_FAILURE;
		}
		
		word = argv[4];
		line = atoi(argv[5]);
		for (i = 0; i < line-1; i++) // Read first line-1 lines
			fscanf(infile, "%s", string);
		if (fscanf(infile, "%s", string) == EOF) {
			printf("Input file has less than %d lines\n", line);

			fclose(infile);
			fclose(outfile);
			return EXIT_FAILURE;
		}
		
		// Get repetitions
		size = kmp((unsigned char *)word, string, strlen((char *) word), strlen((char *) string));
		fprintf(outfile, "%d,%s,%d,Moises Osorio\n", line, word, size);
	} else {
		printf("Parameter type %d is not 1 or 2\n", type);
		return EXIT_FAILURE;
	}
	
	fclose(infile);
	fclose(outfile);
	
	return EXIT_SUCCESS;
}
