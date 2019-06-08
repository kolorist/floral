#pragma once

#include "floral/stdaliases.h"
#include "floral/assert/assert.h"

// NOTE: 	as a trade-off for high performance, those array implementations are considered un-safe
//			for both single-threaded (range check, type check) and multi-threaded (synchronization) purposes

namespace floral {

template <class t_value, u32 t_capacity>
class inplace_array {
	typedef			t_value					value_t;
	typedef			const t_value			const_value_t;
	typedef			t_value*				pointer_t;
	typedef			const t_value*			const_pointer_t;
	typedef			t_value&				reference_t;

public:
	inplace_array()
		: m_size(0)
		, m_capacity(t_capacity)
	{ }

	void init()
	{
		m_size = 0;
		
		FLORAL_ASSERT_MSG((int)m_capacity > 0, "Cannot create an non-positive-capacity array");
		for (u32 i = 0; i < m_capacity; i++) {
			m_data[i] = value_t();
		}
	}

	~inplace_array()
	{
	}

	void push_back(const t_value& i_value) {
		FLORAL_ASSERT_MSG(m_size + 1 <= m_capacity, "Not enough array memory for push_back");
		m_data[m_size] = i_value;
		m_size++;
	}
	
	void empty() {
		m_size = 0;
	}

	void clear() {
		for (u32 i = 0; i < m_size; i++) {
			m_data[i] = value_t();
		}
		m_size = 0;
	}

	const u32								get_size() const					{ return m_size; }
	const u32								get_capacity() const				{ return m_capacity; }
	const u32								get_terminated_index() const		{ return m_size; }
	const_value_t at(const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const u32 find(const t_value& value, 
		bool (*cmpFunc)(const t_value&, const t_value&),
		const u32 fromId = 0, const u32 toId = 0) const 
	{
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (cmpFunc(m_data[i], value))
				return i;
		}
		return m_size;
	}
	
	const u32 find(const t_value& value, const u32 fromId = 0, const u32 toId = 0) const {
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (m_data[i] == value)
				return i;
		}
		return m_size;
	}

