#include "StackAllocator.h"
#include <assert.h>

CStackAllocator::CStackAllocator(size_t l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_CurrentAddress = l_MemAddress;
}

CStackAllocator::~CStackAllocator()
{
    m_CurrentAddress = 0;
}

void *CStackAllocator::Allocate(size_t l_Size, uint32_t l_Alignment)
{
    uint32_t l_Offset = alignOffsetWithHeader(m_CurrentAddress, sizeof(struct AllocHeader), l_Alignment);
    size_t l_TotalSize = l_Offset + l_Size;

    if(m_UsedMemory + l_TotalSize > m_TotalSize) return nullptr;
    uintptr_t l_NewMemAddress = (uintptr_t) m_CurrentAddress + l_Offset;

    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) ((uintptr_t) l_NewMemAddress - sizeof(struct AllocHeader));
    l_AllocHeader->m_OffsetPos = (uintptr_t) m_CurrentAddress - (uintptr_t) m_BaseAddress;

    m_CurrentAddress = (void *) (l_NewMemAddress + l_Size);
    m_UsedMemory += l_TotalSize;
    m_NumAllocations++;

    return (void *) l_NewMemAddress;
}

void CStackAllocator::Deallocate(void* l_MemAddress)
{
    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) ((uintptr_t) l_MemAddress - sizeof(struct AllocHeader));

    m_UsedMemory -= (uintptr_t) m_CurrentAddress - ((uintptr_t) m_BaseAddress + l_AllocHeader->m_OffsetPos);
    m_CurrentAddress = (void *) ((uintptr_t) m_BaseAddress + l_AllocHeader->m_OffsetPos);
    m_NumAllocations--;
}