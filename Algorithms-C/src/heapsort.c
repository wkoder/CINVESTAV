#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 1000
#define REP 10

// Procedure 5.2 from notes
void heapify(int *data, int n, int i)
{
	int left, right, big, tmp;

	left = ((i+1) << 1) - 1; // i*2 equivalent with 0-based i
	right = (i+1) << 1; // i*2+1 equivalent with 0-based i
	big = i;

	if (left < n && data[left] > data[big])
		big = left;

	if (right < n && data[right] > data[big])
		big = right;

	if (big != i) {
		tmp = data[big];
		data[big] = data[i];
		data[i] = tmp;
		heapify(data, n, big);
	}
}

// Procedure 5.3.1 from notes
void build_heap(int *data, int n)
{
	int i;
	for (i = n >> 1; i >= 0; i--)
		heapify(data, n, i);
}

// Procedure 5.3.2 from notes
void heapsort(int *data, int n)
{
	int i, tmp;

	build_heap(data, n);
	for (i = n-1; i >= 1; i--) {
		tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		heapify(data, i, 0); // n = n-1
	}
}

// Generates a random data array of length n
void randomize2(int *data, int n)
{
	int i;
	for (i = 0; i < n; i++)
		data[i] = rand();
}

// Microseconds since the epoch
long long get_time2()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000LL + tv.tv_usec;
}

// Entry point. No input necessary since it will generate the table asked in the task
int main2() {
	int data[MAX];
	int n, i, j;
	long long start_time, time_sum;

	srand(time(NULL)); // Set time as random seed

	for (n = 1; n <= MAX; n++) {
		time_sum = 0;
		for (i = 0; i < REP; i++) {
			randomize(data, n); // Generate random data

			start_time = get_time();
			heapsort(data, n); // Sort the data
			time_sum += get_time() - start_time; // Get the time it took to sort

			for (j = 1; j < n; j++)
				if (data[j] < data[j-1]) {
					printf("ERROR, it does not work!\n");
					exit(-1);
				}
		}

		// Show the avergage time it took to sort REP arrays of length n
		printf("%d %lld\n", n, time_sum / REP);
	}

	return 0;
}
