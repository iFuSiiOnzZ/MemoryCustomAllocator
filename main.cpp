#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Allocator.h"
#include "StackAllocator.h"
#include "LinearAllocator.h"
#include "FreeListAllocator.h"

#define B   1
#define KB  1024
#define MB  (1024 * KB)
#define GB  (1024 * MB)

#define ASSERT(x) if(!(x)){*(int *) 0 = 0; }

struct vector3_t
{
    float x, y, z;
};

struct ArgsTest
{
    float x, y, z;

    ArgsTest(void) : x(1.0f), y(2.0f), z(3.0f){}
    ArgsTest(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
};

void StackAllocatorTest()
{
    void *l_pMem = VirtualAlloc((void *) 10000000000, 64, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    uint32_t t = sizeof(uintptr_t) == 4 ? 4 : 8;
    CStackAllocator Allocator(64, l_pMem);

    int *f = (int *)Allocator.New<int>();
    Allocator.Deallocate(f);

    vector3_t *a = (vector3_t *)Allocator.Allocate(sizeof(vector3_t), 4);
    uint32_t s = 12 + t; ASSERT(s == Allocator.GetUsedMemory());

    int *b = (int *)Allocator.Allocate(sizeof(int), 4);
    s = s + 4 + t;  ASSERT(s == Allocator.GetUsedMemory());

    Allocator.Deallocate(b);
    s = s - 4 - t; ASSERT(s == Allocator.GetUsedMemory());

    Allocator.Deallocate(a);
    ASSERT(0 == Allocator.GetUsedMemory());
    
    VirtualFree(l_pMem, 0, MEM_RELEASE);
}

void LinearAllocatorTest()
{
    void *l_pMem = VirtualAlloc((void *)10000000000, 64, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    CLinearAllocator Allocator(512, l_pMem);

    vector3_t *a = (vector3_t *)Allocator.Allocate(sizeof(vector3_t), 4);
    uint32_t s = 12; ASSERT(s == Allocator.GetUsedMemory());

    int *b = (int *)Allocator.Allocate(sizeof(int), 4);
    s = s + 4;  ASSERT(s == Allocator.GetUsedMemory());

    Allocator.Reset();
    ASSERT(0 == Allocator.GetUsedMemory());

    a = Allocator.New<vector3_t>(10);
    ASSERT(sizeof(vector3_t) * 10 == Allocator.GetUsedMemory());

    for(size_t i = 0; i < 10; ++i)
    {
        a[i].x = (float) i;
    }

    for (size_t i = 0; i < 10; ++i)
    {
       ASSERT(a[i].x == (float)i);
    }

    ArgsTest *pArgsTest = Allocator.MakeNew<ArgsTest>(3.0f, 2.0f, 1.0f);
    ASSERT(sizeof(ArgsTest) + sizeof(vector3_t) * 10 == Allocator.GetUsedMemory());


    ASSERT(pArgsTest->x == 3.0f);
    ASSERT(pArgsTest->y == 2.0f);
    ASSERT(pArgsTest->z == 1.0f);

    VirtualFree(l_pMem, 0, MEM_RELEASE);
}

int main(int argc, char *argv[])
{
    StackAllocatorTest();
    LinearAllocatorTest();

    system("pause");
    return(EXIT_SUCCESS);
}