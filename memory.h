#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// Handle lower-level memory operation.
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity)*2)

// Allocate a new space and copy the old stuff.
#define GROW_ARRAY(type, pointer, old_count, new_count)                        \
    (type *)reallocate(pointer, sizeof(type) * (old_count),                    \
                       sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count)                                   \
    reallocate(pointer, sizeof(type) * (old_count), 0);

/*
    old new     =>    op
     0  n-z          new block
    n-z  0           free
    n-z  >           shrink
    n-z  <           grow
*/
void *reallocate(void *pointer, size_t old_size, size_t new_size);

#endif