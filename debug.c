#include <stdio.h>

#include "debug.h"
#include "value.h"

static int simple_instruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constant_instruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constant_idx = chunk->code[offset];
    printf("%-16s %4d '", name, constant_idx);
    print_value(chunk->constants.values[constant_idx]);
    printf("'\n");
    return offset + 2;
}
// FILE_SCOPE

void disassemble_chunk(Chunk *chunk, const char *name) {
    printf("BEGIN == %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }

    printf("END   == %s ==\n\n", name);
}

// @Note Return value is the next offset.
int disassemble_instruction(Chunk *chunk, int offset) {
    // Offset inside the chunk.
    printf("%04d ", offset);

    { // Line information.
        if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
            printf("   | ");
        } else {
            printf("%4d ", chunk->lines[offset]);
        }
    }

    { // Instruction.
        uint8_t instruction = chunk->code[offset];
        switch (instruction) {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);

        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);

        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);

        default:
            printf("Unknown instruction %d\n", instruction);
            break;
        }
    }
}