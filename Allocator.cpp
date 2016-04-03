#include "Allocator.h"

CAllocator::CAllocator(size_t l_Size, void *l_MemAddress)
{
    m_TotalSize = l_Size;
    m_BaseAddress = l_MemAddress;

    m_UsedMemory = 0;
    m_NumAllocations = 0;
}

CAllocator::~CAllocator()
{
    m_TotalSize = 0;
    m_BaseAddress = nullptr;

    m_UsedMemory = 0;
    m_NumAllocations = 0;
}