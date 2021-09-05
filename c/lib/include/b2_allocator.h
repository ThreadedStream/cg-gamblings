#pragma once

#include "defs.hpp"



class B2Allocator{
public:
    B2Allocator() = delete;

    template <int size>
    FORCE_INLINE static void *allocate() { return allocator.Allocate(size); }

    template<void*ptr, int size>
    FORCE_INLINE static void deallocate() { allocator.Free(ptr, size); }
private:
    static b2BlockAllocator allocator;
};

