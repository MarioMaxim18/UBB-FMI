#include "dynamicarray.h"
#include <stdlib.h>

DynamicArray createArray() {
	DynamicArray d;
	d.capacity = 2;
	d.length = 0;
	d.data = (TElem*)malloc(d.capacity * sizeof(TElem));
	return d;
}

void addToEnd(DynamicArray* array, TElem elem) {
	if (array->capacity == array->length)
		resize(array);
	array->data[array->length] = elem;
	array->length++;
}

void resize(DynamicArray* array) {
	array->capacity *= 2;
	TElem* data = (TElem*)malloc(array->capacity * sizeof(TElem));
	for (int i = 0; i < array->length; i++)
		data[i] = array->data[i];
	free(array->data);
	array->data = data;
}

TElem removeLast(DynamicArray* array) {
	TElem lastElement = array->data[array->length - 1];
	array->length--;
	return lastElement;
}

TElem removeFromPosition(DynamicArray* array, int pos) {
	//fine if the order doesn't need to be kept
	TElem element = array->data[pos];
	for (int i = pos; i < array->length; i++) {
		array->data[i] = array->data[i + 1];
	}
	array->length--;
	return element;

	/*
	array->data[pos] = array->data[array->length - 1];
	array->length--;
	return element;*/
}

TElem getElem(DynamicArray* array, int pos) {
	return array->data[pos];
}

TElem setElem(DynamicArray* array, TElem elem, int pos)
{
	TElem replacedElement = array->data[pos];
	array->data[pos] = elem;
	return replacedElement;
}

bool search(DynamicArray* array, TElem elem)
{
	for (int i = 0; i < array->length; i++)
		if (array->data[i] == elem)
			return true;
	return false;
}

int size(DynamicArray* array) {
	return array->length;
}

void destroyArray(DynamicArray* arr) {
	free(arr->data);
}
