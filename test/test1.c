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

	#pragma omp parallel for num_threads(thread_count) schedule(dynamic)
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
	
	printf("%d\n", cnt);
	
	// printf("%d\n", primes[0]);
	// i = 0;
	// while(1) {
	// 	if (!primes[i])
	// 		break;
	// 	printf("%d ", primes[i++]);
	// }
	// printf("\n");
	return 0;
}