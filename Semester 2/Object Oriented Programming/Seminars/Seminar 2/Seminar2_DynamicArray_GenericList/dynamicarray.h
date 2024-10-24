#pragma once
#include "movie.h"
#include <stdlib.h>
#include <stdbool.h>
//#define NULL_TELEM void*;

//modification from last version
typedef void* TElem;

typedef bool(*equalFct)(void*, void*);
typedef void(*destroyFct)(void*);

typedef struct {
	TElem* data;
	int length;
	int capacity;
	equalFct equalityFn;
	destroyFct destroyFct;

} DynamicArray;

DynamicArray createArray(equalFct eqFn, destroyFct destroyFn);
void addToEnd(DynamicArray* array, TElem elem);
void resize(DynamicArray* array);
TElem removeLast(DynamicArray* array);
TElem removeFromPosition(DynamicArray* array, int pos);
TElem getElem(DynamicArray* array, int pos);
TElem setElem(DynamicArray* array, TElem elem, int pos);
bool search(DynamicArray* array, TElem elem);
int size(DynamicArray* array);
void destroyArray(DynamicArray* arr);