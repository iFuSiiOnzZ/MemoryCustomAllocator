#include "StackAllocator.h"
#include <assert.h>

CStackAllocator::CStackAllocator(unsigned int l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_CurrentAddress = l_MemAddress;
}

CStackAllocator::~CStackAllocator()
{
    m_CurrentAddress = 0;
}

void *CStackAllocator::Allocate(unsigned int l_Size, unsigned int l_Alignment)
{
    unsigned int l_Offset = alignOffsetWithHeader(m_CurrentAddress, l_Alignment, sizeof(struct AllocHeader));
    unsigned int l_TotalSize = l_Offset + l_Size;

    if(m_UsedMemory + l_TotalSize > m_Size) return 0;
    unsigned int l_NewMemAddress = (unsigned int) m_CurrentAddress + l_Offset;

    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) ((unsigned int) l_NewMemAddress - sizeof(struct AllocHeader));
    l_AllocHeader->m_OffsetPos = (unsigned int) m_CurrentAddress - (unsigned int) m_MemAddress;

    m_CurrentAddress = (void *) (l_NewMemAddress + l_Size);
    m_UsedMemory += l_TotalSize;
    m_NumAllocations++;

    return (void *) l_NewMemAddress;
}

void CStackAllocator::Deallocate(void* l_MemAddress)
{
    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) ((unsigned int) l_MemAddress - sizeof(struct AllocHeader));

    m_UsedMemory -= (unsigned int) m_CurrentAddress - ((unsigned int) m_MemAddress + l_AllocHeader->m_OffsetPos);
    m_CurrentAddress = (void *) ((unsigned int) m_MemAddress + l_AllocHeader->m_OffsetPos);
    m_NumAllocations--;
}