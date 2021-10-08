#pragma once

#include "../../shared/defs.hpp"


class AllocatorWrapper {
public:
    static AllocatorWrapper* getSingleton();

    AllocatorWrapper();

    inline void *allocate(size_t size) { return allocator.Allocate(size); }

    inline void deallocate(void* ptr, size_t size) { return allocator.Free(ptr, size); }

private:
    static AllocatorWrapper* singleton;
    b2BlockAllocator allocator;
};