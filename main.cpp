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

struct test_t
{
    float x, y, z;
};

int main(int argc, char *argv[])
{
    void *l_pMem = (void *) malloc (GB);
    CAllocator *l_pAllocator = new CStackAllocator(GB, l_pMem);

    int *i = (int *) l_pAllocator->Allocate(sizeof(int), __alignof(int));
    *i = 123;
    printf("i = %d\n", *i);
    printf("Addr i: %u\n", i);
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    float *f = (float *) l_pAllocator->Allocate(sizeof(float), __alignof(float));
    *f = 3.1415f;
    printf("f = %f\n", *f);
    printf("Addr f: %u\n", f);
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    test_t *t = (test_t *) l_pAllocator->Allocate(sizeof(test_t), __alignof(test_t));
    t->x = t->y = t->z = 3.1415f;
    printf("(x, y, z) = (%f, %f %f)\n", t->x, t->y, t->z);
    printf("Addr t: %u\n", t);
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    l_pAllocator->Deallocate(t);
    printf("Deallocate(t)\n");
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    l_pAllocator->Deallocate(f);
    printf("Deallocate(f)\n");
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    l_pAllocator->Deallocate(i);
    printf("Deallocate(i)\n");
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    t = (test_t *) l_pAllocator->Allocate(sizeof(test_t), __alignof(test_t));
    t->x = t->y = t->z = 3.1415f;
    printf("(x, y, z) = (%f, %f %f)\n", t->x, t->y, t->z);
    printf("Addr t: %u\n", t);
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    l_pAllocator->Deallocate(t);
    printf("Deallocate(t)\n");
    printf("Used Memory: %u\n", l_pAllocator->GetUsedMemory());
    printf("===============================================\n");

    free(l_pMem);
    delete(l_pAllocator);

    system("pause");
    return(EXIT_SUCCESS);
}
