#ifndef __FLORAL_NATIVE_IO_H__
#define __FLORAL_NATIVE_IO_H__

#include <stdaliases.h>

#if defined(PLATFORM_WINDOWS)
#include <Windows.h>
#endif

/*
 * WARNING: Those functions are not thread-safe
 */

namespace floral {

#if defined(PLATFORM_WINDOWS)
	struct file_info {
		HANDLE									file_handle;
		u64										file_size;				// in bytes
	};
#else
#endif

	class file_stream {
		public:
			file_stream();
			~file_stream();

			u8									read_byte();
			void								unread_byte();
			c8									read_char();
			const u64							read_to_buffer(voidptr o_buffer, const u64 i_size);

			const bool							is_eos();

		public:
			file_info							info;
			u64									rpos;
			u8*									buffer;
	};

	// -----------------------------------------

	file_info									open_file(const_cstr filePath);
	void										read_all_file(const file_info& fileInfo, voidptr buffer);
	void										read_all_file(const file_info& fileInfo, file_stream& fileStream);
	void										mmap_all_file(const file_info& fileInfo, voidptr buffer);
	void										close_file(file_info& fileInfo);
}

#endif // __FLORAL_NATIVE_IO_H__
