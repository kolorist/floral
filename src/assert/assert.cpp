#include "assert/assert.h"

#include <Windows.h>
#include <stdio.h>
#include <commctrl.h>

#include <assert/StackWalker.h>
#include <thread/mutex.h>

// use this pragma in order to enable visual style v6 by generating application manifest
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace floral {

	static bool g_stack_walker_init				= false;
	static StackWalker							g_stack_walker;

	static mutex								g_stacktrace_mtx;

	void get_stack_trace(cstr stackTraceBuffer)
	{
		// StackWalker is not thread-safe, we have to guard it to prevent race-condition
		floral::lock_guard traceGuard(g_stacktrace_mtx);

		if (!g_stack_walker_init) {
			g_stack_walker.LoadModules();
			g_stack_walker_init = true;
		}

		if (stackTraceBuffer)
			g_stack_walker.ShowCallstack(stackTraceBuffer);
	}

	assert_action_e assertion_report(const_cstr expr, const_cstr file, const u32 line)
	{
		return assertion_report_dlg(expr, "", file, line);
	}

	assert_action_e assertion_report_msg(const_cstr expr, const_cstr msg, const_cstr file, const u32 line)
	{
		return assertion_report_dlg(expr, msg, file, line);
	}

	assert_action_e assertion_report_msgonly(const_cstr msg, const_cstr file, const u32 line)
	{
		return assertion_report_dlg("", msg, file, line);
	}

	assert_action_e assertion_report_dlg(const_cstr title, const_cstr msg, const_cstr file, const u32 line)
	{
		s32 buttonPressed = 0;
		wchar_t wTitle[1024];
		wchar_t wMsg[4096];
		wchar_t wFile[1024];
		MultiByteToWideChar(CP_ACP, 0, title, -1, wTitle, 1024);
		MultiByteToWideChar(CP_ACP, 0, msg, -1, wMsg, 4096);
		MultiByteToWideChar(CP_ACP, 0, file, -1, wFile, 1024);

		wchar_t wContent[4096];
		c8 stackTrace[8192];
		wchar_t wStackTrace[8192];
		_snwprintf(wContent, 8192, L"File: %s\nLine: %d\nMessage: %s",
				wFile, line, wMsg);
		memset(stackTrace, 0, sizeof(stackTrace));
		get_stack_trace(stackTrace);
		MultiByteToWideChar(CP_ACP, 0, stackTrace, -1, wStackTrace, 8192);

		TASKDIALOGCONFIG config = { 0 };
		const TASKDIALOG_BUTTON buttons[]   = { 
			{ IDOK,		L"Abort" },
			{ IDRETRY,	L"Debug break" },
			{ IDCLOSE,	L"Ignore" }
		};
		config.cbSize							= sizeof(config);
		config.hInstance						= NULL;
		config.dwFlags							= TDF_SIZE_TO_CONTENT | TDF_EXPAND_FOOTER_AREA;
		config.pszWindowTitle					= L"floral assertion failed!";
		config.pszMainIcon						= TD_ERROR_ICON;
		config.pszMainInstruction				= wTitle;
		config.pszContent						= wContent;
		config.pButtons							= buttons;
		config.cButtons							= ARRAYSIZE(buttons);
		config.pszExpandedInformation			= wStackTrace;
		config.pszExpandedControlText			= L"Hide Stacktrace";
		config.pszCollapsedControlText			= L"Show Stacktrace";

		TaskDialogIndirect(&config, &buttonPressed, NULL, NULL);

		switch (buttonPressed) {
			case IDOK:
				return assert_action_e::abort;
			case IDRETRY:
				return assert_action_e::debug_break;
			case IDCLOSE:
				return assert_action_e::ignore;
			default:
				return assert_action_e::ignore;
		}
	}
}
