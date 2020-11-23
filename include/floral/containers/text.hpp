namespace floral
{
// ----------------------------------------------------------------------------

template <class t_allocator>
fast_dynamic_text_buffer<t_allocator>::fast_dynamic_text_buffer()
{
	// nothing :)
}

template <class t_allocator>
fast_dynamic_text_buffer<t_allocator>::fast_dynamic_text_buffer(t_allocator* allocator)
	: buffer(allocator)
{
}

template <class t_allocator>
inline c8 fast_dynamic_text_buffer<t_allocator>::operator[] (ssize i)
{
	FLORAL_ASSERT(buffer.get_size() > 0);
	return buffer[i];
}

template <class t_allocator>
const c8* fast_dynamic_text_buffer<t_allocator>::begin() const
{
	if (buffer.get_size() > 0)
	{
		return &buffer[0];
	}
	else
	{
		return empty_string;
	}
}

template <class t_allocator>
const c8* fast_dynamic_text_buffer<t_allocator>::end() const
{
	if (buffer.get_size() > 0)
	{
		return &buffer[buffer.get_size() - 1];
	}
	else
	{
		return empty_string; // Buf is zero-terminated, so end() will point on the zero-terminator
	}
}

template <class t_allocator>
ssize fast_dynamic_text_buffer<t_allocator>::get_size() const
{
	ssize buffSize = buffer.get_size();
	return buffSize > 0 ? buffSize - 1: 0;
}

template <class t_allocator>
bool fast_dynamic_text_buffer<t_allocator>::is_empty()
{
	return buffer.get_size() <= 1;
}

template <class t_allocator>
void fast_dynamic_text_buffer<t_allocator>::clear()
{
	buffer.clear();
}

template <class t_allocator>
void fast_dynamic_text_buffer<t_allocator>::reserve(const ssize capacity)
{
	buffer.reserve(capacity);
}

template <class t_allocator>
void fast_dynamic_text_buffer<t_allocator>::reserve(const ssize capacity, t_allocator* allocator)
{
	buffer.reserve(capacity, allocator);
}

template <class t_allocator>
const_cstr fast_dynamic_text_buffer<t_allocator>::c_str() const
{
	return begin();
}

template <class t_allocator>
void fast_dynamic_text_buffer<t_allocator>::append(const_cstr str, const_cstr strEnd /* = nullptr */)
{
	ssize len = strEnd ? (ssize)(strEnd - str) : (ssize)strlen(str);

	// Add zero-terminator the first time
	const ssize writeOff = (buffer.get_size() != 0) ? buffer.get_size() : 1;
	const ssize neededSz = writeOff + len;
	if (neededSz >= buffer.get_capacity())
	{
		int newCapacity = buffer.get_capacity() * 2;
		buffer.reserve(neededSz > newCapacity ? neededSz : newCapacity); // sometimes, double growing is not enough
	}

	buffer.resize(neededSz);
	memcpy(&buffer[writeOff - 1], str, len);
	buffer[writeOff - 1 + len] = 0;
}

// ----------------------------------------------------------------------------
}
