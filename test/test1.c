#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

// serial version of SoE algorithm

int main(int argc, char* argv[]) {

	int N = atoi(argv[1]);
	int *isPrime = malloc(N*sizeof(int));
	int *primes = malloc(N*sizeof(int));
	memset(isPrime, 1, N*sizeof(int));
	memset(primes, 0, N*sizeof(int));

	int nPrime = 0;
	int i;
	for (i = 2; i < N; i++) {
		if (isPrime[i]) {
			int j;
			for (j = i + i; j < N; j += i)
				isPrime[j] = 0;
			primes[nPrime++] = i;
		}
	}

	printf("%d\n", primes[0]);
	i = 0;
	while(1) {
		if (!primes[i])
			break;
		printf("%d ", primes[i++]);
	}
	printf("\n");
	return 0;
}