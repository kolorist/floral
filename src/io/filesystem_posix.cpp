#include "floral/io/filesystem.h"

#include "floral/io/nativeio.h"

namespace floral
{
namespace platform
{
// -------------------------------------------------------------------

const bool get_application_directory(cstr o_buffer, const size i_maxLength)
{
	o_buffer[0] = 0;
	const_cstr wdir = get_working_directory();
	size wdirLen = strlen(wdir);
	if (wdirLen < i_maxLength)
	{
		strcpy(o_buffer, wdir);

		for (size i = 0; i < wdirLen; i++)
		{
			if (o_buffer[i] == '\\')
			{
				o_buffer[i] = '/';
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

// -------------------------------------------------------------------
}
}
