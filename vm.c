#include "vm.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>

VM vm;

static Interpret_Result run() {
#ifdef DEBUG_TRACE_EXECUTION
    printf("Debug Interpreting...\n");
#endif

    // @Note The beating heart of the VM.
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]);

    for (;;) {

        // Diagnostic logiging.
#ifdef DEBUG_TRACE_EXECUTION
        printf("stack be like:  ");
        for (Value *slot = vm.stack; slot < vm.stack_top; slot++) {
            printf("[ ");
            print_value(*slot);
            printf(" ]");
        }
        printf("\n");

        disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        // Decoding/Dispatching the instructions.
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
        case OP_CONSTANT:
            Value constant = READ_CONSTANT();
            push(constant);
            break;

        case OP_RETURN:
            print_value(pop());
            printf("\n");
            return INTERPRET_OK;

        case OP_NEGATE:
            push(-pop());
            break;

        default:
            break;
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

static void reset_stack() { vm.stack_top = vm.stack; }
// FILE_SCOPE

void vm_init() { reset_stack(); }

void vm_free() {}

Interpret_Result interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value) {
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop() {
    vm.stack_top--;
    return *vm.stack_top;
}