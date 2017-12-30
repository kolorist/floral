#ifndef __FLORAL_CONDITION_VARIABLE_H__
#define __FLORAL_CONDITION_VARIABLE_H__

#include <stdaliases.h>

#include <thread/Mutex.h>

#if defined(PLATFORM_WINDOWS)
#include "WindowsConditionVariable.h"
#elif defined (PLATFORM_POSIX)
#include "PosixConditionVariable.h"
#endif

namespace floral {

#if defined(PLATFORM_WINDOWS)
	typedef WindowsConditionVariable			ConditionVariable;
#elif defined(PLATFORM_POSIX)
	typedef PosixConditionVariable				ConditionVariable;
#endif

	typedef ConditionVariable*					ConditionVariablePtr;
	typedef ConditionVariable&					ConditionVariableRef;

	////////////////////////////////////////////
	void										InitConditionVariable(ConditionVariableRef condVar);
	void										WaitForCondition(ConditionVariableRef condVar, MutexRef mtx);
	void										NotifyOneWaiter(ConditionVariableRef condVar);
	void										NotifyAllWaiters(ConditionVariableRef condVar);
	void										ReleaseConditionVariable(ConditionVariableRef condVar);
	////////////////////////////////////////////
}

#endif // __FLORAL_CONDITION_VARIABLE_H__
