#include "floral/io/filesystem.h"

#include "floral/io/nativeio.h"

namespace floral
{
namespace platform
{
// -------------------------------------------------------------------

static c8										s_workingDirectory[MAX_PATH_LENGTH];

void set_working_directory(const_cstr i_wdir)
{
	strcpy(s_workingDirectory, i_wdir);
}

// -------------------------------------------------------------------

const bool get_application_directory(cstr o_buffer, const size i_maxLength)
{
	o_buffer[0] = 0;
	size wdirLen = strlen(s_workingDirectory);
	if (wdirLen < i_maxLength)
	{
		strcpy(o_buffer, s_workingDirectory);

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
