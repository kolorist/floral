#include "assert/assert.h"

#include <stdio.h>
#include <cassert>
#include <commctrl.h>

#include <assert/StackWalker.h>
#include <thread/mutex.h>

#include <Windows.h>
// use this pragma in order to enable visual style v6 by generating application manifest
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace floral {

	static bool g_stack_walker_init				= false;
	static StackWalker							g_stack_walker;

	static mutex								g_stacktrace_mtx;
	static mutex								g_dlg_mtx;

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

	static c8 s_stack_trace[4096];

	assert_action_e assertion_report_dlg(const_cstr title, const_cstr msg, const_cstr file, const u32 line)
	{
		memset(s_stack_trace, 0, sizeof(s_stack_trace));
		get_stack_trace(s_stack_trace);
#if 0
		wchar_t wTitle[256];
		wchar_t wMsg[2048];
		wchar_t wFile[512];
		wchar_t wContent[2048];
		wchar_t wStackTrace[4096];
		floral::lock_guard dlgGuard(g_dlg_mtx);
		s32 buttonPressed = 0;
		MultiByteToWideChar(CP_ACP, 0, title, -1, wTitle, 256);
		MultiByteToWideChar(CP_ACP, 0, msg, -1, wMsg, 2048);
		MultiByteToWideChar(CP_ACP, 0, file, -1, wFile, 512);

		_snwprintf(wContent, 2048, L"File: %s\nLine: %d\nMessage: %s",
				wFile, line, wMsg);
		MultiByteToWideChar(CP_ACP, 0, stackTrace, -1, wStackTrace, 4096);

		static TASKDIALOGCONFIG config = { 0 };
		static const TASKDIALOG_BUTTON buttons[]   = { 
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

		//TaskDialog(NULL, NULL, L"title", L"instruction", L"content", TDCBF_OK_BUTTON | TDCBF_YES_BUTTON, NULL, &buttonPressed);
		//MessageBox(NULL, stackTrace, title, MB_ABORTRETRYIGNORE);
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
#else
		c8 errorStr[8192];
		sprintf(errorStr, ">> expression: %s\n>> message: %s\n>> location: %s:%d\n>> stacktrace: \n%s",
				title, msg, file, line, s_stack_trace);

		s32 buttonPressed = MessageBox(NULL, errorStr, "floral assertion failed!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
		switch (buttonPressed) {
			case IDABORT:
				return assert_action_e::abort;
			case IDRETRY:
				return assert_action_e::debug_break;
			case IDIGNORE:
				return assert_action_e::ignore;
			default:
				return assert_action_e::ignore;
		}
#endif
	}
}
