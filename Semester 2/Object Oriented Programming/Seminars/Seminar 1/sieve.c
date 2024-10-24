/*
* Write a function that finds and returns the first n prime numbers.
It turns out that there is a well known ancient algorithm for this:
the Sieve of Eratosthenes. The output of this function should be an array
containing the prime numbers smaller than or equal to n, as well as the
number of elements that fulfill this property. (Don’t just print the prime numbers
in the function!).
*
*/
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// Initialize sieve array with 1s,
/// except positions 0,1
/// </summary>
/// <param name="sieve">sieve aray</param>
/// <param name="n">number of elements in sieve array</param>
void init_arr(int sieve[], int n) {
	for (int i = 0; i < n; i++) {
		sieve[i] = 1;
	}

	sieve[0] = 0;
	sieve[1] = 0;
}

/// <summary>
/// Create a (dynamically allocated) array in 
/// which the prime numbers up to n will be stored
/// </summary>
/// <param name="n">the number of spots allocated in the array</param>
/// <returns>the array in which the prime numbers will be kept</returns>
int* create_to_return(int n) {
	int* to_return = (int *)malloc(sizeof(int) * n);
	//this was added as an initial check that the array 
	//is modified in function
	//to_return[0] = 101;
	return to_return;
}
/// <summary>
/// Returns the prime numbers up to n by completing sieve array
/// </summary>
/// <param name="sieve">the (previously initialized) sieve array </param> 
/// <param name="to_return">the array through which the prime numbers up to n are returned</param> 
/// <param name="count">how many prime numbers are found up to n </param> 
/// <param name="n">the number up to which we want to find prime numbers</param> 
void complete_sieve(int sieve[], int to_return[],int *count,int n) {
	int index = 0;

	for (int i = 2; i < n; i++) {
		if (sieve[i] == 1) {
			for (int j = i+i; j < n; j = j + i) {
				sieve[j] = 0;
			}
		}
	}

	for (int i = 2; i < n; i++) {
		if (sieve[i] == 1) {
			to_return[index++] = i;
		}
	}

	*count = index;
}

int main4324() {
	int n = 100;
	int sieve[100];
	int count = 0;

	//printf("%d", to_return[0]);

	init_arr(sieve, n);
	int* to_return = create_to_return(n);

	//other choices:
	//make complete_sieve a separate function that only „completes” sieve,
	//returns modified sieve array
	//make another function that creates the array of prime numbers up to n
	//which receives sieve array as input and returns the array of prime numbers
	complete_sieve(sieve, to_return,&count,n);


	//see printf documentation:
	//https://cplusplus.com/reference/cstdio/printf/
	printf("%3d |", to_return[0]);
	for (int i = 1; i < count; i++) {
		printf("%3d |", to_return[i]);
		if ((i+1) % 5 == 0)
			printf("\n");
	}
}