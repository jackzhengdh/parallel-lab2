#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define f(x) 2 * x + 10

void Trap(double a, double b, int n, double* global_result_p);

int main(int argc, char* argv[]) {
	double global_result = 0.0;
	double a, b; // left and right endpoints
	int n; 	// total number of trapezoids
	int thread_count;

	thread_count = strtol(argv[1], NULL, 10);
	a = 0; 
	b = 100;

	#pragma omp parallel num_threads (thread_count)
	Trap(a, b, n, &global_result);

	printf("With %d trapezoids, estimated integral from %2f to %2f = %.2e\n"
		, n, a, b, global_result);
	return 0;
}

void Trap(double a, double b, int n, double* global_result_p) {
	double dx, x, my_result;
	double local_a, local_b;
	int i, local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_num_threads();

	dx = (b - a) / n;
	local_n = n / thread_count;
	local_a = a + my_rank * local_n * dx;
	local_b = b + local_n * dx;
	my_result = (f(local_a) + f(local_b)) / 2.0;
	for (i = 1; i <= local_n - 1; i++) {
		x = local_a + i * dx;
		my_result += f(x);
	}
	my_result *= dx;

	#pragma omp critical
	*global_result_p += my_result;
}