#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "disjointset.h"

#define REP 10
#define INF (1 << 31)

int **edges;

// Compares two arrays using the first element as the key
int array_cmp(const void* _a, const void* _b)
{
	const int** a;
	const int** b;

	a = (const int**) _a;
	b = (const int**) _b;

	return (*a)[0] - (*b)[0];
}

void kruskal_init()
{
	int i;

	edges = malloc(MAX * MAX * sizeof(int *));
	for (i = 0; i < MAX * MAX; i++)
		edges[i] = malloc(3 * sizeof(int));
}

// Returns the minimum spanning tree of the given adjacency matrix describing a graph.
void kruskal(int adj[MAX][MAX], int n, int mst[MAX][3])
{
	int i, j, e, mst_size;
	disjointset *ds; // Forest of trees

	// Get the edges in an array and sort them
	e = 0;
	for (i = 0; i < n; i++)
		for (j = i+1; j < n; j++) {
			edges[e][0] = adj[i][j];
			edges[e][1] = i;
			edges[e][2] = j;
			e++;
		}

	qsort(edges, e, sizeof(int *), array_cmp); // Sort edges according to their weight

	ds = disjointset_init(n); // Create disjoint set
	mst_size = 0;
	for (i = 0; i < e; i++) {
		int x, y;
		x = edges[i][1];
		y = edges[i][2];

		if (disjointset_find(ds, x) != disjointset_find(ds, y)) { // Don't belong to the same set
			mst[mst_size][0] = x; // Add to MST
			mst[mst_size][1] = y;
			mst_size++;

			disjointset_union(ds, x, y); // Unite them

			if (mst_size == n-1)
				break;
		}
	}

	if (mst_size < n-1) // Must have n-1 edges
		printf("No MST found!");
}

// Generates a random symmetric adjacency matrix of size NxN (non-directed graph)
void randomize(int data[MAX][MAX], int n)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = i+1; j < n; j++)
			data[i][j] = data[j][i] = rand(); // Graph must be symmetric since we need a non-directed graph
}

// Microseconds since the epoch
long long get_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000LL + tv.tv_usec;
}

// Entry point. No input necessary since it will generate the statistics up to MAX.
int main() {
	int n, i;
	long long start_time, time_sum;
	int adj[MAX][MAX];
	int mst[MAX][3];

	srand(time(NULL)); // Set time as random seed

	kruskal_init(); // Intialize the algorithm

	for (n = 1; n <= MAX; n++) {
		time_sum = 0;
		for (i = 0; i < REP; i++) {
			randomize(adj, n); // Generate random graph

			start_time = get_time();
			kruskal(adj, n, mst); // Get the MST
			time_sum += get_time() - start_time; // Get the time it took
		}

		// Show the average time it took to get the MST
		printf("%d %lld\n", n, time_sum / REP);
	}

	return 0;
}
