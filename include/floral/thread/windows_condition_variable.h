#pragma once

#include "floral/stdaliases.h"

#include "mutex.h"

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