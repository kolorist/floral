#include "floral/io/filesystem.h"

#include "floral/assert/assert.h"

namespace floral
{
// -------------------------------------------------------------------

absolute_path get_application_directory()
{
	c8 pathStr[MAX_PATH_LENGTH];
	pathStr[0] = '/';
	const bool result = platform::get_application_directory(&pathStr[1], MAX_PATH_LENGTH - 1);
	FLORAL_ASSERT(result);

	return build_absolute_path(pathStr);
}

// -------------------------------------------------------------------

absolute_path build_absolute_path(const_cstr i_pathStr)
{
	absolute_path path;
	path.depth = 0;
	FLORAL_ASSERT_MSG(i_pathStr[0] == '/', "this is an absolute_path, dude, it must start with '/'!");

	size i = 0;
	const_cstr lastSlash = &i_pathStr[0];
	const_cstr nextCh = lastSlash;
	do
	{
		nextCh++;
		if (*nextCh == '/' || *nextCh == 0)
		{
			size entryLen = size(nextCh - lastSlash) - 1;
			FLORAL_ASSERT(entryLen > 0 && entryLen < MAX_ENTRY_NAME_LENGTH);
			memset(path.entries[i], 0, MAX_ENTRY_NAME_LENGTH);
			memcpy(path.entries[i], lastSlash + 1, entryLen);
			lastSlash = nextCh;
			i++;
		}
	}
	while (*nextCh != 0);
	path.depth = i;

	return path;
}

// -------------------------------------------------------------------

relative_path build_relative_path(const_cstr i_pathStr)
{
	relative_path path;
	path.depth = 0;
	FLORAL_ASSERT_MSG(i_pathStr[0] != '/', "this is a relative_path, dude!");

	size i = 0;
	const_cstr lastSlash = &i_pathStr[0];
	const_cstr nextCh = lastSlash;
	do
	{
		nextCh++;
		if (*nextCh == '/' || *nextCh == 0)
		{
			size entryLen = size(nextCh - lastSlash);
			FLORAL_ASSERT(entryLen > 0 && entryLen < MAX_ENTRY_NAME_LENGTH);
			memset(path.entries[i], 0, MAX_ENTRY_NAME_LENGTH);
			memcpy(path.entries[i], lastSlash, entryLen);
			nextCh++;
			lastSlash = nextCh;
			i++;
		}
	}
	while (*nextCh != 0);
	path.depth = i;

	return path;
}

void concat_path(absolute_path* io_absPath, const relative_path& i_relPath)
{
	FLORAL_ASSERT(io_absPath->depth + i_relPath.depth < MAX_DEPTH);
	size finalDepth = io_absPath->depth;
	for (size i = 0; i < i_relPath.depth; i++, finalDepth++)
	{
		strcpy(io_absPath->entries[finalDepth], i_relPath.entries[i]);
	}
	io_absPath->depth = finalDepth;
}

void get_as_cstr(cstr o_buffer, const absolute_path& i_absPath)
{
	cstr pStr = o_buffer;
	for (size i = 0; i < i_absPath.depth; i++)
	{
		size entryLen = strlen(i_absPath.entries[i]);
		memcpy(pStr, i_absPath.entries[i], entryLen);
		pStr += entryLen;
		if (i != i_absPath.depth - 1)
		{
			*pStr = '/';
			pStr++;
		}
	}
	*pStr = 0;
}

// -------------------------------------------------------------------
}
