#ifndef __FLORAL_THREAD_BASE_H__
#define __FLORAL_THREAD_BASE_H__

#include <stdaliases.h>

namespace floral {
	typedef void								(*ThreadFuncType)(voidptr pData);

	struct ThreadBase {
		ThreadFuncType							EntryPoint;
		voidptr									Data;
	};
}

#endif // __FLORAL_THREAD_BASE_H__
