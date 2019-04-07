#pragma once

#include <floral/stdaliases.h>
////////////////////////////////////////////////
#include <floral/containers/array.h>
#include <floral/containers/fast_array.h>
#include <floral/containers/queue.h>
#include <floral/containers/ring_buffer.h>
////////////////////////////////////////////////
#include <floral/gpds/vec.h>
#include <floral/gpds/mat.h>
#include <floral/gpds/geometry.h>
#include <floral/gpds/rect.h>
#include <floral/gpds/camera.h>
#include <floral/gpds/quaternion.h>
////////////////////////////////////////////////
#include <floral/cmds/path.h>
#include <floral/cmds/crc_string.h>
////////////////////////////////////////////////
#include <floral/math/utils.h>
#include <floral/math/intersect.h>
#include <floral/math/transform.h>
#include <floral/math/easings.h>
#include <floral/math/coordinate.h>
////////////////////////////////////////////////
#include <floral/thread/thread.h>
#include <floral/thread/mutex.h>
#include <floral/thread/condition_variable.h>
////////////////////////////////////////////////
#include <floral/types/type_traits.h>
#include <floral/types/type_list.h>
////////////////////////////////////////////////
#include <floral/assert/assert.h>
//----------------------------------------------
#include <floral/io/nativeio.h>
//----------------------------------------------
#include <floral/function/functor.h>
#include <floral/function/simple_callback.h>