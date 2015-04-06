#pragma once
#include "Allocator.h"

class CStackAllocator : public CAllocator
{
    private:
        void *m_CurrentAddress;
        unsigned int  m_SizeOfOffset;
        
    public:
        CStackAllocator(unsigned int l_Size, void *l_MemAddress);
        ~CStackAllocator();
        
        void *Allocate(unsigned int l_Size, unsigned int l_Aligment);
        void  Deallocate(void *l_MemAddress);
};
