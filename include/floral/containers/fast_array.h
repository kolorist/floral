#pragma once

#include "floral/stdaliases.h"
#include "floral/assert/assert.h"
#include "floral/math/utils.h"

// NOTE:	this is the ultimate-form of performance trade-off for both coding and execution time

namespace floral
{
// ----------------------------------------------------------------------------

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
		// !!! IMPORTANT: do not free data
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

	inline void invalidate()
	{
		if (m_allocator)
		{
			if (m_data)
			{
				m_allocator->free(m_data);
			}
			m_size = 0;
			m_capacity = 0;
			m_data = nullptr;
			m_allocator = nullptr;
		}
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

// ----------------------------------------------------------------------------
// In fast_dynamic_array, there maybe no constructor and destructor call,
// therefore, it is best suit for POD type, but with care and understanding, you
// can use that for C++ class

template <class t_value, class t_allocator>
class fast_dynamic_array
{
	typedef			t_value					value_t;
	typedef			const t_value			const_value_t;
	typedef			t_value*				pointer_t;
	typedef			const t_value*			const_pointer_t;
	typedef			t_allocator				allocator_t;
	typedef			allocator_t*			allocator_ptr_t;

public:
	fast_dynamic_array()
		: m_size(0)
		, m_capacity(0)
		, m_allocatedCapacity(0)
		, m_data(nullptr)
		, m_allocator(nullptr)
	{ }

	explicit fast_dynamic_array(allocator_ptr_t i_myAllocator)
		: m_size(0)
		, m_capacity(0)
		, m_allocatedCapacity(0)
		, m_data(nullptr)
		, m_allocator(i_myAllocator)
	{

	}

	fast_dynamic_array(const size i_capacity, allocator_ptr_t i_myAllocator)
		: m_size(0)
		, m_capacity(0)
		, m_allocatedCapacity(0)
		, m_data(nullptr)
		, m_allocator(i_myAllocator)
	{
		FLORAL_ASSERT_MSG(i_capacity > 0, "Cannot create an non-positive-capacity array");
		reserve(i_capacity);
	}

	fast_dynamic_array(fast_dynamic_array&& i_other)
		: m_size(i_other.m_size)
		, m_capacity(i_other.m_capacity)
		, m_data(i_other.m_data)
		, m_allocator(i_other.m_allocator)
	{
		i_other.m_capacity = 0;
		i_other.m_size = 0;
		i_other.m_allocator = nullptr;
		i_other.m_data = nullptr;
	}

	~fast_dynamic_array()
	{
		// !!! IMPORTANT: do not free data
	}

	void push_back(const_value_t& v)
	{
		if (m_size + 1 > m_capacity)
		{
			if (m_capacity == 0)
			{
				FLORAL_ASSERT(m_size == 0);
				reserve(1);
			}
			else
			{
				reserve(m_capacity << 1);
			}
		}
		m_data[m_size] = v;
		m_size++;
	}

	t_value pop_back()
	{
		FLORAL_ASSERT_MSG(m_size > 0, "Cannot pop_back an empty array");
		t_value retVal = m_data[m_size - 1];
		m_size--;
		return retVal;
	}

	void empty()
	{
		m_size = 0;
	}

	const size									get_size() const					{ return m_size; }
	const size									get_capacity() const				{ return m_capacity; }
	const size									get_terminated_index() const		{ return m_size; }

	inline value_t& at(const size index) const
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const size find(const value_t& value, bool (*cmpFunc)(const value_t&, const value_t&),
		const size fromId = 0, const size toId = 0) const
	{
		size from = fromId;
		size to = toId > 0 ? toId : m_size;

		for (size i = from; i < to; i++)
		{
			if (cmpFunc(m_data[i], value))
			{
				return i;
			}
		}
		return m_size;
	}

	const size find(const value_t& value, const size fromId = 0, const size toId = 0) const
	{
		size from = fromId;
		size to = toId > 0 ? toId : m_size;

		for (size i = from; i < to; i++)
		{
			if (m_data[i] == value)
			{
				return i;
			}
		}
		return m_size;
	}

	value_t& operator[](const size index)
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const value_t& operator[](const size index) const
	{
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	fast_dynamic_array& operator=(const fast_dynamic_array& i_other)
	{
		if (this != &i_other)
		{
			FLORAL_ASSERT_MSG(m_capacity >= i_other.m_size, "Not enough capacity in destination array");
			empty();
			for (size i = 0; i < i_other.m_size; i++)
			{
				m_data[i] = i_other.m_data[i];
			}
			m_size = i_other.m_size;
		}
		return *this;
	}

	fast_dynamic_array& operator=(fast_dynamic_array&& i_other)
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

	void reserve(const size i_newCapacity, allocator_ptr_t i_myAllocator)
	{
		FLORAL_ASSERT_MSG(m_allocator == nullptr, "An allocator already exists, please use reserve(newSize) instead");
		m_allocator = i_myAllocator;
		reserve(i_newCapacity);
	}

	void reserve(const size i_newCapacity)
	{
		FLORAL_ASSERT_MSG(m_allocator != nullptr, "No allocator, please use reserve(newSize, allocator) instead");
		if (i_newCapacity > m_allocatedCapacity)
		{
			size po2Capacity = next_pow2(i_newCapacity);
			size newMemSize = po2Capacity * sizeof(value_t);
			size oldMemEffectiveSize = m_size * sizeof(value_t);

			pointer_t data = (pointer_t)m_allocator->allocate(newMemSize);
			if (m_data)
			{
				memcpy(data, m_data, oldMemEffectiveSize);
				// cast to voidptr to prevent the allocator calling the destructor ^.^
				m_allocator->free((voidptr)m_data);
			}
			m_capacity = i_newCapacity;
			m_allocatedCapacity = po2Capacity;
			m_data = data;
		}
		else
		{
			m_capacity = i_newCapacity;
		}

		if (m_capacity < m_size)
		{
			m_size = m_capacity;
		}
	}

	void resize(const size i_newSize)
	{
		if (i_newSize > m_capacity)
		{
			reserve(i_newSize);
		}
		m_size = i_newSize;
	}

	// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
	// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void sort()
	{
		partition<t_compare_func>(0, m_size - 1);
	}

private:
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void partition(s32 lo, s32 hi)
	{
		if (lo >= hi)
		{
			return;
		}
		// we choose pivot to be the center element (not the median-value) because of the simplicity
		//s32 pivot = (lo + hi) / 2;
		s32 pivot = lo + (hi - lo) / 2;
		t_value pivotVal = m_data[pivot];
		//s32 i = lo - 1, j = hi + 1;
		s32 i = lo, j = hi;
		while (i <= j)
		{
			while (t_compare_func(m_data[i], pivotVal) > 0)
			{
				i++;
			}

			while (t_compare_func(m_data[j], pivotVal) < 0)
			{
				j--;
			}

			if (i <= j)
			{
				if (i < j)
				{
					t_value tmp = m_data[i];
					m_data[i] = m_data[j];
					m_data[j] = tmp;
				}
				i++;
				j--;
			}
		}
		partition<t_compare_func>(lo, j);
		partition<t_compare_func>(i, hi);
	}

private:
	size										m_size;
	size										m_capacity;
	size										m_allocatedCapacity;

	pointer_t									m_data;
	allocator_ptr_t								m_allocator;
};

// ----------------------------------------------------------------------------
}

#include "fast_array.hpp"
