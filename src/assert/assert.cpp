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
		c8 errorStr[8192];
		sprintf(errorStr, ">> expression: %s\n>> message: %s\n>> location: %s:%d\n>> stacktrace: \n%s\n",
				title, msg, file, line, s_stack_trace);
		OutputDebugStringA(errorStr);
		return floral::assert_action_e::debug_break;
	}
}
