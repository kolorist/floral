#pragma once

#include "floral/stdaliases.h"

// NOTE:	this is the ultimate-form of performance trade-off for both coding and execution time

namespace floral {
	template <class t_value, class t_allocator>
	struct fast_fixed_array {

		fast_fixed_array()
			: capacity(0)
			, current_size(0)
			, data_allocator(nullptr)
		{ }

		explicit fast_fixed_array(const u32 i_capacity)
			: capacity(i_capacity)
			, current_size(0)
			, data_allocator(nullptr)
		{ }

		// array data
		t_value*								data;

		// array internal information
		u32										capacity;
		u32										current_size;
		t_allocator*							data_allocator;
	};
	
	template <class t_value, const u32 t_capacity>
	struct fast_inplace_array {

		fast_inplace_array()
			: capacity(t_capacity)
			, current_size(0)
		{ }

		// array data
		t_value									data[t_capacity];
		
		// array internal information
		const u32								capacity;
		u32										current_size;
	};

	// fast_fixed_array service functions
	template <class t_value, class t_allocator>
	void init_fixed_array(fast_fixed_array<t_value, t_allocator>& i_array, t_allocator& i_allocator);

	template <class t_value, class t_allocator>
	void init_fixed_array(fast_fixed_array<t_value, t_allocator>& i_array, const u32 i_capacity, t_allocator& i_allocator);

	// general service functions
	template <class t_fast_array, class t_value>
	void push_back(t_fast_array& i_array, const t_value& i_value);

	template <class t_fast_array>
	void empty(t_fast_array& i_array);
}

#include "fast_array.hpp"