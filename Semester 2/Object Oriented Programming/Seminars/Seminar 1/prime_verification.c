#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<assert.h>


/// <summary>
/// Determines whether the specified x is prime.
/// </summary>
/// <param name="x">The given number</param>
/// <returns>
///   <c>true</c> if the specified x is prime; otherwise, <c>false</c>.
/// </returns>
bool isPrime(int x) {
	if (x < 2) return false;
	if (x % 2 == 0 && x!=2) return false;

	for (int divisor = 3; divisor*divisor <= x; divisor += 2) {
		if (x % divisor == 0) return false;
	}

	return true;
}

void testIsPrime() {
	// Negative values should return false on isPrime
	for (int number = -10; number < 0; ++number) 
		assert(isPrime(number) == false);

	// Check 0 -> false 1 -> false and 2 -> true
	assert(isPrime(0) == false);
	assert(isPrime(1) == false);
	assert(isPrime(2) == true);

	// Perform another set of checks for prime and non-prime numbers
	assert(isPrime(9) == false);
	assert(isPrime(7) == true);
	assert(isPrime(200) == false);
	assert(isPrime(48) == false);
	assert(isPrime(101) == true);

	assert(isPrime(3) == true);
	assert(isPrime(4) == false);
}

int main43(void) {
	testIsPrime();
	printf("Tests succeeded\n");

	int number;
	printf("Provide a number to check if it is prime:");
	scanf("%d",&number);
	if (isPrime(number) == true)
		printf("Number %d is prime", number);
	else {
		printf("Number %d is not prime", number);

	}
	//printf("%d", number);

	return 0;
}