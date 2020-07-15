#pragma once

#include "floral/stdaliases.h"
#include "floral/assert/assert.h"
#include "floral/math/utils.h"

// NOTE: this is the ultimate-form of performance trade-off for both coding and execution time

namespace floral
{

// ----------------------------------------------------------------------------
// fast_fixed_array
// - allocation happen when:
//  > constructing with a specific capacity
//  > explicitly calling reserve()
// - IMPORTANT:
//  > no deallocation for the contained data, even when destroy the object
//  > the contained data is assumed of POD types, so no constructor / destructor calls either

template <class t_value, class t_allocator>
class fast_fixed_array
{
public:
	fast_fixed_array();
	explicit fast_fixed_array(t_allocator* allocator);
	fast_fixed_array(const ssize capacity, t_allocator* allocator);
	fast_fixed_array(fast_fixed_array&& other);
	~fast_fixed_array();

	void										reserve(const ssize capacity, t_allocator* newAllocator);
	void										reserve(const ssize capacity);
	void										resize(const ssize newSize);
	void										push_back(const t_value& value);
	t_value										pop_back();
	void										clear();
	/*
	 * This will free the data, reset every members to theirs default values
	 * Be careful of memory deallocation order if you are using a linear allocator.
	 */
	void										invalidate();

	const ssize									get_size() const;
	const ssize									get_capacity() const;
	const ssize									get_terminated_index() const;

	const ssize									find(const t_value& value, const ssize fromId = 0, const ssize toId = 0) const;
	const ssize									find(const t_value& value, const bool (*cmpFunc)(const t_value&, const t_value&),
													 const ssize fromId = 0, const ssize toId = 0) const;

	t_value&									at(const ssize index) const;
	t_value&									operator[](const ssize index);
	const t_value&								operator[](const ssize index) const;
	fast_fixed_array&							operator=(const fast_fixed_array& other);
	fast_fixed_array&							operator=(fast_fixed_array&& other);

	// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
	// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
	template <ssize (*t_compare_func)(t_value&, t_value&)>
	void										sort();

private:
	template <ssize (*t_compare_func)(t_value&, t_value&)>
	void										partition(ssize lo, ssize hi);

private:
	ssize										m_size;
	ssize										m_capacity;

	t_value*									m_data;
	t_allocator*								m_allocator;
};

// ----------------------------------------------------------------------------
// fast_dynamic_array
// - allocation happen when:
//  > constructing with a specific capacity
//  > explicitly calling reserve()
//  > automatically grow (both allocation and deallocation)
// - IMPORTANT:
//  > no deallocation for the contained data, even when destroy the object
//  > the contained data is assumed of POD types, so no constructor / destructor calls either
//  > suggest using with a freelist allocator

template <class t_value, class t_allocator>
class fast_dynamic_array
{
public:
	fast_dynamic_array();
	explicit fast_dynamic_array(t_allocator* allocator);
	fast_dynamic_array(const ssize capacity, t_allocator* allocator);
	fast_dynamic_array(fast_dynamic_array&& other);
	~fast_dynamic_array();

	void										push_back(const t_value& v);
	t_value										pop_back();
	void										clear();

	const ssize									get_size() const;
	const ssize									get_capacity() const;
	const ssize									get_terminated_index() const;

	const ssize									find(const t_value& value, const ssize fromId = 0, const ssize toId = 0) const;
	const ssize									find(const t_value& value, const bool (*cmpFunc)(const t_value&, const t_value&),
													 const ssize fromId = 0, const ssize toId = 0) const;

	t_value&									at(const ssize index) const;
	t_value&									operator[](const ssize index);
	const t_value&								operator[](const ssize index) const;
	fast_dynamic_array&							operator=(const fast_dynamic_array& other);
	fast_dynamic_array&							operator=(fast_dynamic_array&& other);

	void										reserve(const ssize newCapacity, t_allocator* allocator);
	void										reserve(const ssize newCapacity);

	void										resize(const ssize newSize);

	// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
	// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void										sort();

private:
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void										partition(s32 lo, s32 hi);

private:
	ssize										m_size;
	ssize										m_capacity;
	ssize										m_allocatedCapacity;

	t_value*									m_data;
	t_allocator*								m_allocator;
};

// ----------------------------------------------------------------------------
}

#include "fast_array.hpp"
