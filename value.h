#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value *values;
} Value_Array;

void array_init(Value_Array *array);
void array_add(Value_Array *array, Value value);
void array_free(Value_Array *array);

void print_value(Value value);

#endif