#ifndef __FLORAL_ASSERT_H__
#define __FLORAL_ASSERT_H__

#include <stdaliases.h>

namespace floral {

	enum class assert_action_e {
		abort = 0,
		debug_break,
		ignore
	};

	void										get_stack_trace(cstr stackTraceBuffer);

	assert_action_e								assertion_report(const_cstr expr, const_cstr file, const u32 line);
	assert_action_e								assertion_report_msg(const_cstr expr, const_cstr msg, const_cstr file, const u32 line);
	assert_action_e								assertion_report_msgonly(const_cstr msg, const_cstr file, const u32 line);
	assert_action_e								assertion_report_dlg(const_cstr title, const_cstr msg, const_cstr file, const u32 line);

#if 1

#define FLORAL_DEBUG_BREAK						__debugbreak

#define FLORAL_ASSERT(x)						\
	do {										\
		if (!(x)) {								\
			switch (floral::assertion_report(#x, __FILE__, __LINE__)) {	\
				case floral::assert_action_e::debug_break: \
					FLORAL_DEBUG_BREAK();		\
					break;						\
				case floral::assert_action_e::abort:	\
					exit(1);					\
					break;						\
				default:						\
					break;						\
			}									\
		}										\
	} while(0)

#define FLORAL_ASSERT_MSG(x, msg)				\
	do {										\
		if (!(x)) {								\
			switch (floral::assertion_report_msg(#x, msg, __FILE__, __LINE__)) {	\
				case floral::assert_action_e::debug_break: \
					FLORAL_DEBUG_BREAK();		\
					break;						\
				case floral::assert_action_e::abort:	\
					exit(1);					\
					break;						\
				default:						\
					break;						\
			}									\
		}										\
	} while(0)

#define FLORAL_ASSERT_MSG_ONLY(x, msg)			\
	do {										\
		if (!(x)) {								\
			switch (floral::assertion_report_msgonly(msg, __FILE__, __LINE__)) {	\
				case floral::assert_action_e::debug_break: \
					FLORAL_DEBUG_BREAK();		\
					break;						\
				case floral::assert_action_e::abort:	\
					exit(1);					\
					break;						\
				default:						\
					break;						\
			}									\
		}										\
	} while(0)

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
