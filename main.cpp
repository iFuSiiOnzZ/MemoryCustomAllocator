#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Allocator.h"
#include "LinearAllocator.h"

#define B   1
#define KB  1024
#define MB  1024 * 1024
#define GB  1024 * 1024 * 1024

int main(int argc, char *argv[])
{
    void *l_pMem = (void *) malloc (GB);
    CAllocator *l_pAllocator = new CLinearAllocator(GB, l_pMem);


    free(l_pMem);
    delete(l_pAllocator);

    system("pause");
    return(EXIT_SUCCESS);
}
