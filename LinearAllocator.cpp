#include "LinearAllocator.h"

CLinearAllocator::CLinearAllocator(size_t l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_CurrentAddress = l_MemAddress;
}

CLinearAllocator::~CLinearAllocator()
{
    m_CurrentAddress = 0;
}

void *CLinearAllocator::Allocate(size_t l_Size, uint32_t l_Alignment)
{
    uint32_t l_Offset = alignOffset(m_CurrentAddress, l_Alignment);
    size_t l_TotalSize = l_Offset + l_Size;

    if(m_UsedMemory + l_TotalSize > m_TotalSize) return nullptr;
    uintptr_t l_NewMemAddress = (uintptr_t) m_CurrentAddress + l_Offset;

    m_CurrentAddress = (void *) (l_NewMemAddress + l_Size);
    m_UsedMemory += l_TotalSize;
    m_NumAllocations++;

    return (void *) l_NewMemAddress;
}

void CLinearAllocator::Deallocate(void *l_MemAddress)
{
}

void CLinearAllocator::Reset(void)
{
    m_CurrentAddress = m_BaseAddress;
    m_NumAllocations = 0;
    m_UsedMemory = 0;
}