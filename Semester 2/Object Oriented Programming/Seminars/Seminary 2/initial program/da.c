#include "da.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void reallocate(DynArray* arr, unsigned int new_cap){
    arr->data=(int*)realloc(arr->data,new_cap);
    if(!arr->data) {
        printf("Memory error");
        exit(-1);
    }
    arr->cap=new_cap;
}

void print(const DynArray* arr){
    printf("The array with capacity %d and length %d: ", arr->cap, arr->len);
    for (int i=0; i<= arr -> len; i++)
        printf("%d ", arr -> data[i]);
    printf("\n");


}
unsigned int getLength(const DynArray * array){
    return array->len;
}
unsigned int getCapacity(const DynArray * array){
    return array->cap;
}
DynArray* create(unsigned int cap){
    DynArray* arr=(DynArray*)malloc(sizeof(DynArray));
    if(!arr) {
        printf("Memory error");
        exit(-1);
    }
    arr->cap=cap;
    arr->len=0;

    arr->data=(int*)malloc(cap*sizeof(int*));
    if(!arr->data) {
        printf("Memory error");
        exit(-1);
    }

    memset(arr->data,0,cap*sizeof(int*));
    return arr;

}

void release(DynArray* arr){
    free(arr->data);
    free(arr);
}

void add(int elem, DynArray* arr){
    if(arr->len==arr->cap){
        reallocate(arr, (arr->cap)*2);
    }
    arr->data[arr->len]=elem;
    (arr->len)++;


}
