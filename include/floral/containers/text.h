#pragma once

#include "floral/stdaliases.h"

#include "fast_array.h"

namespace floral
{
// ----------------------------------------------------------------------------

template <class t_allocator>
struct fast_dynamic_text_buffer
{
    fast_dynamic_array<c8, t_allocator>			buffer;
    static c8									empty_string[1];

    fast_dynamic_text_buffer();
	fast_dynamic_text_buffer(t_allocator* allocator);

    inline c8									operator[] (ssize i);
    const c8*									begin() const;
    const c8*									end() const;

    ssize										get_size() const;
    bool										is_empty();
    void										clear();

	void										reserve(const ssize capacity);
    void										reserve(const ssize capacity, t_allocator* allocator);

    const_cstr									c_str() const;

    void										append(const_cstr str, const_cstr strEnd = nullptr);
};

template <class t_allocator>
c8 fast_dynamic_text_buffer<t_allocator>::empty_string[1]	= { 0 };

// ----------------------------------------------------------------------------
}

#include "text.hpp"
