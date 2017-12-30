#ifndef __FLORAL_WINDOWS_CONDITION_VARIABLE_H__
#define __FLORAL_WINDOWS_CONDITION_VARIABLE_H__

#include <stdaliases.h>

#include <Windows.h>

namespace floral {
	struct WindowsConditionVariable {
		HANDLE									pm_NotifyEvents[2];
		u32										pm_WaitersCount;
		CRITICAL_SECTION						pm_WaitersCountLock;
	};
}

#endif // __FLORAL_WINDOWS_CONDITION_VARIABLE_H__
