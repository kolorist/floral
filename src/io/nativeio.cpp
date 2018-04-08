#include "io/nativeio.h"

namespace floral {

	file_stream::file_stream()
		: rpos(0)
		, buffer(nullptr)
	{
	}

	file_stream::~file_stream()
	{
	}

	u8 file_stream::read_byte()
	{
		u8 retVal = buffer[rpos];
		rpos++;
		return retVal;
	}

	void file_stream::unread_byte()
	{
		rpos--;
	}

	c8 file_stream::read_char()
	{
		c8 retVal = buffer[rpos];
		rpos++;
		return retVal;
	}

	const u64 file_stream::read_to_buffer(voidptr o_buffer, const u64 i_size)
	{
		const u64 copySize = (i_size > (info.file_size - rpos)) ? (info.file_size - rpos) : i_size;
		memcpy((u8*)o_buffer, &buffer[rpos], copySize);
		rpos += copySize;
		return copySize;
	}

	const bool file_stream::is_eos()
	{
		return (rpos >= info.file_size);
	}

	// -----------------------------------------

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

	void read_all_file(const file_info& fileInfo, voidptr buffer)
	{
		DWORD bytesRead = 0;
		ReadFile(fileInfo.file_handle, buffer, fileInfo.file_size, &bytesRead, 0);
	}

	void read_all_file(const file_info& fileInfo, file_stream& fileStream)
	{
		DWORD bytesRead = 0;
		fileStream.info = fileInfo;
		fileStream.rpos = 0;
		ReadFile(fileInfo.file_handle, fileStream.buffer, fileInfo.file_size, &bytesRead, 0);
	}

	void mmap_all_file(const file_info& fileInfo, voidptr buffer)
	{
	}

	void close_file(file_info& fileInfo)
	{
	}
}
