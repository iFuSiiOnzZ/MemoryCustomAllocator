#pragma once
#include "Allocator.h"

class CFreeListAllocator : public CAllocator
{
    private:
        struct AllocHeader
        {
            size_t m_Size;
            uint32_t m_Alignment;
        };

        struct FreeBlock
        {
            size_t m_Size;
            FreeBlock *m_Next;
        };

        struct FreeBlock *m_FreeBlocks;

    public:
        CFreeListAllocator(size_t l_Size, void *l_MemAddress);
        ~CFreeListAllocator();

        void *Allocate(size_t l_Size, uint32_t l_Alignment);
        void  Deallocate(void *l_MemAddress);
};
