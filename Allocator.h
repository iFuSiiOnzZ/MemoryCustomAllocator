#pragma once
#include <new>

class CAllocator 
{
    protected:
        unsigned int m_UsedMemory;
        unsigned int m_NumAllocations;

        unsigned int m_Size;
        void         *m_MemAddress;
        
    private:
        
    public:
        CAllocator(unsigned int l_Size, void *l_MemAddress);
        virtual ~CAllocator();
        
        virtual void *Allocate(unsigned int l_Size, unsigned int Aligment) = 0;
        virtual void  Deallocate(void *l_MemAddress) = 0;

        unsigned int GetSize(void);
        unsigned int GetUsedMemory(void);
        unsigned int GetNumAllocations(void);
};

