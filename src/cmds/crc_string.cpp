#include "cmds/crc_string.h"

#include <math/utils.h>

namespace floral {
	crc_string::crc_string()
	{
		crc32 = 0;
#if defined(FLORAL_DEBUG_CRCSTRING)
		memset(c_str, 0, sizeof(c_str));
#endif
	}

	crc_string::crc_string(const_cstr nullTerminatedStr)
	{
		crc32 = compute_crc32_naive(nullTerminatedStr);
#if defined(FLORAL_DEBUG_CRCSTRING)
		strcpy(c_str, nullTerminatedStr);
#endif
	}

	const bool crc_string::operator==(const crc_string& other) const
	{
		return (crc32 == other.crc32);
	}

	crc_string& crc_string::operator=(const crc_string& other)
	{
		crc32 = other.crc32;
#if defined(FLORAL_DEBUG_CRCSTRING)
		strcpy(c_str, other.c_str);
#endif
		return *this;
	}
}
