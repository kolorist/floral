#ifndef __FLORAL_H__
#define __FLORAL_H__

#include <stdaliases.h>
////////////////////////////////////////////////
#include <containers/array.h>
#include <containers/fast_array.h>
#include <containers/queue.h>
#include <containers/ring_buffer.h>
////////////////////////////////////////////////
#include <gpds/vec.h>
#include <gpds/mat.h>
#include <gpds/geometry.h>
#include <gpds/rect.h>
#include <gpds/camera.h>
////////////////////////////////////////////////
#include <cmds/path.h>
#include <cmds/crc_string.h>
////////////////////////////////////////////////
#include <math/utils.h>
#include <math/intersect.h>
#include <math/transform.h>
#include <math/easings.h>
#include <math/coordinate.h>
////////////////////////////////////////////////
#include <thread/thread.h>
#include <thread/mutex.h>
#include <thread/condition_variable.h>
////////////////////////////////////////////////
#include <types/type_traits.h>
#include <types/type_list.h>
////////////////////////////////////////////////
#include <assert/assert.h>
//----------------------------------------------
#include <io/nativeio.h>
//----------------------------------------------
#include <function/functor.h>
#include <function/simple_callback.h>

#endif // __FLORAL_H__
