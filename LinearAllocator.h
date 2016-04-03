#pragma once
#include "Allocator.h"

class CLinearAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;

    public:
        CLinearAllocator(size_t l_Size, void *l_MemAddress);
        ~CLinearAllocator();

        void *Allocate(size_t l_Size, uint32_t l_Alignment);
        void  Deallocate(void *l_MemAddress);
        void  Reset(void);
};
