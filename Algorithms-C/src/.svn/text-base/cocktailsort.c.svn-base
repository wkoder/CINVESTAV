#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 1000
#define REP 10

// Cocktail sort implementation
void cocktailsort(int *data, int n)
{
	int i, j, temp, swapped;
	do {
		swapped = 0;
		for (i = 0; i < n-1; i++) // Move the greater element to the end
			if (data[i] > data[i+1]) {
				temp = data[i];
				data[i] = data[i+1];
				data[i+1] = temp;
				swapped = 1;
			}

		if (!swapped)
			break; // Already sorted!

		swapped = 0;
		for (i = n-2; i >= 0; i--) // Move the lesses element to the start
			if (data[i] > data[i+1]) {
				temp = data[i];
				data[i] = data[i+1];
				data[i+1] = temp;
				swapped = 1;
			}
	} while (swapped);
}

// Generates a random data array of length n
void randomize3(int *data, int n)
{
	int i;
	for (i = 0; i < n; i++)
		data[i] = rand();
}

// Microseconds since the epoch
long long get_time3() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000LL + tv.tv_usec;
}

// Entry point. No input necessary since it will generate the table asked in the task
int main3() {
	int data[MAX];
	int n, i, j;
	long long start_time, time_sum;

	srand(time(NULL)); // Set time as random seed

	for (n = 1; n <= MAX; n++) {
		time_sum = 0;
		for (i = 0; i < REP; i++) {
			randomize(data, n); // Generate random data

			start_time = get_time();
			cocktailsort(data, n); // Sort the data
			time_sum += get_time() - start_time; // Get the time it took to sort

			for (j = 1; j < n; j++)
				if (data[j] < data[j-1]) {
					printf("ERROR, it does not work!\n");
					exit(-1);
				}
		}

		// Show the average time it took to sort REP arrays of length n
		printf("%d %lld\n", n, time_sum / REP);
	}

	return 0;
}
