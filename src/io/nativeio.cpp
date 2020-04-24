#include "floral/io/nativeio.h"

#include <stdio.h>

namespace floral
{

static const_cstr s_working_dir = "";

// ---------------------------------------------

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

void file_stream::read_bytes(voidptr o_buffer, const size i_count)
{
	memcpy((p8)o_buffer, &buffer[rpos], i_count);
	rpos += i_count;
}

void file_stream::unread_byte()
{
	rpos--;
}

void file_stream::unread_bytes(const size i_count)
{
	rpos -= i_count;
}

void file_stream::seek_begin(const size i_offset)
{
	rpos = i_offset;
}

c8 file_stream::read_char()
{
	c8 retVal = buffer[rpos];
	rpos++;
	return retVal;
}

u32 file_stream::read_line_to_buffer(voidptr o_buffer)
{
	u32 len = 0;
	p8 buffer = (p8)o_buffer;
	while (true)
	{
		c8 ch = read_char();
		if (ch == '\n')
		{
			buffer[len] = 0;
			break;
		}
		else
		{
			buffer[len] = ch;
			len++;
		}
	}
	return len;
}

const bool file_stream::is_eos()
{
	return (rpos >= info.file_size);
}

// ---------------------------------------------

output_file_stream::output_file_stream()
{
}

output_file_stream::~output_file_stream()
{
}

void output_file_stream::seek_begin(const size i_offset)
{
	LARGE_INTEGER li;
	li.QuadPart = i_offset;
	
	SetFilePointer(info.file_handle, li.LowPart, &li.HighPart, FILE_BEGIN);
}

const size output_file_stream::get_pointer_position()
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	
	li.LowPart = SetFilePointer(info.file_handle, li.LowPart, &li.HighPart, FILE_CURRENT);
	return size(li.QuadPart);
}

void output_file_stream::write_bytes(voidptr i_buffer, const size i_count)
{
	DWORD byteWritten = 0;
	WriteFile(info.file_handle, i_buffer, (DWORD)i_count, &byteWritten, NULL);
}

// ---------------------------------------------

void set_working_directory(const_cstr i_path)
{
	s_working_dir = i_path;
}

file_info open_file(const_cstr filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s%s", s_working_dir, filePath);
	file_info newFile;
	newFile.file_handle = CreateFileA(fullPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	newFile.file_size = 0;
	if (newFile.file_handle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER fileSize;
		GetFileSizeEx(newFile.file_handle, &fileSize);
		newFile.file_size = (u64)fileSize.QuadPart;
	}
	return newFile;
}

file_info open_file(path i_filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s%s", s_working_dir, i_filePath.pm_PathStr);
	file_info newFile;
	newFile.file_handle = CreateFileA(fullPath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	newFile.file_size = 0;
	if (newFile.file_handle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER fileSize;
		GetFileSizeEx(newFile.file_handle, &fileSize);
		newFile.file_size = (u64)fileSize.QuadPart;
	}
	return newFile;
}

file_info open_output_file(const_cstr i_filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s%s", s_working_dir, i_filePath);
	file_info newFile;
	newFile.file_handle = CreateFileA(fullPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	newFile.file_size = 0;
	return newFile;
}

void read_all_file(const file_info& fileInfo, voidptr buffer)
{
	DWORD bytesRead = 0;
	// 32bit / 64bit: ReadFile only accept DWORD as file size
	ReadFile(fileInfo.file_handle, buffer, static_cast<size32>(fileInfo.file_size), &bytesRead, 0);
}

void read_all_file(const file_info& fileInfo, file_stream& fileStream)
{
	DWORD bytesRead = 0;
	fileStream.info = fileInfo;
	fileStream.rpos = 0;
	// 32bit / 64bit: ReadFile only accept DWORD as file size
	ReadFile(fileInfo.file_handle, fileStream.buffer, static_cast<size32>(fileInfo.file_size), &bytesRead, 0);
}

void mmap_all_file(const file_info& fileInfo, voidptr buffer)
{
}

void map_output_file(const file_info& i_fileInfo, output_file_stream& o_fileStream)
{
	o_fileStream.info = i_fileInfo;
}

void close_file(file_info& fileInfo)
{
	CloseHandle(fileInfo.file_handle);
}

}
