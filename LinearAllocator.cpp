#include "LinearAllocator.h"

CLinearAllocator::CLinearAllocator(unsigned int l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_CurrentAddress = l_MemAddress;
}

CLinearAllocator::~CLinearAllocator()
{
    m_CurrentAddress = nullptr;
}

void *CLinearAllocator::Allocate(unsigned int l_Size, unsigned int l_Aligment)
{
    uintptr_t l_Offset = l_Aligment - (((uintptr_t) m_CurrentAddress) & ((uintptr_t) l_Aligment - 1));
    l_Offset = (l_Offset == l_Aligment) ? 0 : l_Offset;

    if(m_UsedMemory + l_Offset + l_Size > m_Size) return nullptr;
    uintptr_t l_NewMemAddress = (uintptr_t) m_CurrentAddress + l_Offset;
    
    m_CurrentAddress = (void *) (l_NewMemAddress + l_Size);
    m_UsedMemory += l_Size + l_Offset;
    m_NumAllocations++;

    return (void *) l_NewMemAddress;
}

void CLinearAllocator::Deallocate(void* l_MemAddress)
{
}

void CLinearAllocator::Reset(void)
{
    m_CurrentAddress = m_MemAddress;
    m_NumAllocations = 0;
    m_UsedMemory = 0;
}
