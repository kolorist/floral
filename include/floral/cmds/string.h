#pragma once

#include "floral/stdaliases.h"

namespace floral
{
// ---------------------------------------------
// WARNING: this is not thread-safe!!!

typedef voidptr									(*alloc_string_func_t)(const size i_size);
typedef void									(*free_string_func_t)(voidptr i_data);

template <class TAllocator>
void											initialize_string_db(TAllocator* i_allocator);
void											initialize_string_db(alloc_string_func_t i_allocFunc, free_string_func_t i_freeFunc);

// ---------------------------------------------
}

#include "string.inl"
