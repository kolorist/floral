#include "cmds/path.h"

#include <cstring>

#include <stdaliases.h>
#include <math/utils.h>

namespace floral {
	
	path::path()
		: m_CRC32(0)
		, m_IsFile(false)
	{
		memset(m_PathStr, 0, sizeof(m_PathStr));
		memset(m_FileName, 0, sizeof(m_FileName));
		memset(m_CurrentDir, 0, sizeof(m_CurrentDir));
		memset(m_FileNameNoExt, 0, sizeof(m_FileNameNoExt));
	}

	path::path(const_cstr pathNullTerminated)
		: path()
	{
		ComputeInfos(pathNullTerminated);
	}

	path::~path()
	{
		// nothing
	}

	const bool path::operator==(const path& other) const
	{
		return (m_CRC32 == other.m_CRC32);
	}

	//////////////////////////////////////////////////////////////////////////
	void path::ComputeInfos(const_cstr newPath)
	{
		m_CRC32 = compute_crc32_naive(newPath);
		strcpy_s(m_PathStr, sizeof(m_PathStr), newPath);

		// is file?
		s32 idx = strlen(m_PathStr) - 1;
		while (idx >= 0 && m_PathStr[idx] != '.' && m_PathStr[idx] != '/') idx--;
		if (idx >= 0 && m_PathStr[idx] == '.') m_IsFile = true;

		if (m_IsFile) {
			while (idx >= 0 && m_PathStr[idx] != '/') idx--;
			strcpy_s(m_FileName, sizeof(m_FileName), &m_PathStr[idx + 1]);
			strcpy_s(m_FileNameNoExt, sizeof(m_FileName), &m_PathStr[idx + 1]);
			s32 dotPos = strlen(m_FileNameNoExt) - 1;
			while (dotPos >= 0 && m_FileNameNoExt[dotPos] != '.') dotPos--;
			memset(&m_FileNameNoExt[dotPos], 0, strlen(m_FileNameNoExt) - dotPos);
			strcpy_s(m_CurrentDir, sizeof(m_CurrentDir), m_PathStr);
			// TOOD (fixme): when specifing a file in current directory without "./" part, the current dir will show up as empty string
			memset(&m_CurrentDir[idx], 0, strlen(m_PathStr) - idx);
			if (strlen(m_CurrentDir) == 0) 
				strcpy_s(m_CurrentDir, sizeof(m_CurrentDir), ".");
		}
		else {
			strcpy_s(m_CurrentDir, sizeof(m_CurrentDir), m_PathStr);
		}
	}

}