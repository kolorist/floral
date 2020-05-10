namespace floral
{
// -------------------------------------------------------------------

template <class t_allocator>
filesystem<t_allocator>* create_filesystem(const absolute_path& i_workingDir, t_allocator* i_allocator)
{
	filesystem<t_allocator>* fs = i_allocator->template allocate<filesystem<t_allocator>>();
	fs->allocator = i_allocator;
	fs->workingStack.reserve(4, i_allocator);
	fs->workingStack.push_back(i_workingDir);
	return fs;
}

template <class t_allocator>
const absolute_path& get_working_directory(const filesystem<t_allocator>* i_fs)
{
	return i_fs->workingStack[i_fs->workingStack.get_size() - 1];
}

template <class t_allocator>
file_info open_file_read(const filesystem<t_allocator>* i_fs, const relative_path& i_relPath)
{
	absolute_path* absPath = i_fs->allocator->template allocate<absolute_path>();
	*absPath = get_working_directory(i_fs);
	concat_path(absPath, i_relPath);

	// TODO: make open_file accept absolute_path as parameter
	c8 absPathCstr[MAX_PATH_LENGTH];
	get_as_cstr(absPathCstr, *absPath);
	i_fs->allocator->free(absPath);
	return open_file(absPathCstr);
}

// -------------------------------------------------------------------
}

