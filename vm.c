#include "vm.h"
#include "common.h"
#include "debug.h"
#include "compiler.h"
#include <stdio.h>

VM vm;

static Interpret_Result run() {
#ifdef DEBUG_TRACE_EXECUTION
    printf("[Debug] Interpreting...\n");
#endif

    // @Note The beating heart of the VM.

    // @Note Helper macros...
    // I don't event know that we can pass the op to a macro before reading this
    // book... Now I know macros are just plain text to be compiled...
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]);
#define BINARY_OP(op)                                                          \
    do {                                                                       \
        double r = pop();                                                      \
        double l = pop();                                                      \
        push(l op r);                                                          \
    } while (false)
    // @Note This do-while stuff below is pretty funny.
    // Special Case:
    //      #define WAKE_UP() { make_coffee(); drink_coffee();}
    //      if (morning)
    //          WAKE_UP();
    //      else
    //          sleep_in();

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

            // @Note All of these operators are Stack-Based!!!
        case OP_ADD:
            BINARY_OP(+);
            break;
        case OP_SUBTRACT:
            BINARY_OP(-);
            break;
        case OP_MULTIPLY:
            BINARY_OP(*);
            break;
        case OP_DIVIDE:
            BINARY_OP(/);
            break;

        case OP_NEGATE:
            push(-pop());
            break;

        default:
            break;
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

static void reset_stack() { vm.stack_top = vm.stack; }
// FILE_SCOPE

void vm_init() { reset_stack(); }

void vm_free() {}

Interpret_Result interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}

void push(Value value) {
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop() {
    vm.stack_top--;
    return *vm.stack_top;
}