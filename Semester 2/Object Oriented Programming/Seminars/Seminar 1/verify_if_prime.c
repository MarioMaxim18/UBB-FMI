/*
* Write a C program to check if a number is prime.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
/// <summary>
/// Verify that the given number is prime
/// </summary>
/// <param name="nr">the number to check; precondition: number is positive, smaller than 65535</param>
/// <returns>true if the number is prime, false otherwhise</returns>
bool prime(short unsigned nr) {
	if (nr < 2)
		return false;
	if (nr < 4)
		return true;
	if (nr % 2 == 0)
		return false;
	for (int i = 3; i * i <= nr; i = i + 2) {
		if (nr % i == 0)
			return false;
	}
	return true;
}
void test_prime() {
	assert(prime(0) == false);
	assert(prime(1) == false);
	assert(prime(5) == true);
	assert(prime(6) == false);
	assert(prime(145) == false);
	assert(prime(101) == true);
	//careful about big nrs (remember, we use
	// (unsigned) short int)
	// - undefined behavior
	//assert(prime(17000002) == false);
}
int main24() {
	short unsigned number;
	test_prime();
	
	scanf("%hu", &number);
	if (prime(number) == true) printf("TRUE");
	else printf("FALSE");

	//char name[5];
	//printf("Give name:");
	//scanf_s("%s", name, 5);
	//scanf_s("%4s", name, 5);
	//printf("\nThe name: %s", name);
	


}