#include "src/cmds/path.cpp"
#include "src/cmds/crc_string.cpp"

#include "src/gpds/geometry.cpp"
#include "src/gpds/camera.cpp"

#include "src/math/utils.cpp"
#include "src/math/transform.cpp"
#include "src/math/coordinate.cpp"
#include "src/math/intersect.cpp"

#include "src/thread/thread.cpp"
#include "src/thread/mutex.cpp"
#if defined(PLATFORM_WINDOWS)
#include "src/thread/windows_thread.cpp"
#include "src/thread/windows_mutex.cpp"
#include "src/thread/windows_condition_variable.cpp"
#elif defined(PLATFORM_POSIX)
#include "src/thread/posix_thread.cpp"
#include "src/thread/posix_mutex.cpp"
#include "src/thread/posix_condition_variable.cpp"
#else
// TODO: not supported
#endif

#if defined(PLATFORM_WINDOWS)
#include "src/assert/assert.cpp"
#include "src/assert/StackWalker.cpp"

#include "src/io/nativeio.cpp"
#elif defined(PLATFORM_POSIX)
#include "src/io/nativeio_posix.cpp"
#else
// TODO: not supported
#endif
