#pragma once
typedef struct{
    unsigned int cap, len;
    void** data;
}DynArray;

DynArray* create(unsigned int cap);
void release(DynArray* arr);
void add(void* elem, DynArray* arr);
void print(const DynArray* arr, void *(display)(void* elem));

unsigned int getLength(const DynArray * array);
unsigned int getCapacity(const DynArray * array);
