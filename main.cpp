#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Allocator.h"
#include "LinearAllocator.h"

#define B   1
#define KB  1024
#define MB  1024 * 1024
#define GB  1024 * 1024 * 1024

struct Foo
{
    float x;
    float y;
    float z;

    Foo(float a, float b, float c) : x(a), y(b), z(c){}
};

class Bar
{
    public:
        Bar   (int a, int b) { printf("%d : %d\n", a, b); }
        ~Bar  () {}
};

int main(int argc, char *argv[])
{
    void *l_pMem = (void *) malloc (GB);
    CAllocator *l_pAllocator = new CLinearAllocator(GB, l_pMem);

    printf("(sizeof(Bar): %d\n", sizeof(Bar));
    Bar *b = (Bar *) l_pAllocator->Allocate(sizeof(Bar), 4);
    new (b) Bar(1, 2); // Call constructor

    printf("NumAllocations: %d\n", l_pAllocator->GetNumAllocations());
    printf("UsedMemory: %d\n", l_pAllocator->GetUsedMemory());
    printf("===================\n\n");

    Foo *f1 = (Foo *) l_pAllocator->Allocate(sizeof(Foo), 4);
    f1->x = 1.0f; f1->y = 2.0f; f1->z = 3.0f;
    printf("(x, y ,z) : (%f, %f, %f)\n", f1->x, f1->y, f1->z);

    Foo *f2 = (Foo *) l_pAllocator->Allocate(sizeof(Foo), 4);
    new (f2) Foo(4.0f, 5.0f, 6.0f); // Call constructor
    printf("(x, y ,z) : (%f, %f, %f)\n", f2->x, f2->y, f2->z);

    printf("NumAllocations: %d\n", l_pAllocator->GetNumAllocations());
    printf("UsedMemory: %d\n", l_pAllocator->GetUsedMemory());
    printf("===================\n\n");

    int *i = (int *) l_pAllocator->Allocate(sizeof(int), 4);
    *i = 10; printf("i: %d\n", *i);

    printf("NumAllocations: %d\n", l_pAllocator->GetNumAllocations());
    printf("UsedMemory: %d\n", l_pAllocator->GetUsedMemory());
    printf("===================\n\n");

    float *f = (float *) l_pAllocator->Allocate(sizeof(float), 4);
    *f = -9.81f; printf("f: %f\n", *f);

    printf("NumAllocations: %d\n", l_pAllocator->GetNumAllocations());
    printf("UsedMemory: %d\n", l_pAllocator->GetUsedMemory());
    printf("===================\n\n");

    double *d = (double *) l_pAllocator->Allocate(sizeof(double), 8);
    *d = -3.14; printf("d: %lf\n", *d);

    printf("NumAllocations: %d\n", l_pAllocator->GetNumAllocations());
    printf("UsedMemory: %d\n", l_pAllocator->GetUsedMemory());
    printf("===================\n\n");

    free(l_pMem);
    system("pause");
    return(EXIT_SUCCESS);
}
