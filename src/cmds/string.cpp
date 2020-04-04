#include "floral/cmds/string.h"

#include "floral/assert/assert.h"

#include "floral/containers/fast_array.h"

namespace floral
{
// ---------------------------------------------

static alloc_string_func_t s_allocate_string_func = nullptr;
static free_string_func_t s_free_string_func = nullptr;

struct string_db
{
	//floral::array_view<cstr>					stringList;
};

static string_db s_string_db;

cstr allocate_string(size_t i_length)
{

}

void free_string(cstr i_str)
{
}

void initialize_string_db(alloc_string_func_t i_allocFunc, free_string_func_t i_freeFunc)
{
	FLORAL_ASSERT_MSG(s_allocate_string_func == nullptr && s_free_string_func == nullptr, "Already initialized!");

	s_allocate_string_func = i_allocFunc;
	s_free_string_func = i_freeFunc;
}

// ---------------------------------------------
}
