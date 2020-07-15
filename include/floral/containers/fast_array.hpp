namespace floral
{
// ----------------------------------------------------------------------------
// fast_fixed_array

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>::fast_fixed_array()
	: m_size(0)
	, m_capacity(0)
	, m_data(nullptr)
	, m_allocator(nullptr)
{
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>::fast_fixed_array(t_allocator* allocator)
	: m_size(0)
	, m_capacity(0)
	, m_data(nullptr)
	, m_allocator(allocator)
{
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>::fast_fixed_array(const ssize capacity, t_allocator* allocator)
	: m_allocator(allocator)
{
	reserve(capacity);
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>::fast_fixed_array(fast_fixed_array&& other)
	: m_capacity(other.m_capacity)
	, m_size(other.m_size)
	, m_allocator(other.m_allocator)
	, m_data(other.m_data)
{
	other.m_capacity = 0;
	other.m_size = 0;
	other.m_allocator = nullptr;
	other.m_data = nullptr;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>::~fast_fixed_array()
{
	// !!! IMPORTANT: do not free data
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
void fast_fixed_array<t_value, t_allocator>::reserve(const ssize capacity, t_allocator* newAllocator)
{
	m_allocator = newAllocator;
	reserve(capacity);
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
void fast_fixed_array<t_value, t_allocator>::reserve(const ssize capacity)
{
	FLORAL_ASSERT_MSG(m_allocator != nullptr, "Cannot reserve memory for array without an allocator");
	FLORAL_ASSERT_MSG((int)capacity > 0, "Cannot create an non-positive-capacity array");
	m_capacity = capacity;
	m_size = 0;
	m_data = m_allocator->template allocate_podarray<t_value>(m_capacity);
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline void fast_fixed_array<t_value, t_allocator>::push_back(const t_value& value)
{
	FLORAL_ASSERT_MSG(m_size + 1 <= m_capacity, "Not enough array memory for push_back");
	m_data[m_size] = value;
	m_size++;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline t_value fast_fixed_array<t_value, t_allocator>::pop_back()
{
	FLORAL_ASSERT_MSG(m_size > 0, "Cannot pop_back an empty array");
	t_value retVal = m_data[m_size - 1];
	m_size--;
	return retVal;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline void fast_fixed_array<t_value, t_allocator>::clear()
{
	m_size = 0;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
void fast_fixed_array<t_value, t_allocator>::invalidate()
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

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const ssize fast_fixed_array<t_value, t_allocator>::get_size() const
{
	return m_size;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const ssize fast_fixed_array<t_value, t_allocator>::get_capacity() const
{
	return m_capacity;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const ssize fast_fixed_array<t_value, t_allocator>::get_terminated_index() const
{
	return m_size;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
const ssize fast_fixed_array<t_value, t_allocator>::find(const t_value& value,
		const ssize fromId /* = 0 */, const ssize toId /* = 0 */) const
{
	ssize from = fromId;
	ssize to = toId > 0 ? toId : m_size;

	for (ssize i = from; i < to; i++)
	{
		if (m_data[i] == value)
		{
			return i;
		}
	}
	return m_size;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
const ssize fast_fixed_array<t_value, t_allocator>::find(const t_value& value, const bool (*cmpFunc)(const t_value&, const t_value&),
		const ssize fromId /* = 0 */, const ssize toId /* = 0 */) const
{
	ssize from = fromId;
	ssize to = toId > 0 ? toId : m_size;

	for (ssize i = from; i < to; i++)
	{
		if (cmpFunc(m_data[i], value))
		{
			return i;
		}
	}
	return m_size;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline t_value& fast_fixed_array<t_value, t_allocator>::at(const ssize index) const
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline t_value& fast_fixed_array<t_value, t_allocator>::operator[](const ssize index)
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const t_value& fast_fixed_array<t_value, t_allocator>::operator[](const ssize index) const
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>& fast_fixed_array<t_value, t_allocator>::operator=(const fast_fixed_array& other)
{
	if (this != &other)
	{
		FLORAL_ASSERT_MSG(m_capacity >= other.m_size, "Not enough capacity in destination array");
		clear();
		for (ssize i = 0; i < other.m_size; i++)
		{
			m_data[i] = other.m_data[i];
		}
		m_size = other.m_size;
	}
	return *this;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_fixed_array<t_value, t_allocator>& fast_fixed_array<t_value, t_allocator>::operator=(fast_fixed_array&& other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_allocator = other.m_allocator;
	m_data = other.m_data;

	other.m_capacity = 0;
	other.m_size = 0;
	other.m_allocator = nullptr;
	other.m_data = nullptr;
	return *this;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
template <ssize (*t_compare_func)(t_value&, t_value&)>
inline void fast_fixed_array<t_value, t_allocator>::sort()
{
	partition<t_compare_func>(0, m_size - 1);
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline void fast_fixed_array<t_value, t_allocator>::resize(const ssize newSize)
{
	FLORAL_ASSERT_MSG(newSize <= m_capacity, "Invalid new ssize!");
	m_size = newSize;
}

template <class t_value, class t_allocator>
template <ssize (*t_compare_func)(t_value&, t_value&)>
void fast_fixed_array<t_value, t_allocator>::partition(ssize lo, ssize hi)
{
	if (lo >= hi)
	{
		return;
	}
	// we choose pivot to be the center element (not the median-value) because of the simplicity
	ssize pivot = lo + (hi - lo) / 2; // to prevent overflow
	t_value pivotVal = m_data[pivot];
	ssize i = lo, j = hi;
	while (i <= j)
	{
		while (t_compare_func(m_data[i], pivotVal) > 0) i++;
		while (t_compare_func(m_data[j], pivotVal) < 0) j--;
		if (i <= j)
		{
			if (i < j)
			{
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

// ----------------------------------------------------------------------------
// fast_dynamic_array

template <class t_value, class t_allocator>
inline fast_dynamic_array<t_value, t_allocator>::fast_dynamic_array()
	: m_size(0)
	, m_capacity(0)
	, m_allocatedCapacity(0)
	, m_data(nullptr)
	, m_allocator(nullptr)
{
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline fast_dynamic_array<t_value, t_allocator>::fast_dynamic_array(t_allocator* allocator)
	: m_size(0)
	, m_capacity(0)
	, m_allocatedCapacity(0)
	, m_data(nullptr)
	, m_allocator(allocator)
{
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
fast_dynamic_array<t_value, t_allocator>::fast_dynamic_array(const ssize capacity, t_allocator* allocator)
	: m_size(0)
	, m_capacity(0)
	, m_allocatedCapacity(0)
	, m_data(nullptr)
	, m_allocator(allocator)
{
	FLORAL_ASSERT_MSG(capacity > 0, "Cannot create an non-positive-capacity array");
	reserve(capacity);
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline fast_dynamic_array<t_value, t_allocator>::fast_dynamic_array(fast_dynamic_array&& other)
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
	, m_data(other.m_data)
	, m_allocator(other.m_allocator)
{
	other.m_capacity = 0;
	other.m_size = 0;
	other.m_allocator = nullptr;
	other.m_data = nullptr;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline fast_dynamic_array<t_value, t_allocator>::~fast_dynamic_array()
{
	// !!! IMPORTANT: do not free data
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
void fast_dynamic_array<t_value, t_allocator>::push_back(const t_value& v)
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

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline t_value fast_dynamic_array<t_value, t_allocator>::pop_back()
{
	FLORAL_ASSERT_MSG(m_size > 0, "Cannot pop_back an empty array");
	t_value retVal = m_data[m_size - 1];
	m_size--;
	return retVal;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline void fast_dynamic_array<t_value, t_allocator>::clear()
{
	m_size = 0;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const ssize fast_dynamic_array<t_value, t_allocator>::get_size() const
{
	return m_size;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
inline const ssize fast_dynamic_array<t_value, t_allocator>::get_capacity() const
{
	return m_capacity;
}

// ----------------------------------------------------------------------------

template <class t_value, class t_allocator>
const ssize fast_dynamic_array<t_value, t_allocator>::get_terminated_index() const
{
	return m_size;
}

template <class t_value, class t_allocator>
inline t_value& fast_dynamic_array<t_value, t_allocator>::at(const ssize index) const
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

template <class t_value, class t_allocator>
const ssize fast_dynamic_array<t_value, t_allocator>::find(const t_value& value, const bool (*cmpFunc)(const t_value&, const t_value&),
	const ssize fromId /* = 0 */, const ssize toId /* = 0 */) const
{
	ssize from = fromId;
	ssize to = toId > 0 ? toId : m_size;

	for (ssize i = from; i < to; i++)
	{
		if (cmpFunc(m_data[i], value))
		{
			return i;
		}
	}
	return m_size;
}

template <class t_value, class t_allocator>
const ssize fast_dynamic_array<t_value, t_allocator>::find(const t_value& value,
		const ssize fromId /* = 0 */, const ssize toId /* = 0 */) const
{
	ssize from = fromId;
	ssize to = toId > 0 ? toId : m_size;

	for (ssize i = from; i < to; i++)
	{
		if (m_data[i] == value)
		{
			return i;
		}
	}
	return m_size;
}

template <class t_value, class t_allocator>
inline t_value& fast_dynamic_array<t_value, t_allocator>::operator[](const ssize index)
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

template <class t_value, class t_allocator>
inline const t_value& fast_dynamic_array<t_value, t_allocator>::operator[](const ssize index) const
{
	FLORAL_ASSERT_MSG((int)index >= 0 && index < m_size, "Array access violation (out of range)");
	return m_data[index];
}

template <class t_value, class t_allocator>
fast_dynamic_array<t_value, t_allocator>& fast_dynamic_array<t_value, t_allocator>::operator=(const fast_dynamic_array& other)
{
	if (this != &other)
	{
		FLORAL_ASSERT_MSG(m_capacity >= other.m_size, "Not enough capacity in destination array");
		clear();
		for (ssize i = 0; i < other.m_size; i++)
		{
			m_data[i] = other.m_data[i];
		}
		m_size = other.m_size;
	}
	return *this;
}

template <class t_value, class t_allocator>
fast_dynamic_array<t_value, t_allocator>& fast_dynamic_array<t_value, t_allocator>::operator=(fast_dynamic_array&& other)
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_allocator = other.m_allocator;
	m_data = other.m_data;

	other.m_capacity = 0;
	other.m_size = 0;
	other.m_allocator = nullptr;
	other.m_data = nullptr;
	return *this;
}

template <class t_value, class t_allocator>
void fast_dynamic_array<t_value, t_allocator>::reserve(const ssize newCapacity, t_allocator* allocator)
{
	FLORAL_ASSERT_MSG(m_allocator == nullptr, "An allocator already exists, please use reserve(newSize) instead");
	m_allocator = allocator;
	reserve(newCapacity);
}

template <class t_value, class t_allocator>
void fast_dynamic_array<t_value, t_allocator>::reserve(const ssize newCapacity)
{
	FLORAL_ASSERT_MSG(m_allocator != nullptr, "No allocator, please use reserve(newSize, allocator) instead");
	if (newCapacity > m_allocatedCapacity)
	{
		ssize po2Capacity = next_pow2(newCapacity);
		ssize newMemSize = po2Capacity * sizeof(t_value);
		ssize oldMemEffectiveSize = m_size * sizeof(t_value);

		t_value* data = (t_value*)m_allocator->allocate(newMemSize);
		if (m_data)
		{
			memcpy(data, m_data, oldMemEffectiveSize);
			// cast to voidptr to prevent the allocator calling the destructor ^.^
			m_allocator->free((voidptr)m_data);
		}
		m_capacity = newCapacity;
		m_allocatedCapacity = po2Capacity;
		m_data = data;
	}
	else
	{
		m_capacity = newCapacity;
	}

	if (m_capacity < m_size)
	{
		m_size = m_capacity;
	}
}

template <class t_value, class t_allocator>
void fast_dynamic_array<t_value, t_allocator>::resize(const ssize newSize)
{
	if (newSize > m_capacity)
	{
		reserve(newSize);
	}
	m_size = newSize;
}

template <class t_value, class t_allocator>
template <s32 (*t_compare_func)(t_value&, t_value&)>
void fast_dynamic_array<t_value, t_allocator>::sort()
{
	partition<t_compare_func>(0, m_size - 1);
}

template <class t_value, class t_allocator>
template <s32 (*t_compare_func)(t_value&, t_value&)>
void fast_dynamic_array<t_value, t_allocator>::partition(s32 lo, s32 hi)
{
	if (lo >= hi)
	{
		return;
	}
	// we choose pivot to be the center element (not the median-value) because of the simplicity
	s32 pivot = lo + (hi - lo) / 2; // to prevent overflow
	t_value pivotVal = m_data[pivot];
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

// ----------------------------------------------------------------------------
}
