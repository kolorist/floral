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

// -------------------------------------------------------------------

template <class t_allocator>
void destroy_filesystem(filesystem<t_allocator>** i_fs)
{
	(*i_fs)->allocator->free_all();
	*i_fs = nullptr;
}

// -------------------------------------------------------------------

template <class t_filesystem>
void push_directory(t_filesystem* io_fs, const relative_path& i_relPath)
{
	absolute_path absPath = get_working_directory(io_fs);
	concat_path(&absPath, i_relPath);
	io_fs->workingStack.push_back(absPath);
}

// -------------------------------------------------------------------

template <class t_filesystem>
void push_directory(t_filesystem* io_fs, const absolute_path& i_path)
{
	io_fs->workingStack.push_back(i_path);
}

// -------------------------------------------------------------------

template <class t_filesystem>
void pop_directory(t_filesystem* io_fs)
{
	io_fs->workingStack.pop_back();
}

// -------------------------------------------------------------------

template <class t_allocator>
const absolute_path& get_working_directory(const filesystem<t_allocator>* i_fs)
{
	return i_fs->workingStack[i_fs->workingStack.get_size() - 1];
}

// -------------------------------------------------------------------

template <class t_allocator>
file_info open_file_read(const filesystem<t_allocator>* i_fs, const relative_path& i_relPath)
{
	absolute_path* absPath = i_fs->allocator->template allocate<absolute_path>();
	*absPath = get_working_directory(i_fs);
	concat_path(absPath, i_relPath);

	file_info fileInfo = open_file_read(i_fs, *absPath);
	i_fs->allocator->free(absPath);
	return fileInfo;
}

// -------------------------------------------------------------------

template <class t_allocator>
file_info open_file_read(const filesystem<t_allocator>* i_fs, const absolute_path& i_absPath)
{
	c8 absPathCstr[MAX_PATH_LENGTH];
	get_as_cstr(absPathCstr, i_absPath);
	return open_file(absPathCstr);
}

// -------------------------------------------------------------------

template <class t_allocator>
file_info open_file_write(const filesystem<t_allocator>* i_fs, const relative_path& i_relPath)
{
	absolute_path* absPath = i_fs->allocator->template allocate<absolute_path>();
	*absPath = get_working_directory(i_fs);
	concat_path(absPath, i_relPath);

	file_info fileInfo = open_file_write(i_fs, *absPath); 
	i_fs->allocator->free(absPath);
	return fileInfo;
}

// -------------------------------------------------------------------

template <class t_allocator>
file_info open_file_write(const filesystem<t_allocator>* i_fs, const absolute_path& i_absPath)
{
	c8 absPathCstr[MAX_PATH_LENGTH];
	get_as_cstr(absPathCstr, i_absPath);
	return open_output_file(absPathCstr);
}

// -------------------------------------------------------------------
}

