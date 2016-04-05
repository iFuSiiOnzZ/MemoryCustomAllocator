#pragma once
#include <new>
#include <cmath>

typedef signed         char      int8_t;
typedef signed        short      int16_t;
typedef signed         int       int32_t;
typedef signed      long long    int64_t;

typedef unsigned       char     uint8_t;
typedef unsigned      short     uint16_t;
typedef unsigned       int      uint32_t;
typedef unsigned    long long   uint64_t;

typedef               float     float32;
typedef              double     float64;

#if _WIN64
typedef unsigned    long long   uintptr_t;
#else
typedef unsigned       int      uintptr_t;
#endif


class CAllocator
{
    protected:
        size_t m_UsedMemory;
        size_t m_NumAllocations;

        size_t m_TotalSize;
        void   *m_BaseAddress;

    private:

    public:
        CAllocator(size_t Size, void *l_MemAddress);
        virtual ~CAllocator();

        virtual void *Allocate(size_t Size, uint32_t Aligment) = 0;
        virtual void  Deallocate(void *MemAddress) = 0;

        inline size_t GetSize(void) { return m_TotalSize; }
        inline size_t GetUsedMemory(void) { return m_UsedMemory; }
        inline size_t GetNumAllocations(void) { return m_NumAllocations; }

        template <class T, class... ArgsType> T *MakeNew(ArgsType... Args) { return new (Allocate(sizeof(T), __alignof(T))) T(Args...); }
        template <class T> void  MakeDelete(T *ClassPtr) { if(ClassPtr){ ClassPtr->~T(); Deallocate(ClassPtr); } }

        template <class T> T *New(size_t NumElements = 1) { return (T *) Allocate(sizeof(T) * NumElements, __alignof(T)); }
        void Delete(void *l_MemAddress) { Deallocate(l_MemAddress); }
};

inline uint32_t alignOffset(void *l_Address, uint32_t l_Alignment = 4)
{
    uint32_t l_Offset = l_Alignment - ((uintptr_t) l_Address & (l_Alignment - 1));
    return (l_Offset == l_Alignment) ? 0 : l_Offset;
}

inline uint32_t alignOffsetWithHeader(void *l_Address, uint32_t l_HeaderSize, uint32_t l_Alignment = 4)
{
    unsigned int l_Offset = alignOffset(l_Address, l_Alignment);
    if(l_HeaderSize > l_Offset) l_Offset += l_Alignment * (uint32_t) ceil((float32) (l_HeaderSize - l_Offset) / (float32) l_Alignment);

    return l_Offset;
}
