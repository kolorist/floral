#ifndef __FLORAL_PATH_H__
#define __FLORAL_PATH_H__

#include <stdaliases.h>

namespace floral {
	class path {
	public:
		path();
		explicit path(const_cstr pathNullTerminated);
		~path();

		const_cstr									ToCStr() const						{ return m_PathStr; }
		const_cstr									GetFileName() const					{ return m_FileName; }
		const_cstr									GetFileNameNoExt() const			{ return m_FileNameNoExt; }
		const_cstr									GetCurrentDir() const				{ return m_CurrentDir; }

		const bool									IsFile() const						{ return m_IsFile; }
		const bool									IsDir() const						{ return !m_IsFile; }

		const bool									operator==(const path& other) const;

	private:
		void										ComputeInfos(const_cstr newPath);

	private:
		u32											m_CRC32;
		c8											m_PathStr[1024];
		c8											m_FileName[256];
		c8											m_FileNameNoExt[256];
		c8											m_CurrentDir[1024];
		bool										m_IsFile;
	};
}

#endif // __FLORAL_PATH_H__
