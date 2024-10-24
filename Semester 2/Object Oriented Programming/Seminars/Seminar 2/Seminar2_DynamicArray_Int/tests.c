#include "tests.h"

void testCreateDestroyArray()
{
	DynamicArray arr = createArray();
	assert(size(&arr) == 0);
	destroyArray(&arr);
}

void testAddArray()
{
	DynamicArray arr = createArray();
	addToEnd(&arr, 10);
	assert(size(&arr) == 1);
	TElem elem1 = getElem(&arr, 0);
	assert(elem1 == 10);

	addToEnd(&arr, 9);
	assert(size(&arr) == 2);

	elem1 = getElem(&arr, 0);
	assert(elem1 == 10);

	TElem elem2 = getElem(&arr, 1);
	assert(elem2 == 9);

	addToEnd(&arr, 4);
	assert(size(&arr) == 3);

	addToEnd(&arr, 5);
	assert(size(&arr) == 4);
	TElem lastElement = getElem(&arr, arr.length-1);
	assert(lastElement == 5);

	destroyArray(&arr);
}

void testRemoveFromArray(){
	DynamicArray arr = createArray();
	addToEnd(&arr, 10);
	addToEnd(&arr, 9);
	addToEnd(&arr, 5);
	addToEnd(&arr, 4);
	addToEnd(&arr, 2);
	
	assert(size(&arr) == 5);
	TElem deletedElement = removeLast(&arr);
	assert(size(&arr) == 4);
	assert(!search(&arr, 2));
	assert(deletedElement == 2);

	assert(getElem(&arr, 0) == 10);
	assert(getElem(&arr, 1) == 9);
	assert(getElem(&arr, 2) == 5);
	assert(getElem(&arr, 3) == 4);

	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement == 10);
	assert(size(&arr) == 3);

	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement == 9);
	assert(size(&arr) == 2);


	deletedElement = removeFromPosition(&arr, 1);
	assert(deletedElement == 4);
	assert(size(&arr) == 1);

	destroyArray(&arr);

	
}

void testSetGetElemPosArray() {
	DynamicArray arr = createArray();
	addToEnd(&arr, 10);
	addToEnd(&arr, 9);
	addToEnd(&arr, 5);
	addToEnd(&arr, 4);
	addToEnd(&arr, 2);

	TElem element = getElem(&arr, 0);
	assert(element == 10);

	element = getElem(&arr, 1);
	assert(element == 9);

	element = getElem(&arr, 2);
	assert(element == 5);

	element = getElem(&arr, 3);
	assert(element == 4);

	element = getElem(&arr, 4);
	assert(element == 2);

	TElem replacedElement = setElem(&arr, -6, 0);
	assert(replacedElement == 10);
	element = getElem(&arr, 0);
	assert(element == -6);

	replacedElement = setElem(&arr, 83, 4);
	assert(replacedElement == 2);
	element = getElem(&arr, 4);
	assert(element == 83);


	destroyArray(&arr);

}
void testSearchInArray() {
	DynamicArray arr = createArray();
	addToEnd(&arr, 10);
	addToEnd(&arr, 9);
	addToEnd(&arr, 5);
	addToEnd(&arr, 4);
	addToEnd(&arr, 2);

	assert(!search(&arr, 7));
	assert(!search(&arr, 3));
	assert(search(&arr, 9));
	assert(search(&arr, 10));
	assert(search(&arr, 2));

	destroyArray(&arr);




}
