#include "assert/assert.h"

#include <Windows.h>
#include <commctrl.h>

// use this pragma in order to enable visual style v6 by generating application manifest
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace floral {
	void assertion_fail(const_cstr msg, const_cstr file, const u32 line)
	{
		s32 buttonPressed = 0;
		wchar_t wMsg[4096];
		wchar_t wFile[1024];
		MultiByteToWideChar(CP_ACP, 0, msg, -1, wMsg, 4096);
		MultiByteToWideChar(CP_ACP, 0, file, -1, wFile, 1024);

		TASKDIALOGCONFIG config = { 0 };
		const TASKDIALOG_BUTTON buttons[]   = { 
			{ IDOK, L"Abort" },
			{ IDRETRY, L"Debug break" },
			{ IDCLOSE, L"Ignore" }
		};
		config.cbSize							= sizeof(config);
		config.hInstance						= NULL;
		//config.dwCommonButtons              = TDCBF_CANCEL_BUTTON;
		config.pszWindowTitle					= L"floral assertion failed!";
		config.pszMainIcon						= TD_ERROR_ICON;
		//config.pszMainInstruction				= L"";
		config.pszContent						= wMsg;
		config.pButtons							= buttons;
		config.cButtons							= ARRAYSIZE(buttons);
		config.pszExpandedInformation			= wMsg;
		config.pszExpandedControlText			= L"Stacktrace";
		config.pszCollapsedControlText			= L"Stacktrace";

		TaskDialogIndirect(&config, &buttonPressed, NULL, NULL);
	}
}
