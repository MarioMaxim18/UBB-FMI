#include <stdio.h>
#include "da.h"
#include <string.h>

void display(void* el){
    printf("%d", *((int*)el));
}

int main() {
    DynArray *arr=create(4);
    for(int i=0;i<10;i++){
        int* el = (int*)malloc(sizeof(int));
        add(el, arr);

    }
    print(arr);//16 cap
    release(arr);
    return 0;

