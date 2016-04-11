#include "FreeListAllocator.h"
#include <stdio.h>

CFreeListAllocator::CFreeListAllocator(size_t l_Size, void *l_MemAddress) : CAllocator(l_Size, l_MemAddress)
{
    m_FreeBlocks = (struct FreeBlock *) l_MemAddress;

    m_FreeBlocks->m_Size = l_Size;
    m_FreeBlocks->m_Next = 0;
}

CFreeListAllocator::~CFreeListAllocator()
{
    m_FreeBlocks = 0;
}

void *CFreeListAllocator::Allocate(size_t l_Size, uint32_t l_Alignment)
{
    uint32_t l_Offset = 0;
    size_t l_TotalSize = 0;

    struct FreeBlock *l_PrevBlock = nullptr;
    struct FreeBlock *l_FreeBlock = m_FreeBlocks;

    while(l_FreeBlock != 0)
    {
        l_Offset = alignOffsetWithHeader(l_FreeBlock, sizeof(struct AllocHeader), l_Alignment);
        l_TotalSize = l_Size + l_Offset;

        if(l_FreeBlock->m_Size >= l_TotalSize) break;

        l_PrevBlock = l_FreeBlock;
        l_FreeBlock = l_FreeBlock->m_Next;
    }

    if(l_FreeBlock == 0) return 0;

    if(l_FreeBlock->m_Size - l_TotalSize <= sizeof(struct FreeBlock))
    {
        l_TotalSize = l_FreeBlock->m_Size;

        if(l_PrevBlock != 0) l_PrevBlock->m_Next = l_FreeBlock->m_Next;
        else m_FreeBlocks = l_FreeBlock->m_Next;
    }
    else
    {
        struct FreeBlock *l_NextFreeBlock = (struct FreeBlock *) ((uintptr_t) l_FreeBlock + l_TotalSize);

        l_NextFreeBlock->m_Size = l_FreeBlock->m_Size - l_TotalSize;
        l_NextFreeBlock->m_Next = l_FreeBlock->m_Next;

        if(l_PrevBlock != 0) l_PrevBlock->m_Next = l_NextFreeBlock;
        else m_FreeBlocks = l_NextFreeBlock;
    }

    uintptr_t l_NewMemAddress = (uintptr_t) l_FreeBlock + l_Offset;
    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) (l_NewMemAddress - sizeof(struct AllocHeader));

    l_AllocHeader->m_Size = l_Size + l_Offset;
    l_AllocHeader->m_Alignment = l_Offset;

    m_UsedMemory += l_Size + l_Offset;
    m_NumAllocations++;

    return (void *) l_NewMemAddress;
}

void CFreeListAllocator::Deallocate(void *l_MemAddress)
{
    if(l_MemAddress == 0) return;
    struct AllocHeader *l_AllocHeader = (struct AllocHeader *) ((uintptr_t) l_MemAddress - sizeof(struct AllocHeader));

    size_t l_BlockStart = (uintptr_t) l_MemAddress - l_AllocHeader->m_Alignment;
    size_t l_BlockEnd = l_BlockStart + l_AllocHeader->m_Size;

    struct FreeBlock *l_PrevBlock = nullptr;
    struct FreeBlock *l_FreeBlock = m_FreeBlocks;

    while(l_FreeBlock != 0 && (uintptr_t) l_FreeBlock < l_BlockEnd)
    {
        l_PrevBlock = l_FreeBlock;
        l_FreeBlock = l_FreeBlock->m_Next;
    }

    if(l_PrevBlock == nullptr)
    {
        l_PrevBlock = (FreeBlock*) l_BlockStart;

        l_PrevBlock->m_Size = l_AllocHeader->m_Size;
        l_PrevBlock->m_Next = m_FreeBlocks;

        m_FreeBlocks = l_PrevBlock;
    }
    else if((uintptr_t) l_PrevBlock + l_PrevBlock->m_Size == l_BlockStart)
    {
        l_PrevBlock->m_Size += l_AllocHeader->m_Size;
    }
    else
    {
        FreeBlock* temp = (FreeBlock*) l_BlockStart;

        temp->m_Size = l_AllocHeader->m_Size;
        temp->m_Next = l_PrevBlock->m_Next;

        l_PrevBlock->m_Next = temp;
        l_PrevBlock = temp;
    }

    if( l_PrevBlock != 0 && (uintptr_t) l_FreeBlock == l_BlockEnd)
    {
        l_PrevBlock->m_Size += l_FreeBlock->m_Size;
        l_PrevBlock->m_Next = l_FreeBlock->m_Next;
    }

    m_UsedMemory -= l_AllocHeader->m_Size;
    m_NumAllocations--;
}