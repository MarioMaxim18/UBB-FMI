#include "dynamicarray.h"

DynamicArray createArray(equalFct eqFn, destroyFct destroyFn)
{
	DynamicArray dynamicArr;
	dynamicArr.capacity = 2;
	dynamicArr.length = 0;
	dynamicArr.data = (TElem*) malloc(dynamicArr.capacity * sizeof(TElem));
	dynamicArr.equalityFn = eqFn;
	dynamicArr.destroyFct = destroyFn;
	return dynamicArr;
}

void addToEnd(DynamicArray* array, TElem elem)
{
	if (array->length == array->capacity)
		resize(array);
	array->data[array->length] = elem;
	array->length++;
}

void resize(DynamicArray* array)
{
	int newCapacity = array->capacity * 2;
	TElem* newArray = (TElem*)malloc(sizeof(TElem) * newCapacity);
	for (int i = 0; i < array->length; i++)
		newArray[i] = array->data[i];
	free(array->data);
	array->data = newArray;
	array->capacity = newCapacity;
}

TElem removeLast(DynamicArray* array)
{
	TElem deletedElem = array->data[array->length - 1];
	array->data[array->length - 1] = NULL;
	array->length--;
	return deletedElem;
}

TElem removeFromPosition(DynamicArray* array, int pos)
{

	TElem deletedElem = array->data[pos];
	for (int i = pos; i < array->length-1; i++)
		array->data[i] = array->data[i + 1];
	array->length--;
	return deletedElem;
}

TElem getElem(DynamicArray* array, int pos)
{
	if (pos<0 || pos>array->length)
		return;
	return array->data[pos];

}

TElem setElem(DynamicArray* array, TElem elem, int pos)
{
	/*if (pos<0 || pos>array->length)
		return -1;*/
	TElem replacedElement = array->data[pos];
	array->data[pos] = elem;
	return replacedElement;
}

bool search(DynamicArray* array, TElem elem)
{
	for (int i = 0; i < array->length; i++)
		if (array->equalityFn(elem, array->data[i]))
			return true;
	return false;
}

int size(DynamicArray* array)
{
	return array->length;
}

void destroyArray(DynamicArray* arr)
{
	for (int i = 0; i < arr->length; i++)
		arr->destroyFct(arr->data[i]);
	free(arr->data);
}