	// operator overloading
	reference_t operator[](const u32 index) {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const t_value& operator[](const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	// copy assignment
	inplace_array& operator=(const inplace_array& i_other) {
		if (this != &i_other) {
			FLORAL_ASSERT_MSG(m_capacity >= i_other.m_size, "Not enough capacity in destination array");
			empty();
			for (u32 i = 0; i < i_other.m_size; i++) {
				m_data[i] = i_other.m_data[i];
			}
			m_size = i_other.m_size;
		}
		return *this;
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
		if (lo >= hi) {
			return;
		}
		// we choose pivot to be the center element (not the median-value) because of the simplicity
		//s32 pivot = (lo + hi) / 2;
		s32 pivot = lo + (hi - lo) / 2;
		t_value pivotVal = m_data[pivot];
		//s32 i = lo - 1, j = hi + 1;
		s32 i = lo, j = hi;
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
	u32										m_size;
	u32										m_capacity;

	value_t									m_data[t_capacity];
};

template <class t_value, class t_allocator>
class fixed_array {
	typedef			t_value					value_t;
	typedef			const t_value			const_value_t;
	typedef			t_value*				pointer_t;
	typedef			const t_value*			const_pointer_t;
	typedef			t_value&				reference_t;
	typedef			const t_value&			const_reference_t;
	typedef			t_allocator				allocator_t;
	typedef			allocator_t*			allocator_ptr_t;

public:
	fixed_array()
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr)
		, m_allocator(nullptr)
	{ }

	explicit fixed_array(const u32 i_capacity, allocator_ptr_t i_myAllocator)
	{
		init(i_capacity, i_myAllocator);
	}
	
	void init(const u32 i_capacity, allocator_ptr_t i_allocator)
	{
		m_capacity = i_capacity;
		m_allocator = i_allocator;
		m_size = 0;
		
		FLORAL_ASSERT_MSG((int)i_capacity > 0, "Cannot create an non-positive-capacity array");
		m_data = m_allocator->template allocate_array<value_t>(m_capacity);
		for (u32 i = 0; i < m_capacity; i++) {
			m_data[i] = value_t();
		}
	}

	// C++11 move constructor
	fixed_array(fixed_array&& i_other) 
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

	~fixed_array()
	{
		if (m_data)
			m_allocator->free(m_data);
	}

	void push_back(const_reference_t i_value) {
		FLORAL_ASSERT_MSG(m_size + 1 <= m_capacity, "Not enough array memory for push_back");
		m_data[m_size] = i_value;
		m_size++;
	}
	
	void empty() {
		m_size = 0;
	}

	void clear() {
		for (u32 i = 0; i < m_size; i++) {
			m_data[i] = value_t();
		}
		m_size = 0;
	}

	const u32								get_size() const					{ return m_size; }
	const u32								get_capacity() const				{ return m_capacity; }
	const u32								get_terminated_index() const		{ return m_size; }
	const_value_t at(const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const u32 find(const_reference_t value, 
		bool (*cmpFunc)(const_reference_t, const_reference_t),
		const u32 fromId = 0, const u32 toId = 0) const 
	{
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (cmpFunc(m_data[i], value))
				return i;
		}
		return m_size;
	}
	
	const u32 find(const_reference_t value, const u32 fromId = 0, const u32 toId = 0) const {
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (m_data[i] == value)
				return i;
		}
		return m_size;
	}

	// operator overloading
	reference_t operator[](const u32 index) {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const_reference_t operator[](const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	// copy assignment
	fixed_array& operator=(const fixed_array& i_other) {
		if (this != &i_other) {
			FLORAL_ASSERT_MSG(m_capacity >= i_other.m_size, "Not enough capacity in destination array");
			empty();
			for (u32 i = 0; i < i_other.m_size; i++) {
				m_data[i] = i_other.m_data[i];
			}
			m_size = i_other.m_size;
		}
		return *this;
	}

	// move assignment
	fixed_array& operator=(fixed_array&& i_other)
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
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void sort()
	{
		partition<t_compare_func>(0, m_size - 1);
	}

	void resize_ex(const u32 newSize) {
		FLORAL_ASSERT_MSG(newSize <= m_capacity, "Invalid new size!");
		m_size = newSize;
	}

private:
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void partition(s32 lo, s32 hi)
	{
		if (lo >= hi) {
			return;
		}
		// we choose pivot to be the center element (not the median-value) because of the simplicity
		//s32 pivot = (lo + hi) / 2;
		s32 pivot = lo + (hi - lo) / 2;
		t_value pivotVal = m_data[pivot];
		//s32 i = lo - 1, j = hi + 1;
		s32 i = lo, j = hi;
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
	u32										m_size;
	u32										m_capacity;

	pointer_t								m_data;
	allocator_ptr_t							m_allocator;
};

// FIXME: template type naming convention
template <class t_value, class t_allocator>
class dynamic_array {
	typedef			t_value					value_t;
	typedef			const t_value			const_value_t;
	typedef			t_value*				pointer_t;
	typedef			const t_value*			const_pointer_t;
	typedef			t_value&				reference_t;
	typedef			const t_value&			const_reference_t;
	typedef			t_allocator				allocator_t;
	typedef			allocator_t*			allocator_ptr_t;

public:

	dynamic_array()
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr)
		, m_allocator(nullptr)
	{ }
	
	explicit dynamic_array(t_allocator* myAllocator)
		: m_size(0)
		, m_capacity(0)
		, m_data(nullptr)
		, m_allocator(myAllocator)
	{
		
	}

	dynamic_array(const u32 capacity, t_allocator* myAllocator)
		: m_size(0)
		, m_capacity(capacity)
		, m_allocator(myAllocator)
	{
		FLORAL_ASSERT_MSG((int)capacity > 0, "Cannot create an non-positive-capacity array");
		m_data = m_allocator->template allocate_array<value_t>(m_capacity);
		for (u32 i = 0; i < m_capacity; i++) {
			m_data[i] = value_t();
		}
	}

	// C++11 move constructor
	dynamic_array(dynamic_array&& i_other) 
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

	~dynamic_array()
	{
		m_allocator->free(m_data);
	}

	void push_back(const_reference_t v) {
		if (m_size + 1 > m_capacity) {
			resize(m_capacity << 1);			// strategy: double capacity growth
		}
		m_data[m_size] = v;
		m_size++;
	}
	
	void empty() {
		m_size = 0;
	}

	void clear() {
		for (u32 i = 0; i < m_size; i++) {
			m_data[i] = value_t();
		}
		m_size = 0;
	}

	const u32								get_size() const					{ return m_size; }
	const u32								get_capacity() const				{ return m_capacity; }
	const u32								get_terminated_index() const		{ return m_size; }
	const_value_t at(const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const u32 find(const_reference_t value, 
		bool (*cmpFunc)(const_reference_t, const_reference_t),
		const u32 fromId = 0, const u32 toId = 0) const 
	{
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (cmpFunc(m_data[i], value))
				return i;
		}
		return m_size;
	}
	
	const u32 find(const_reference_t value, const u32 fromId = 0, const u32 toId = 0) const {
		u32 from = fromId;
		u32 to = toId > 0 ? toId : m_size;

		for (u32 i = from; i < to; i++) {
			if (m_data[i] == value)
				return i;
		}
		return m_size;
	}

	// operator overloading
	reference_t operator[](const u32 index) {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	const_reference_t operator[](const u32 index) const {
		FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
		return m_data[index];
	}

	// copy assignment
	dynamic_array& operator=(const dynamic_array& i_other) {
		if (this != &i_other) {
			FLORAL_ASSERT_MSG(m_capacity >= i_other.m_size, "Not enough capacity in destination array");
			empty();
			for (u32 i = 0; i < i_other.m_size; i++) {
				m_data[i] = i_other.m_data[i];
			}
			m_size = i_other.m_size;
		}
		return *this;
	}

	// move assignment
	dynamic_array& operator=(dynamic_array&& i_other)
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
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void sort()
	{
		partition<t_compare_func>(0, m_size - 1);
	}

private:
	template <s32 (*t_compare_func)(t_value&, t_value&)>
	void partition(s32 lo, s32 hi)
	{
		if (lo >= hi) {
			return;
		}
		// we choose pivot to be the center element (not the median-value) because of the simplicity
		//s32 pivot = (lo + hi) / 2;
		s32 pivot = lo + (hi - lo) / 2;
		t_value pivotVal = m_data[pivot];
		//s32 i = lo - 1, j = hi + 1;
		s32 i = lo, j = hi;
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


public:

	void resize_ex(const u32 newSize) {
		if (newSize > m_capacity) {
			// run-time reallocate => round (up) to the nearest power of 2
			// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
			u32 po2Size = newSize;
			po2Size--;
			po2Size |= po2Size >> 1;
			po2Size |= po2Size >> 2;
			po2Size |= po2Size >> 4;
			po2Size |= po2Size >> 8;
			po2Size |= po2Size >> 16;
			po2Size++;

			pointer_t data = m_allocator->template allocate_array<value_t>(po2Size);
			for (u32 i = 0; i < po2Size; i++) {
				data[i] = value_t();
			}
			// copy data
			for (u32 i = 0; i < m_size; i++) {
				data[i] = m_data[i];
			}
			// free old data
			if (m_data)
				m_allocator->free(m_data);
			m_capacity = po2Size;
			m_data = data;
		}

		m_size = newSize;
	}

	void resize(const u32 newCapacity) {
		if (newCapacity <= m_capacity)
			return;
	
		pointer_t data = m_allocator->template allocate_array<value_t>(newCapacity);
		for (u32 i = 0; i < newCapacity; i++) {
			data[i] = value_t();
		}
		// copy data
		for (u32 i = 0; i < m_size; i++) {
			data[i] = m_data[i];
		}
		// free old data
		if (m_data)
			m_allocator->free(m_data);
		
		m_capacity = newCapacity;
		m_data = data;
	}

private:
	u32										m_size;
	u32										m_capacity;

	pointer_t								m_data;
	allocator_ptr_t							m_allocator;
};
}