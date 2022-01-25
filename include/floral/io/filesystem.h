#pragma once

#include "floral/stdaliases.h"
#include "floral/containers/fast_array.h"

#include "nativeio.h"

namespace floral
{
// -------------------------------------------------------------------

#define MAX_PATH_LENGTH							1024
#define MAX_ENTRY_NAME_LENGTH					64
#define MAX_DEPTH								32

// copyable
struct generic_path
{
	size										depth;
	c8											entries[MAX_DEPTH][MAX_ENTRY_NAME_LENGTH];
};

// copyable
struct absolute_path : generic_path
{
};

// copyable
struct relative_path : generic_path
{
};

// copyable
template <class t_allocator>
struct filesystem
{
	t_allocator*								allocator;
	floral::fast_dynamic_array<absolute_path, t_allocator>	workingStack;
};

// -------------------------------------------------------------------

namespace platform
{
// -------------------------------------------------------------------

const bool										get_application_directory(cstr o_buffer, const size i_maxLength);

// -------------------------------------------------------------------
}

// -------------------------------------------------------------------

absolute_path									get_application_directory();

// i_pathStr must be null-terminated
absolute_path									build_absolute_path(const_cstr i_pathStr);
// i_pathStr must be null-terminated
relative_path									build_relative_path(const_cstr i_pathStr);
void											concat_path(absolute_path* io_absPath, const relative_path& i_relPath);
void											get_as_cstr(cstr o_buffer, const absolute_path& i_absPath);

template <class t_allocator>
filesystem<t_allocator>*						create_filesystem(const absolute_path& i_workingDir, t_allocator* i_allocator);

template <class t_allocator>
void											destroy_filesystem(filesystem<t_allocator>** i_fs);

template <class t_filesystem>
void											push_directory(t_filesystem* io_fs, const relative_path& i_relPath);

template <class t_filesystem>
void											push_directory(t_filesystem* io_fs, const absolute_path& i_path);

template <class t_filesystem>
void											pop_directory(t_filesystem* io_fs);

template <class t_allocator>
const absolute_path&							get_working_directory(const filesystem<t_allocator>* i_fs);

template <class t_allocator>
file_info										open_file_read(const filesystem<t_allocator>* i_fs, const relative_path& i_relPath);

template <class t_allocator>
file_info										open_file_read(const filesystem<t_allocator>* i_fs, const absolute_path& i_absPath);

template <class t_allocator>
file_info										open_file_write(const filesystem<t_allocator>* i_fs, const relative_path& i_relPath);

template <class t_allocator>
file_info										open_file_write(const filesystem<t_allocator>* i_fs, const absolute_path& i_absPath);

// -------------------------------------------------------------------
}

#include "filesystem.inl"
