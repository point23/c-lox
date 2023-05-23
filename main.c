#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
    vm_init();

    Chunk chunk;
    chunk_init(&chunk);

    {     // return -1.2
        { // @Note Register that constant value.
            int idx = add_constant(&chunk, 1.2);
            chunk_write(&chunk, OP_CONSTANT, 123);
            chunk_write(&chunk, idx, 123);
        }

        // Unary neg operation.
        chunk_write(&chunk, OP_NEGATE, 123);

        // Return that value.
        chunk_write(&chunk, OP_RETURN, 123);
    }

    disassemble_chunk(&chunk, "test chunk");

    interpret(&chunk);

    vm_free();
    chunk_free(&chunk);

    return 0;
}