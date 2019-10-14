#pragma once

#include "floral/stdaliases.h"

#include "mutex.h"

#define WIN32_LEAN_AND_MEAN
// NOTE: we have to define NOMINMAX when including Windows.h because the min(), max()
// function of Windows API may conflict with floral::min() and floral::max()
#define NOMINMAX
#include <Windows.h>

namespace floral {
	struct windows_condition_variable {
		HANDLE									notify_events[2];
		u32										waiters_count;
		CRITICAL_SECTION						waiters_count_lock;

		windows_condition_variable();
		~windows_condition_variable();

		void wait(mutex_ref_t mtx);
		void notify_one();
		void notify_all();
	};
}