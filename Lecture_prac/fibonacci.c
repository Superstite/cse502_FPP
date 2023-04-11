// #include <inttypes.h>
// #include <stdio.h>
// #include <stdlib.h>

// uint64_t fib(uint64_t n)
// {
// 	if (n<2)
// 	{
// 		return n;
// 	}
// 	else
// 	{
// 		uint64_t x = fib(n-1);
// 		uint64_t y = fib(n-2);
// 		return (x+y);
// 	}
// }

// int main(int argc, char *argv[])
// {
// 	uint64_t n = atoi(argv[1]);
// 	uint64_t result = fib(n);
// 	printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n",n, result);
// 	return 0;
// }
	
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint64_t fib(uint64_t n) {
	if (n < 2) {
		return n;
	} else {
	uint64_t x = fib(n-1);
	uint64_t y = fib(n-2);
	//printf(" %" PRIu64, (x+y));
	return (x + y);
	}
}

int main(int argc, char *argv[]) {
	clock_t start, end;
	double cpu_time_used;
	uint64_t n = atoi(argv[1]);   //atoi convets string to int
	start = clock();
	uint64_t result = fib(n);
	end = clock();
	printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n",n, result);
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time used = %lf seconds \n", cpu_time_used);
	return 0;
}

// int main()
// {
//     int num; // variable to store how many elements to be displayed in the series
//     printf("Enter the number of elements to be in the series : ");
//     scanf("%d", &num); // taking user input

//     for (uint64_t i = 0; i < num; i++)
//     {
//     	uint64_t result = fib(i);
//         printf("%" PRIu64, result); // calling fibonacci() function for each iteration and printing the returned value
//     }

//     return 0;
// }



     
     
     

     
     