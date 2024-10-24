#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
# include <math.h>

int number_of_digits(int n) {
	int digitCount = 0;
	while (n != 0) {
		digitCount++;
		n /= 10;
	}
	return digitCount;
}
void print_numbers_up_to(int n) {
	double square_root = sqrt(n);
	printf("Square root as double is: %lf.\n", square_root);
	//what happens here?
	int isquare_root = square_root;
	printf("Square root as int is: %d.\n", isquare_root);
	int width = number_of_digits(n) + 1;


	for (int i = 1; i <= n; i++) {
		printf("%*d |", width, i);
		if (i % isquare_root == 0)
			printf("\n");
	}
}

int main()
{
	//How would we modify this code so that
	//it prints the prime numbers up to given n?
	int n;
	printf("How many values to print?");
	scanf("%d",&n);
	print_numbers_up_to(n);
	return 0;
}