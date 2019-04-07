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

class file_stream {
	public:
		file_stream();
		~file_stream();

		u8									read_byte();
		void								read_bytes(voidptr o_buffer, const size i_count);
		void								unread_byte();
		void								unread_bytes(const size i_count);
		void								seek_begin(const size i_offset);
		c8									read_char();
		u32									read_line_to_buffer(voidptr o_buffer);

		template <typename t_type>
		void read(t_type* i_to) {
			memcpy((p8)i_to, &buffer[rpos], sizeof(t_type));
			rpos += sizeof(t_type);
		}

		const bool							is_eos();

	public:
		file_info							info;
		size								rpos;
		p8									buffer;
};

// -----------------------------------------

file_info									open_file(const_cstr filePath);
file_info									open_file(path i_filePath);
void										read_all_file(const file_info& fileInfo, voidptr buffer);
void										read_all_file(const file_info& fileInfo, file_stream& fileStream);
void										mmap_all_file(const file_info& fileInfo, voidptr buffer);
void										close_file(file_info& fileInfo);

}