#include "value.h"
#include "memory.h"
#include <stdio.h>

void array_init(Value_Array *array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void array_add(Value_Array *array, Value value) {
    if (array->capacity < array->count + 1) {
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(array->capacity);
        array->values =
            GROW_ARRAY(Value, array->values, old_capacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void array_free(Value_Array *array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    array_init(array);
}

void print_value(Value value) { printf("%g", value); }