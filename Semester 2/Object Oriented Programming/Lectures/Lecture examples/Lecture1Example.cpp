// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int GLOBAL_V;
// pass by value
void f(int b) {
    b = 10;
    GLOBAL_V = 10;
}

// pass by pointer /address
void minValLoc(int* a, int sz, int* min, int* minIndex) {
    int x;
    *min = a[0]; 
    *minIndex = 0;
    int i;
    for (i = 0; i < sz; i++) {
        if (a[i] < *min) {
            *min = a[i];
            *minIndex = i;
        }
        a[i] = 100;
    }
    i++;
    GLOBAL_V = 20;
}

int main()
{
    int arr[10]= { 10, 30, 1, 5, -3 };
    int sz = 5;

    scanf("%d", &sz); // pass by pointer
    for (int i = 0; i < sz; i++) {
        printf("a[%d]=", i);
        scanf("%d", &arr[i]);
    }

    char name[20];
    scanf("%s", name);
    printf("the name is %s ", name);


    int min = 0;
    int minIndex = 0;
    minValLoc(arr, sz, &min, &minIndex);
    printf("min = %d, minIndex = %d", min, minIndex);
    printf("arr[0] = %d arr=%p\n", arr[0], arr);
    {
        int a = 4;
		printf("a = %d\n", a);
		f(a);
		printf("a = %d\n", a); 
		printf("The number is %d and a++ is %d", a, a + 1);
		// & - address of operator
		// pointer datatype*
		int* pa = &a;
		printf("\nThe mem loc of a %p\n", pa);

        int arr[10];
        printf("The address of the array is %p %p ; addr off the second element %p\n", arr, &arr[0], &arr[1]);
        //  printf("diff in addess between a[1] and a[0] %d", &arr[1] - &arr[0]);

          // * - dereferencing operator: access the data at a memory location
        *pa = 10;
        printf("\na = %d, *pa=%d\n", a, *pa);
        arr[0];
    }
    return 0;
}

