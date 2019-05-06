#pragma once

#include "floral/stdaliases.h"
#include "floral/cmds/path.h"

#if defined(PLATFORM_WINDOWS)
#include <Windows.h>
#endif

/*
 * WARNING: Those functions are not thread-safe
 */

namespace floral
{

#if defined(PLATFORM_WINDOWS)
struct file_info {
	HANDLE									file_handle;
	size									file_size;				// in bytes
};
#else
struct file_info {
	size									file_size;
};
#endif

// -----------------------------------------

class file_stream {
	public:
		file_stream();
		~file_stream();

		u8										read_byte();
		void									read_bytes(voidptr o_buffer, const size i_count);
		void									unread_byte();
		void									unread_bytes(const size i_count);
		void									seek_begin(const size i_offset);
		c8										read_char();
		u32										read_line_to_buffer(voidptr o_buffer);

		template <typename t_type>
		void read(t_type* o_to) {
			memcpy((p8)o_to, &buffer[rpos], sizeof(t_type));
			rpos += sizeof(t_type);
		}

		const bool								is_eos();

	public:
		file_info								info;
		size									rpos;
		p8										buffer;
};

// -----------------------------------------

class output_file_stream {
public:
	output_file_stream();
	~output_file_stream();

	void										write_bytes(voidptr i_buffer, const size i_count);

	template <typename t_type>
	void write(const t_type& i_from)
	{
		DWORD byteWritten = 0;
		WriteFile(
				info.file_handle,
				&i_from,
				sizeof(t_type),
				&byteWritten,
				NULL);
	}

public:
	file_info									info;
};

// -----------------------------------------

file_info										open_file(const_cstr filePath);
file_info										open_file(path i_filePath);
file_info										open_output_file(const_cstr i_filePath);

void											read_all_file(const file_info& fileInfo, voidptr buffer);
void											read_all_file(const file_info& fileInfo, file_stream& fileStream);
void											mmap_all_file(const file_info& fileInfo, voidptr buffer);
void											map_output_file(const file_info& i_fileInfo, output_file_stream& o_fileStream);

void											close_file(file_info& fileInfo);

}
