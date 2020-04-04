#include "floral/assert/assert.h"

namespace floral
{
// ---------------------------------------------

template <class TAllocator>
struct helich_allocator
{
	static TAllocator* allocator;

	static voidptr alloc_memory(const size i_size)
	{
		return allocator->allocate(i_size);
	}

	static void free_memory(voidptr i_data)
	{
		allocator->free(i_data);
	}
};

template <class TAllocator>
TAllocator* helich_allocator<TAllocator>::allocator = nullptr;

template <class TAllocator>
void initialize_string_db(TAllocator* i_allocator)
{
	FLORAL_ASSERT_MSG(helich_allocator<TAllocator>::allocator == nullptr, "An allocator of this type has been used before!");
	helich_allocator<TAllocator>::allocator = i_allocator;
	initialize_string_db(
			&helich_allocator<TAllocator>::alloc_memory,
			&helich_allocator<TAllocator>::free_memory);
}

// ---------------------------------------------
}
