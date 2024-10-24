#pragma once
#include <stdlib.h>
#include <stdbool.h>
#define NULL_TELEM -111111;
typedef int TElem;
typedef struct {
	TElem* data;
	int length;
	int capacity;
} DynamicArray;

/// <summary>
/// Creates dynamic array with initial capacity = 2
/// Obs: can modify this function to give initial capacity as parameter
/// </summary>
/// <returns>the created dynamic array</returns>
DynamicArray createArray();

/// <summary>
/// Adds an element to the end of the dynamic array
/// given as parameter; if array is full, capacity will
/// be increased
/// </summary>
/// <param name="array">the dynamic array in which we add</param>
/// <param name="elem">the added element</param>
void addToEnd(DynamicArray* array, TElem elem);

void resize(DynamicArray* array);

TElem removeLast(DynamicArray* array);
TElem removeFromPosition(DynamicArray* array, int pos);

/// <summary>
/// Returns the element from index pos in the dynamic 
/// array "array"
/// </summary>
/// <param name="array">the dynamic array</param>
/// <param name="pos">the index (pre: pos between 0 and array.length-1)</param>
/// <returns>the element from index pos from the dynamic array</returns>
/// Obs. how do we handle the case in which pos is not valid?
/// Opt. 1: return NULL_TELEM
///		Advantages: easy to implement (at least for int elements)
///		Disadvantages: not suggestive
/// Opt. 2: return error code 
///     Advantages: (more) suggestive, easier to interpret if we have
///                 elements different from int
///		Disadvantages: have to return both element and error code somehow
///						e.g. struct with elem, error code
///							 one of them passed to the fn as parameter (through pointer)
///							 ...  
/// Opt. 3: throw an exception (C++)
///     both suggestive and easy to implement (if exception mechanism available)

TElem getElem(DynamicArray* array, int pos);

/// <summary>
/// Change element from position pos to have value elem
/// </summary>
/// <param name="array">the dynamic array</param>
/// <param name="elem">the element to set at position pos</param>
/// <param name="pos">the position at which we want to set the element</param>
/// <returns>the old value from index pos</returns>
TElem setElem(DynamicArray* array, TElem elem, int pos);

/// <summary>
/// Checks if elem appears in the given dynamic array
/// </summary>
/// <param name="array">the array we are searching in</param>
/// <param name="elem">the element we are searching for</param>
/// <returns>true if elem appears in the array, false otherwise</returns>
bool search(DynamicArray* array, TElem elem);

/// <summary>
/// Returns the number of elements in the dynamic array
/// </summary>
/// <param name="array">the given array</param>
/// <returns>number of elements in the dynamic array (int) </returns>
int size(DynamicArray* array);



/// <summary>
/// Destroys the given dynamic array 
/// (memory occupied by the dynamic array 
/// arr has been freed)
/// </summary>
/// <param name="arr">the array to be destroyed</param>
void destroyArray(DynamicArray* arr);