#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

// serial version of SoE algorithm

int main(int argc, char* argv[]) {

	int thread_count;

	int N = atoi(argv[1]);
	thread_count = atoi(argv[2]);
	int *isPrime = malloc(N*sizeof(int));
	int *primes = malloc(N*sizeof(int));
	memset(isPrime, 1, N*sizeof(int));
	memset(primes, 0, N*sizeof(int));

	int nPrime = 0;
	int i;

	double tstart = 0.0, tend = 0.0, ttaken;

	tstart = omp_get_wtime();

	#pragma omp parallel for num_threads(thread_count)
	for (i = 2; i < N; i++) {
		if (isPrime[i]) {
			int j;
			for (j = i + i; j < N; j += i)
				isPrime[j] = 0;
		}
	}

	int cnt = 0;
	for (i = 2; i < N; i++) {
		if (isPrime[i]) {
			primes[nPrime++] = i;
			cnt++;
		}
	}
	ttaken = omp_get_wtime() - tstart;

	printf("Pi(%d) = %d\n", N, cnt);
	printf("Time taken = %f\n", ttaken);

	FILE* fp;
	char filename[10];
	sprintf(filename, "%d.txt", N);

	fp = fopen(filename, "w+");
	
	i = 1;
	int pre = primes[0];
	fprintf("%d %d %d\n", i, pre, 0);
	while(1) {
		if (!primes[i])
			break;
		fprintf("%d %d %d\n", i + 1, primes[i], primes[i] - pre);
		pre = primes[i++];
	}
	fprintf("\n");
	fclose(fp);

	return 0;
}