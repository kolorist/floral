#ifndef __FLORAL_PATH_H__
#define __FLORAL_PATH_H__

#include <stdaliases.h>

namespace floral {
	struct path {
	public:
		path();
		explicit path(const_cstr pathNullTerminated);
		path(const path& other);

		const bool								IsFile() const						{ return pm_IsFile; }
		const bool								IsDir() const						{ return !pm_IsFile; }

		const bool								operator==(const path& other) const;

		void									UpdatePath(const_cstr newPath);
		void									EmptyPath();

	private:
		u32										m_CRC32;

	public:
		c8										pm_PathStr[1024];
		c8										pm_FileName[256];
		c8										pm_FileNameNoExt[256];
		c8										pm_CurrentDir[1024];
		bool									pm_IsFile;
	};
	////////////////////////////////////////////
	void										combine_path(path& lhs, const path& rhs);
}

#endif // __FLORAL_PATH_H__
