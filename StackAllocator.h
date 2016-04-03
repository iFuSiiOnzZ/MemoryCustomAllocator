#pragma once
#include "Allocator.h"

class CStackAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;

        struct AllocHeader
        {
            size_t m_OffsetPos;
        };

    public:
        CStackAllocator(size_t l_Size, void *l_MemAddress);
        ~CStackAllocator();

        void *Allocate(size_t l_Size, uint32_t l_Alignment);
        void  Deallocate(void *l_MemAddress);
};
