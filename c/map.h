//
// Created by threadedstream on 8/16/21.
//

#ifndef PHYSC_MAP_H
#define PHYSC_MAP_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Brief description of inner-workings of a map
// The map will be implemented as an array of structures indexed by a key
// In order to avoid collisions, proper key generation algorithm should be used
// The algorithm should generate unique key given spatial bounds of an array.
// For example, if array (or slice in Go-lingo) has bounds [0, 20], the algorithm
// will return a unique index with a small probability of a collision.
// I should note that at the moment I'm ignorant of methods(algorithms) for
// fulfilling the task I managed to describe above.

// for now, i'm going to stick to naive implementation
// here's a flow: adding a value to hash table is supplied with
// computing a hash value for the key, subsequently using the result
// of operation as an index for array the value will be put into.


int32_t hash(const char* key, int32_t bounds);

void testHash();


#endif //PHYSC_MAP_H
