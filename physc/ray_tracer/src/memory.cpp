#include "../include/memory.h"

AllocatorWrapper* AllocatorWrapper::singleton = nullptr;

AllocatorWrapper* AllocatorWrapper::getSingleton() {
    return singleton;
}

AllocatorWrapper::AllocatorWrapper() {
    singleton = this;
}

