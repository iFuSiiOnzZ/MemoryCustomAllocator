#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Allocator.h"
#include "StackAllocator.h"
#include "LinearAllocator.h"

#define B   1
#define KB  1024
#define MB  1024 * 1024
#define GB  1024 * 1024 * 1024

#include <iostream>

struct test_t
{
    float x, y, z;
};


int main(int argc, char *argv[])
{
    void *l_pMem = (void *) malloc (512);
    CAllocator *l_pAllocator = new CStackAllocator(512, l_pMem);

    int *i = (int *) l_pAllocator->Allocate(sizeof(int), __alignof(int));
    //*i = 123;
   
    float *f = (float *) l_pAllocator->Allocate(sizeof(float), __alignof(float));
    //*f = 3.1415f;

    test_t *t = (test_t *) l_pAllocator->Allocate(sizeof(test_t), __alignof(test_t));
    //t->x = t->y = t->z = 3.1415f;

    //printf("i: %x\n", i);
    //printf("f: %x\n", f);
    //printf("t: %x\n", t);

    printf("Allocated Mem: %d\n", l_pAllocator->GetUsedMemory());

    l_pAllocator->Deallocate(t);
    l_pAllocator->Deallocate(f);
    l_pAllocator->Deallocate(i);

    printf("Allocated Mem: %d\n", l_pAllocator->GetUsedMemory());

    free(l_pMem);
    delete(l_pAllocator);

    system("pause");
    return(EXIT_SUCCESS);
}
