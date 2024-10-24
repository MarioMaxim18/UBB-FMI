/*
* Write a function that approximates the square root of a real 
positive number n with precision eps.  You should use a divide et 
impera approach for this. Divide et impera is a programming technique in 
which the base problem is broken down into smaller problems of the same type, 
until we reach a problem that is so simple that it can be solved directly.
Then, the solutions to all these simpler subproblems are combined to get the solution 
of the original problem. You can treat this problem as a searching problem. 
We know that the square root of a real positive number is in the interval [0, n]. 
So, similar to binary search, we can successively half and search in this interval 
the number s which if squared it would give a number approximately equal to n: |s*s - eps| < n .

*/


#include <stdio.h>
#include <assert.h>
#include <math.h>
/// <summary>
/// Computes square root of a given number 
/// </summary>
/// <param name="x">The number for which the square root is computed</param>
/// <param name="precision">The precision for the computed square root</param>
/// <returns>return square root for the given number</returns>
double square_root(int x, int precision) {
	//consider x>=1 -> what changes if x between 0 and 1?
	double low = 1;
	double high = x;
	double middle = (low + high) / 2;
	double precisiond = 1;
	for (int i = 0; i < precision; i++)
		precisiond /= 10;
	double eps = fabs(x - (middle * middle));

	while (eps >= precisiond) {
		if (middle * middle > x)
			high = middle;
		else
			low = middle;

		middle = (low + high) / 2;


		eps = fabs(x - (middle * middle));

	}
	printf("Found root: %lf\n", middle);
	double root = (int)(middle * pow(10, precision)) / pow(10, precision);
	printf("After truncating to the decimals we need: %lf\n", root);
	return root;
	
	
	
}
void test_square_root() {
	assert(square_root(27, 3) == 5.196);
	assert(square_root(19, 5) == 4.35889);
	assert(square_root(21, 7) == 4.5825756);
	assert(square_root(50, 2) == 7.07);
	assert(square_root(50, 5) == 7.07106);


}

int main() {
	test_square_root();
}