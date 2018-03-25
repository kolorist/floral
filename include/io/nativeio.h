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

	file_info									open_file(const_cstr filePath);
	void										read_all_file(file_info& fileInfo, voidptr buffer);
	void										mmap_all_file(file_info& fileInfo, voidptr buffer);
	void										close_file(file_info& fileInfo);
}

#endif // __FLORAL_NATIVE_IO_H__
