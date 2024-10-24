#pragma once
typedef struct{
    unsigned int cap, len;
    int* data;
}DynArray;

DynArray* create(unsigned int cap);
void release(DynArray* arr);
void add(int elem, DynArray* arr);
void print(const DynArray* arr);
unsigned int getLength(const DynArray * array);
unsigned int getCapacity(const DynArray * array);
