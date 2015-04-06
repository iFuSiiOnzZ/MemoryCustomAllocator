#include "StackAllocator.h"

CStackAllocator::CStackAllocator(unsigned int l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_CurrentAddress = l_MemAddress;
    m_SizeOfOffset = sizeof(unsigned int);
}

CStackAllocator::~CStackAllocator()
{
    m_CurrentAddress = nullptr;
    m_SizeOfOffset = 0;
}

void *CStackAllocator::Allocate(unsigned int l_Size, unsigned int l_Aligment)
{
    l_Size += m_SizeOfOffset;
    unsigned int l_CurrentOffset =  (unsigned int) ((uintptr_t) m_CurrentAddress - (uintptr_t) m_MemAddress);

    uintptr_t l_Offset = l_Aligment - (((uintptr_t) m_CurrentAddress) & ((uintptr_t) l_Aligment - 1));
    l_Offset = (l_Offset == l_Aligment) ? 0 : l_Offset;

    if(m_UsedMemory + l_Offset + l_Size > m_Size) return nullptr;

    uintptr_t l_NewMemAddress = (uintptr_t) m_CurrentAddress + l_Offset;
    *((unsigned int *) l_NewMemAddress) = l_CurrentOffset;

    m_CurrentAddress = (void *) (l_NewMemAddress + l_Size);
    m_UsedMemory += l_Size + l_Offset;
    m_NumAllocations++;

    return (void *) (l_NewMemAddress + m_SizeOfOffset);
}

void CStackAllocator::Deallocate(void* l_MemAddress)
{
    unsigned int l_CurrentOffset = *((unsigned int *)((uintptr_t) l_MemAddress - m_SizeOfOffset));

    m_UsedMemory -= ((uintptr_t) m_CurrentAddress - ((uintptr_t) l_MemAddress - m_SizeOfOffset));
    m_CurrentAddress = (void *) ((uintptr_t) m_MemAddress + l_CurrentOffset);
    m_NumAllocations--;
}
