#include "io/nativeio.h"

namespace floral {

	file_info open_file(const_cstr filePath)
	{
		file_info newFile;
		newFile.file_handle = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		newFile.file_size = 0;
		if (newFile.file_handle != INVALID_HANDLE_VALUE) {
			LARGE_INTEGER fileSize;
			GetFileSizeEx(newFile.file_handle, &fileSize);
			newFile.file_size = (u64)fileSize.QuadPart;
		}
		return newFile;
	}

	void read_all_file(file_info& fileInfo, voidptr buffer)
	{
		DWORD bytesRead = 0;
		ReadFile(fileInfo.file_handle, buffer, fileInfo.file_size, &bytesRead, 0);
	}

	void mmap_all_file(file_info& fileInfo, voidptr buffer)
	{
	}

	void close_file(file_info& fileInfo)
	{
	}
}
