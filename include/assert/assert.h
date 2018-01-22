#ifndef __FLORAL_ASSERT_H__
#define __FLORAL_ASSERT_H__

#include <stdaliases.h>

namespace floral {

#if 0
	void										assertion_fail(const_cstr expr, const_cstr file, u32 line);
	void										assertion_fail(const_cstr expr, const_cstr msg, const_cstr file, u32 line);
#endif
	void										assertion_fail(const_cstr msg, const_cstr file, const u32 line);

#if 0

#define FLORAL_ASSERT(x)						\
	do { if (!(x)) { assertion_fail(#x, __FILE__, __LINE__); } } while(0)

#define FLORAL_ASSERT_MSG(x, msg)				\
	do { if (!(x)) { assertion_fail(#x, msg, __FILE__, __LINE__); } } while(0)

#define FLORAL_ASSERT_MSG_ONLY(x, msg)			\
	do { if (!(x)) { assertion_fail(msg, __FILE__, __LINE__); } } while (0)

#else

#define FLORAL_ASSERT(x)						\
	do { (void)sizeof(x); } while(0)
#define FLORAL_ASSERT_MSG(x, msg)				\
	do { (void)sizeof(x); } while(0)

#define FLORAL_ASSERT_MSG_ONLY(x, msg)			\
	do { (void)sizeof(x); } while(0)

#endif
}

#endif // __FLORAL_ASSERT_H__
