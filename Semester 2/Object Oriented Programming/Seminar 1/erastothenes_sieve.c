#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void sieve(bool is_prime[], int n) {
	is_prime[0] = false;
	is_prime[1] = false;
	int index = 2;

	//we can modify here, write loop different way
	//as discussed at seminar
	while (index < n) {
		while (!is_prime[index] && index < n) {
			index++;
		}
		for (int i = 2 * index; i <= n; i += index) {
			is_prime[i] = false;
		}
		index++;
	}
}

/// <summary>
/// Prints number - is_prime information
/// </summary>
/// <param name="arr">the bool array which holds the information</param>
/// <param name="n">the number up to which the information is printed</param>
void pretty_print_bool_array(bool arr[], int n) {
	for (int i = 0; i <= n; i++) {
		//"-6" -> https://cplusplus.com/reference/cstdio/printf/
		// see meaning of "-" in flags
		// 6 = (number) in width
		printf("%-6d| ", i);
	}
	printf("\n");
	for (int i = 0; i <= n; i++) {
		//ternary operator
		//condition ? value_if_true : value_if_false
		printf("%-6s| ", arr[i]?"true":"false");

	}
	
}


void get_primes_up_to_n(int n_primes[], int n) {
	//we consider that we cannot have n greater than 1000
	//would the implementation change if we did not 
	//impose this limit (if we would have no specified limit)?

	bool is_prime[1001];
	for (int i = 0; i <= n; i++)
		is_prime[i] = true;


	//after this call, is_prime array is modified;
	//at index i, we have is_prime[i] = true if i
	//is prime, or is_prime[i] = false if i is not prime
	sieve(is_prime, n);

	pretty_print_bool_array(is_prime,n);

	int index = 0;
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			n_primes[index] = i;
			index++;
		}
	}
}

void test_get_primes_up_to_n() {
	int primes[1001];
	int good_primes[] = { 2, 3, 5, 7, 11 };
	get_primes_up_to_n(primes, 12);

	for (int i = 0; i < 5; i++) {
		assert(primes[i] == good_primes[i]);
	}
}

int main() {
	int n, how_many_primes;
	int primes[1001];
	test_get_primes_up_to_n();
	printf("n=");
	scanf("%d", &n);

	//Can we modify the function we have such that 
	//we also return how many primes there are
	//up to n?
	
	//What would you modify/add in this program
	//such that the below code works correctly?

	/*printf("The %d prime numbers up to %d are:\n", how_many_primes, n);
	for (int i = 0; i < how_many_primes; i++)
		printf("%d ", primes[i]);
	return 0;*/
}