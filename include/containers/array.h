#ifndef __FLORAL_ARRAY_H__
#define __FLORAL_ARRAY_H__

#include <macros.h>
#include <stdaliases.h>

namespace floral {
	// FIXME: template type naming convention
	template <class _T, class _Allocator>
	class fixed_array {
		typedef			_T						value_type;
		typedef			const _T				const_value_type;
		typedef			_T*						pointer_type;
		typedef			const _T*				const_pointer_type;
		typedef			_T&						reference_type;
		typedef			const _T&				const_reference_type;
		typedef			_Allocator				my_allocator;
		typedef			my_allocator*			ptr_my_allocator;

		typename		value_type				zero_value = _T();

	public:

		fixed_array()
			: m_Capacity(0)
			, m_Size(0)
			, m_MyAllocator(nullptr)
			, m_Data(nullptr)
		{ }

		explicit fixed_array(const u32 capacity, _Allocator* myAllocator)
			: m_Capacity(capacity)
			, m_Size(0)
			, m_MyAllocator(myAllocator)
		{
			ASSERT_MSG((int)capacity > 0, "Cannot create an non-positive-capacity array");
			m_Data = m_MyAllocator->AllocateArray<value_type>(m_Capacity);
			for (u32 i = 0; i < m_Capacity; i++) {
				m_Data[i] = zero_value;
			}
		}

		// C++11 move constructor
		fixed_array(fixed_array&& other) 
			: m_Capacity(other.m_Capacity)
			, m_Size(other.m_Size)
			, m_MyAllocator(other.m_MyAllocator)
			, m_Data(other.m_Data)
		{
			other.m_Capacity = 0;
			other.m_Size = 0;
			other.m_MyAllocator = nullptr;
			other.m_Data = nullptr;
		}

		~fixed_array()
		{
			m_MyAllocator->Free(m_Data);
		}

		void PushBack(const_reference_type v) {
			ASSERT_MSG(m_Size + 1 <= m_Capacity, "Not enough array memory for PushBack");
			m_Data[m_Size] = v;
			m_Size++;
		}
		
		void Empty() {
			m_Size = 0;
		}

		void Clear() {
			for (u32 i = 0; i < m_Size; i++) {
				m_Data[i] = zero_value;
			}
			m_Size = 0;
		}

