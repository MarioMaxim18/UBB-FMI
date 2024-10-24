#include "tests_int.h"
#include <stdlib.h>
bool equalInts(int* a, int* b) {
	return *a == *b;
}
int* createIntOnHeap(int value) {
	int* pi = malloc(sizeof(int));
	*pi = value;
	return pi;
}
void testCreateDestroyArray()
{
	DynamicArray arr = createArray(equalInts, free);
	assert(size(&arr) == 0);
	destroyArray(&arr);
}

void testAddArray()
{
	DynamicArray arr = createArray(equalInts, free);
	addToEnd(&arr, createIntOnHeap(10));
	assert(size(&arr) == 1);

	addToEnd(&arr, createIntOnHeap(9));
	assert(size(&arr) == 2);

	int* elem1 = getElem(&arr, 0);
	elem1 = getElem(&arr, 0);
	int* elem10 = createIntOnHeap(10);
	assert(equalInts(elem10, elem1));
	free(elem10);

	TElem elem2 = getElem(&arr, 1);
	int* elem9 = createIntOnHeap(9);
	assert(equalInts(elem9, elem2));
	free(elem9);

	addToEnd(&arr, createIntOnHeap(4));
	assert(size(&arr) == 3);

	addToEnd(&arr, createIntOnHeap(5));
	assert(size(&arr) == 4);

	int* elem5 = createIntOnHeap(5);
	TElem lastElement = getElem(&arr, arr.length-1);
	assert(equalInts(elem5, lastElement));
	free(elem5);
	destroyArray(&arr);
}

void testRemoveFromArray(){
	DynamicArray arr = createArray(equalInts, free);
	addToEnd(&arr, createIntOnHeap(10));
	addToEnd(&arr, createIntOnHeap(9));
	addToEnd(&arr, createIntOnHeap(5));
	addToEnd(&arr, createIntOnHeap(4));
	addToEnd(&arr, createIntOnHeap(2));
	
	int* val10 = createIntOnHeap(10);
	int* val9 = createIntOnHeap(9);
	int* val5 = createIntOnHeap(5);
	int* val4 = createIntOnHeap(4);
	int* val2 = createIntOnHeap(2);
	


	assert(size(&arr) == 5);
	TElem deletedElement = removeLast(&arr);
	assert(size(&arr) == 4);
	assert(!search(&arr, val2));
	assert(equalInts(val2, deletedElement));
	free(deletedElement);

	assert(equalInts(getElem(&arr, 0), val10));
	assert(equalInts(getElem(&arr, 1), val9));
	assert(equalInts(getElem(&arr, 2), val5));
	assert(equalInts(getElem(&arr, 3), val4));

	

	deletedElement = removeFromPosition(&arr, 0);
	assert(equalInts(deletedElement, val10));
	assert(size(&arr) == 3);
	free(deletedElement);

	deletedElement = removeFromPosition(&arr, 0);
	assert(equalInts(deletedElement, val9));
	assert(size(&arr) == 2);
	free(deletedElement);


	deletedElement = removeFromPosition(&arr, 1);
	assert(equalInts(deletedElement, val4));
	assert(size(&arr) == 1);
	free(deletedElement);

	free(val10);
	free(val9);
	free(val5);
	free(val4);
	free(val2);
	destroyArray(&arr);

	
}

void testSetGetElemPosArray() {
	DynamicArray arr = createArray(equalInts,free);
	addToEnd(&arr, createIntOnHeap(10));
	addToEnd(&arr, createIntOnHeap(9));
	addToEnd(&arr, createIntOnHeap(5));
	addToEnd(&arr, createIntOnHeap(4));
	addToEnd(&arr, createIntOnHeap(2));

	int* val10 = createIntOnHeap(10);
	int* val9 = createIntOnHeap(9);
	int* val5 = createIntOnHeap(5);
	int* val4 = createIntOnHeap(4);
	int* val2 = createIntOnHeap(2);
	int* val6m = createIntOnHeap(-6);
	int* val83 = createIntOnHeap(83);

	TElem element = getElem(&arr, 0);
	assert(equalInts(element,val10 ));

	element = getElem(&arr, 1);
	assert(equalInts(element,val9));


	element = getElem(&arr, 2);
	assert(equalInts(element, val5));


	element = getElem(&arr, 3);
	assert(equalInts(element, val4));


	element = getElem(&arr, 4);
	assert(equalInts(element, val2));


	TElem replacedElement = setElem(&arr, createIntOnHeap(-6), 0);
	assert(equalInts(replacedElement, val10));
	element = getElem(&arr, 0);
	assert(equalInts(element, val6m));
	free(replacedElement);

	replacedElement = setElem(&arr, createIntOnHeap(83), 4);
	assert(equalInts(replacedElement,val2));
	element = getElem(&arr, 4);
	assert(equalInts(element,val83 ));
	free(replacedElement);

	free(val10);
	free(val9);
	free(val5);
	free(val4);
	free(val2);
	free(val6m);
	free(val83);
	destroyArray(&arr);

}
void testSearchInArray() {
	DynamicArray arr = createArray(equalInts,free);
	addToEnd(&arr, createIntOnHeap(10));
	addToEnd(&arr, createIntOnHeap(9));
	addToEnd(&arr, createIntOnHeap(5));
	addToEnd(&arr, createIntOnHeap(4));
	addToEnd(&arr, createIntOnHeap(2));

	int* val7 = createIntOnHeap(7);
	int* val3 = createIntOnHeap(3);
	int* val9 = createIntOnHeap(9);
	int* val10 = createIntOnHeap(10);
	int* val2 = createIntOnHeap(2);

	assert(!search(&arr,val7 ));
	assert(!search(&arr, val3));
	assert(search(&arr, val9));
	assert(search(&arr, val10));
	assert(search(&arr, val2));

	free(val7);
	free(val9);
	free(val10);
	free(val3);
	free(val2);
	destroyArray(&arr);




}
