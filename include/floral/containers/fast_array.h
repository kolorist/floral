#pragma once

#include "floral/stdaliases.h"
#include "floral/assert/assert.h"

// NOTE:	this is the ultimate-form of performance trade-off for both coding and execution time

namespace floral
{

// for now, the only main difference between fast_fixed_array and fixed_array
// is fast_fixed_array does not release data when being destroyed
template <class t_value, class t_allocator>
class fast_fixed_array
{
protected:
	typedef			t_value					value_t;
	typedef			const t_value			const_value_t;
	typedef			t_value*				pointer_t;
	typedef			const t_value*			const_pointer_t;
	typedef			t_value&				reference_t;

	typedef			t_allocator				allocator_t;
	typedef			allocator_t*			allocator_ptr_t;

public:
	fast_fixed_array()
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr)
		, m_allocator(nullptr)
	{ }

	explicit fast_fixed_array(allocator_ptr_t i_myAllocator)
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr)
		, m_allocator(i_myAllocator)
	{
		// nothing
	}

	fast_fixed_array(const ssize i_capacity, allocator_ptr_t i_myAllocator)
		: m_allocator(i_myAllocator)
	{
		reserve(i_capacity);
	}

	// C++11 move constructor
	fast_fixed_array(fast_fixed_array&& i_other)
		: m_capacity(i_other.m_capacity)
		, m_size(i_other.m_size)
		, m_allocator(i_other.m_allocator)
		, m_data(i_other.m_data)
	{
		i_other.m_capacity = 0;
		i_other.m_size = 0;
		i_other.m_allocator = nullptr;
		i_other.m_data = nullptr;
	}

	~fast_fixed_array()
	{
		// do nothing
	}

	// deprecated
	void init(const ssize i_capacity, allocator_ptr_t i_allocator)
	{
		FLORAL_ASSERT_MSG((int)i_capacity > 0, "Cannot create an non-positive-capacity array");
		m_capacity = i_capacity;
		m_allocator = i_allocator;
		m_size = 0;
		m_data = m_allocator->template allocate_array<value_t>(m_capacity);
	}

	void reserve(const ssize i_capacity, allocator_ptr_t i_newAllocator)
	{
		m_allocator = i_newAllocator;
		reserve(i_capacity);
	}

	void reserve(const ssize i_capacity)
	{
		FLORAL_ASSERT_MSG(m_allocator != nullptr, "Cannot reserve memory for array without an allocator");
		FLORAL_ASSERT_MSG((int)i_capacity > 0, "Cannot create an non-positive-capacity array");
		m_capacity = i_capacity;
		m_size = 0;
		m_data = m_allocator->template allocate_array<value_t>(m_capacity);
	}

	inline void push_back(const t_value& i_value)
	{
		FLORAL_ASSERT_MSG(m_size + 1 <= m_capacity, "Not enough array memory for push_back");
		m_data[m_size] = i_value;
		m_size++;
	}

	t_value pop_back() {
		FLORAL_ASSERT_MSG(m_size > 0, "Cannot pop_back an empty array");
		t_value retVal = m_data[m_size - 1];
		m_size--;
		return retVal;
	}

	inline void empty()
	{
		m_size = 0;
	}

	inline void clear()
	{
		m_size = 0;
	}

	inline const ssize							get_size() const					{ return m_size; }
	inline const ssize							get_capacity() const				{ return m_capacity; }
	inline const ssize							get_terminated_index() const		{ return m_size; }
	inline reference_t at(const ssize index) const
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const ssize find(const t_value& value,
		bool (*cmpFunc)(const t_value&, const t_value&),
		const ssize fromId = 0, const ssize toId = 0) const
	{
		ssize from = fromId;
		ssize to = toId > 0 ? toId : m_size;

		for (ssize i = from; i < to; i++) {
			if (cmpFunc(m_data[i], value))
				return i;
		}
		return m_size;
	}

	const ssize find(const t_value& value, const ssize fromId = 0, const ssize toId = 0) const {
		ssize from = fromId;
		ssize to = toId > 0 ? toId : m_size;

		for (ssize i = from; i < to; i++) {
			if (m_data[i] == value)
				return i;
		}
		return m_size;
	}

	// operator overloading
	inline reference_t operator[](const ssize index)
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	inline const t_value& operator[](const ssize index) const
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	// copy assignment
	fast_fixed_array& operator=(const fast_fixed_array& i_other)
	{
		if (this != &i_other) {
			FLORAL_ASSERT_MSG(m_capacity >= i_other.m_size, "Not enough capacity in destination array");
			empty();
			for (ssize i = 0; i < i_other.m_size; i++) {
				m_data[i] = i_other.m_data[i];
			}
			m_size = i_other.m_size;
		}
		return *this;
	}

	// move assignment
	fast_fixed_array& operator=(fast_fixed_array&& i_other)
	{
		m_capacity = i_other.m_capacity;
		m_size = i_other.m_size;
		m_allocator = i_other.m_allocator;
		m_data = i_other.m_data;

		i_other.m_capacity = 0;
		i_other.m_size = 0;
		i_other.m_allocator = nullptr;
		i_other.m_data = nullptr;
		return *this;
	}

	// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
	// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
	template <ssize (*t_compare_func)(t_value&, t_value&)>
	void sort()
	{
		partition<t_compare_func>(0, m_size - 1);
	}

	inline void resize(const ssize i_newSize)
	{
		FLORAL_ASSERT_MSG(i_newSize <= m_capacity, "Invalid new ssize!");
		m_size = i_newSize;
	}

	// depreacted
	void resize_ex(const ssize newSize) {
		FLORAL_ASSERT_MSG(newSize <= m_capacity, "Invalid new ssize!");
		m_size = newSize;
	}

private:
	template <ssize (*t_compare_func)(t_value&, t_value&)>
	void partition(ssize lo, ssize hi)
	{
		if (lo >= hi) {
			return;
		}
		// we choose pivot to be the center element (not the median-value) because of the simplicity
		ssize pivot = lo + (hi - lo) / 2;
		t_value pivotVal = m_data[pivot];
		ssize i = lo, j = hi;
		while (i <= j) {
			while (t_compare_func(m_data[i], pivotVal) > 0) i++;
			while (t_compare_func(m_data[j], pivotVal) < 0) j--;
			if (i <= j) {
				if (i < j) {
					t_value tmp = m_data[i];
					m_data[i] = m_data[j];
					m_data[j] = tmp;
				}
				i++; j--;
			}
		}
		partition<t_compare_func>(lo, j);
		partition<t_compare_func>(i, hi);
	}

private:
	ssize									m_size;
	ssize									m_capacity;

	pointer_t								m_data;
	allocator_ptr_t							m_allocator;
};

}

#include "fast_array.hpp"