		const u32								GetSize() const					{ return m_Size; }
		const u32								GetCapacity() const				{ return m_Capacity; }
		const u32								GetTerminatedIndex() const		{ return m_Size; }
		const_value_type At(const u32 index) const {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		const u32 Find(const_reference_type value, 
			bool (*cmpFunc)(const_reference_type, const_reference_type),
			const u32 fromId = 0, const u32 toId = 0) const 
		{
			u32 from = fromId;
			u32 to = toId > 0 ? toId : m_Size;

			for (u32 i = from; i < to; i++) {
				if (cmpFunc(m_Data[i], value))
					return i;
			}
			return m_Size;
		}
		
		const u32 Find(const_reference_type value, const u32 fromId = 0, const u32 toId = 0) const {
			u32 from = fromId;
			u32 to = toId > 0 ? toId : m_Size;

			for (u32 i = from; i < to; i++) {
				if (m_Data[i] == value)
					return i;
			}
			return m_Size;
		}

		// operator overloading
		reference_type operator[](const u32 index) {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		const_reference_type operator[](const u32 index) const {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		// copy assignment
		fixed_array& operator=(const fixed_array& other) {
			if (this != &other) {
				ASSERT_MSG(m_Capacity >= other.m_Size, "Not enough capacity in destination array");
				Empty();
				for (u32 i = 0; i < other.m_Size; i++) {
					m_Data[i] = other.m_Data[i];
				}
				m_Size = other.m_Size;
			}
			return *this;
		}

		// move assignment
		fixed_array& operator=(fixed_array&& other)
		{
			m_Capacity = other.m_Capacity;
			m_Size = other.m_Size;
			m_MyAllocator = other.m_MyAllocator;
			m_Data = other.m_Data;

			other.m_Capacity = 0;
			other.m_Size = 0;
			other.m_MyAllocator = nullptr;
			other.m_Data = nullptr;
			return *this;
		}

		// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
		// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
		template <s32 (*__CompareFunc)(_T&, _T&)>
		void Sort()
		{
			Partition<__CompareFunc>(0, m_Size - 1);
		}

	private:
		template <s32 (*__CompareFunc)(_T&, _T&)>
		void Partition(s32 lo, s32 hi)
		{
			if (lo >= hi) {
				return;
			}
			// we choose pivot to be the center element (not the median-value) because of the simplicity
			//s32 pivot = (lo + hi) / 2;
			s32 pivot = lo + (hi - lo) / 2;
			_T pivotVal = m_Data[pivot];
			//s32 i = lo - 1, j = hi + 1;
			s32 i = lo, j = hi;
			while (i <= j) {
				while (__CompareFunc(m_Data[i], pivotVal) > 0) i++;
				while (__CompareFunc(m_Data[j], pivotVal) < 0) j--;
				if (i <= j) {
					if (i < j) {
						_T tmp = m_Data[i];
						m_Data[i] = m_Data[j];
						m_Data[j] = tmp;
					}
					i++; j--;
				}
			}
			Partition<__CompareFunc>(lo, j);
			Partition<__CompareFunc>(i, hi);
		}

	private:
		u32										m_Size;
		u32										m_Capacity;

		pointer_type							m_Data;
		ptr_my_allocator						m_MyAllocator;
	};

	// FIXME: template type naming convention
	template <class _T, class _Allocator>
	class dynamic_array {
		typedef			_T						value_type;
		typedef			const _T				const_value_type;
		typedef			_T*						pointer_type;
		typedef			const _T*				const_pointer_type;
		typedef			_T&						reference_type;
		typedef			const _T&				const_reference_type;
		typedef			_Allocator				my_allocator;
		typedef			my_allocator*			ptr_my_allocator;

		typename		value_type				zero_value = _T();

	public:

		dynamic_array()
			: m_Capacity(0)
			, m_Size(0)
			, m_MyAllocator(nullptr)
			, m_Data(nullptr)
		{ }

		explicit dynamic_array(const u32 capacity, _Allocator* myAllocator)
			: m_Capacity(capacity)
			, m_Size(0)
			, m_MyAllocator(myAllocator)
		{
			ASSERT_MSG((int)capacity > 0, "Cannot create an non-positive-capacity array");
			m_Data = m_MyAllocator->AllocateArray<value_type>(m_Capacity);
			for (u32 i = 0; i < m_Capacity; i++) {
				m_Data[i] = zero_value;
			}
		}

		// C++11 move constructor
		dynamic_array(dynamic_array&& other) 
			: m_Capacity(other.m_Capacity)
			, m_Size(other.m_Size)
			, m_MyAllocator(other.m_MyAllocator)
			, m_Data(other.m_Data)
		{
			other.m_Capacity = 0;
			other.m_Size = 0;
			other.m_MyAllocator = nullptr;
			other.m_Data = nullptr;
		}

		~dynamic_array()
		{
			m_MyAllocator->Free(m_Data);
		}

		void PushBack(const_reference_type v) {
			if (m_Size + 1 > m_Capacity) {
				Resize(m_Capacity << 1);			// strategy: double capacity growth
			}
			m_Data[m_Size] = v;
			m_Size++;
		}
		
		void Empty() {
			m_Size = 0;
		}

		void Clear() {
			for (u32 i = 0; i < m_Size; i++) {
				m_Data[i] = zero_value;
			}
			m_Size = 0;
		}

		const u32								GetSize() const					{ return m_Size; }
		const u32								GetCapacity() const				{ return m_Capacity; }
		const u32								GetTerminatedIndex() const		{ return m_Size; }
		const_value_type At(const u32 index) const {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		const u32 Find(const_reference_type value, 
			bool (*cmpFunc)(const_reference_type, const_reference_type),
			const u32 fromId = 0, const u32 toId = 0) const 
		{
			u32 from = fromId;
			u32 to = toId > 0 ? toId : m_Size;

			for (u32 i = from; i < to; i++) {
				if (cmpFunc(m_Data[i], value))
					return i;
			}
			return m_Size;
		}
		
		const u32 Find(const_reference_type value, const u32 fromId = 0, const u32 toId = 0) const {
			u32 from = fromId;
			u32 to = toId > 0 ? toId : m_Size;

			for (u32 i = from; i < to; i++) {
				if (m_Data[i] == value)
					return i;
			}
			return m_Size;
		}

		// operator overloading
		reference_type operator[](const u32 index) {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		const_reference_type operator[](const u32 index) const {
			ASSERT_MSG((int)index >= 0 && index < m_Size, "Array access violation (out of range)");
			return m_Data[index];
		}

		// copy assignment
		dynamic_array& operator=(const dynamic_array& other) {
			if (this != &other) {
				ASSERT_MSG(m_Capacity >= other.m_Size, "Not enough capacity in destination array");
				Empty();
				for (u32 i = 0; i < other.m_Size; i++) {
					m_Data[i] = other.m_Data[i];
				}
				m_Size = other.m_Size;
			}
			return *this;
		}

		// move assignment
		dynamic_array& operator=(dynamic_array&& other)
		{
			m_Capacity = other.m_Capacity;
			m_Size = other.m_Size;
			m_MyAllocator = other.m_MyAllocator;
			m_Data = other.m_Data;

			other.m_Capacity = 0;
			other.m_Size = 0;
			other.m_MyAllocator = nullptr;
			other.m_Data = nullptr;
			return *this;
		}

		// TODO: cannot sure if this works correctly, need to compare with std::vector or something similar
		// review ref: https://codereview.stackexchange.com/questions/77782/quick-sort-implementation
		template <s32 (*__CompareFunc)(_T&, _T&)>
		void Sort()
		{
			Partition<__CompareFunc>(0, m_Size - 1);
		}

	private:
		template <s32 (*__CompareFunc)(_T&, _T&)>
		void Partition(s32 lo, s32 hi)
		{
			if (lo >= hi) {
				return;
			}
			// we choose pivot to be the center element (not the median-value) because of the simplicity
			//s32 pivot = (lo + hi) / 2;
			s32 pivot = lo + (hi - lo) / 2;
			_T pivotVal = m_Data[pivot];
			//s32 i = lo - 1, j = hi + 1;
			s32 i = lo, j = hi;
			while (i <= j) {
				while (__CompareFunc(m_Data[i], pivotVal) > 0) i++;
				while (__CompareFunc(m_Data[j], pivotVal) < 0) j--;
				if (i <= j) {
					if (i < j) {
						_T tmp = m_Data[i];
						m_Data[i] = m_Data[j];
						m_Data[j] = tmp;
					}
					i++; j--;
				}
			}
			Partition<__CompareFunc>(lo, j);
			Partition<__CompareFunc>(i, hi);
		}


	private:
		void Resize(const u32 newCapacity) {
			pointer_type data = m_MyAllocator->AllocateArray<value_type>(newCapacity);
			for (u32 i = 0; i < newCapacity; i++) {
				data[i] = zero_value;
			}
			// copy data
			for (u32 i = 0; i < m_Size; i++) {
				data[i] = m_Data[i];
			}
			m_Capacity = newCapacity;
			m_MyAllocator->Free(m_Data);
			m_Data = data;
		}

	private:
		u32										m_Size;
		u32										m_Capacity;

		pointer_type							m_Data;
		ptr_my_allocator						m_MyAllocator;
	};
}

#endif // __FLORAL_ARRAY_H__
