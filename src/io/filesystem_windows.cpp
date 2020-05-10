#include "floral/io/filesystem.h"

#include "Windows.h"

namespace floral
{
namespace platform
{
// -------------------------------------------------------------------

const bool get_application_directory(cstr o_buffer, const size i_maxLength)
{
	size ret = GetCurrentDirectory(i_maxLength, o_buffer);
	// replace all '\' with '/'
	if (ret > 0 && ret < i_maxLength)
	{
		for (size i = 0; i < ret; i++)
		{
			if (o_buffer[i] == '\\')
			{
				o_buffer[i] = '/';
			}
		}
		return true;
	}
	return false;
}

// -------------------------------------------------------------------
}
}
