#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint64_t fib(uint64_t n) {
	if (n < 2) {
		return n;
	} else {
		uint64_t x = fib(n-1);
		uint64_t y = fib(n-2);
		return (x + y);
	}
}

typedef struct {
	uint64_t input;
	uint64_t output;
} thread_args;

void *thread_func(void *ptr) {
	uint64_t i =  ((thread_args *)  ptr)-> input;
	((thread_args *)  ptr)-> output = fib(i);
	return NULL;
}

int main(int argc, char *argv[]) {

	clock_t start, end;
	double cpu_time_used;

	pthread_t thread;
	thread_args args;
	int status;
	uint64_t result;

	if (argc < 2) {
		return 1;
	}

	uint64_t n = strtoul(argv[1], NULL, 0); //strtoulconst char *str, char **endptr, int base) function 
											//converts the initial part of the string in str to an unsigned long int value 
											//according to the given base, which must be between 2 and 36 inclusive, or be 
											//the special value 0.
	start = clock();
	if(n<30) {
		result = fib(n);
	}
	else {
		args.input = n-1;
		status = pthread_create(&thread, NULL, thread_func, (void*) &args);
		if(status !=NULL) {
			return 1;
		}
		result = fib(n-2);
		status = pthread_join(thread, NULL);
		if(status!=NULL) {
			return 1;
		}
		result += args.output;
	}
	end = clock();
	printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n",n, result);
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %lf seconds \n", cpu_time_used);
	return 0;
}