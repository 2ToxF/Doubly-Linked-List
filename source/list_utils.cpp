#include <stdlib.h>
#include <string.h>

#include "list_utils.h"


void* MyRecalloc(void* mem_ptr, size_t new_size, size_t num_of_used_bytes)
{
    mem_ptr = realloc(mem_ptr, new_size);
    memset((char*) mem_ptr + num_of_used_bytes, 0, new_size - num_of_used_bytes);
    return mem_ptr;
}
