#include "floral/cmds/path.h"

#include "floral/stdaliases.h"
#include "floral/math/utils.h"

#include <cstring>
#include <stdio.h>

namespace floral {
	
	path::path()
	{
		EmptyPath();
	}

	path::path(const_cstr pathNullTerminated)
		: path()
	{
		UpdatePath(pathNullTerminated);
	}

	path::path(const path& other)
		: path(other.pm_PathStr)
	{ }

	const bool path::operator==(const path& other) const
	{
		return (m_CRC32 == other.m_CRC32);
	}

	void path::UpdatePath(const_cstr newPath)
	{
		m_CRC32 = compute_crc32_naive(newPath);
		strcpy(pm_PathStr, newPath);

		// is file?
		sidx idx = strlen(pm_PathStr) - 1;
		while (idx >= 0 && pm_PathStr[idx] != '.' && pm_PathStr[idx] != '/') idx--;
		if (idx >= 0 && pm_PathStr[idx] == '.') pm_IsFile = true;

		if (pm_IsFile) {
			while (idx >= 0 && pm_PathStr[idx] != '/') idx--;
			strcpy(pm_FileName, &pm_PathStr[idx + 1]);
			strcpy(pm_FileNameNoExt, &pm_PathStr[idx + 1]);
			sidx dotPos = strlen(pm_FileNameNoExt) - 1;
			while (dotPos >= 0 && pm_FileNameNoExt[dotPos] != '.') dotPos--;
			memset(&pm_FileNameNoExt[dotPos], 0, strlen(pm_FileNameNoExt) - dotPos);
			strcpy(pm_CurrentDir, pm_PathStr);
			memset(&pm_CurrentDir[idx], 0, strlen(pm_PathStr) - idx);
			if (strlen(pm_CurrentDir) == 0) 
				strcpy(pm_CurrentDir, ".");
		}
		else {
			strcpy(pm_CurrentDir, pm_PathStr);
		}
	}

	void path::EmptyPath()
	{
		m_CRC32 = 0;
		pm_IsFile = false;
		memset(pm_PathStr, 0, sizeof(pm_PathStr));
		memset(pm_FileName, 0, sizeof(pm_FileName));
		memset(pm_CurrentDir, 0, sizeof(pm_CurrentDir));
		memset(pm_FileNameNoExt, 0, sizeof(pm_FileNameNoExt));
	}

	////////////////////////////////////////////
	void combine_path(path& lhs, const path& rhs)
	{
		c8 tmpPath[1024];
		memset(tmpPath, 0, sizeof(tmpPath));

		if (lhs.pm_PathStr[0] == 0) {
			sprintf(tmpPath, "%s", rhs.pm_PathStr);
			lhs.UpdatePath(tmpPath);
		}
		else {
			sprintf(tmpPath, "%s/%s", lhs.pm_PathStr, rhs.pm_PathStr);
			lhs.UpdatePath(tmpPath);
		}
	}
}
