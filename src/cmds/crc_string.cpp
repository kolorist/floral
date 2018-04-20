#include "cmds/crc_string.h"

#include <math/utils.h>

namespace floral {
	crc_string::crc_string()
	{
		crc32 = 0;
		memset(c_str, 0, sizeof(c_str));
	}

	crc_string::crc_string(const_cstr nullTerminatedStr)
	{
		crc32 = compute_crc32_naive(nullTerminatedStr);
		strcpy(c_str, nullTerminatedStr);
	}

	const bool crc_string::operator==(const crc_string& other) const
	{
		return (crc32 == other.crc32);
	}

	crc_string& crc_string::operator=(const crc_string& other)
	{
		crc32 = other.crc32;
		strcpy(c_str, other.c_str);
		return *this;
	}
}
