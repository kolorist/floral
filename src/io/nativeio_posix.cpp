#include "floral/io/nativeio.h"

#include <sys/stat.h>

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

c8 file_stream::peek_char()
{
	return buffer[rpos];
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

// -------------------------------------------------------------------

output_file_stream::output_file_stream()
{
}

output_file_stream::~output_file_stream()
{
}

void output_file_stream::seek_begin(const size i_offset)
{
}

const size output_file_stream::get_pointer_position()
{
	return 0;
}

void output_file_stream::write_bytes(voidptr i_buffer, const size i_count)
{
}

// -------------------------------------------------------------------

void set_working_directory(const_cstr i_path)
{
	s_working_dir = i_path;
}

const_cstr get_working_directory()
{
	return s_working_dir;
}

file_info open_file(const_cstr filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s/%s", s_working_dir, filePath);
	file_info newFile;
	newFile.file_handle = fopen(fullPath, "rb");
	newFile.file_size = 0;
	if (newFile.file_handle != nullptr)
	{
		struct stat st;
		stat(fullPath, &st);
		newFile.file_size = st.st_size;
	}
	return newFile;
}

file_info open_file(path i_filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s/%s", s_working_dir, i_filePath.pm_PathStr);
	file_info newFile;
	newFile.file_handle = fopen(fullPath, "rb");
	newFile.file_size = 0;
	if (newFile.file_handle != nullptr)
	{
		struct stat st;
		stat(fullPath, &st);
		newFile.file_size = st.st_size;
	}
	return newFile;
}

file_info open_output_file(const_cstr i_filePath)
{
	c8 fullPath[2048];
	sprintf(fullPath, "%s/%s", s_working_dir, i_filePath);
	file_info newFile;
	newFile.file_handle = fopen(fullPath, "wb");
	newFile.file_size = 0;
	return newFile;
}

void read_all_file(const file_info& fileInfo, voidptr buffer)
{
	fread(buffer, fileInfo.file_size, 1, fileInfo.file_handle);
}

void read_all_file(const file_info& fileInfo, file_stream& fileStream)
{
	fileStream.info = fileInfo;
	fileStream.rpos = 0;
	fread(fileStream.buffer, fileInfo.file_size, 1, fileInfo.file_handle);
}

void mmap_all_file(const file_info& fileInfo, voidptr buffer)
{
}

void map_output_file(const file_info& i_fileInfo, output_file_stream* o_fileStream)
{
	o_fileStream->info = i_fileInfo;
}

void close_file(file_info& fileInfo)
{
	fclose(fileInfo.file_handle);
}

}
