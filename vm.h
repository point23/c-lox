#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} Interpret_Result;

typedef struct {
    Chunk *chunk;
    uint8_t *ip; // Instruction Pointer: the location of the instruction
                 // currently being executed, also known as PC(program counter).

    Value stack[STACK_MAX];
    Value *stack_top;
} VM;

void vm_init();
void vm_free();
Interpret_Result interpret(const char* source);

void push(Value value);
Value pop();

#endif