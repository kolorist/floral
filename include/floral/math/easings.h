#pragma once

#include "floral/stdaliases.h"

#include <cmath>

namespace floral {

	template <typename t_numeric_type>
	t_numeric_type ease_out_sin(f32 i_t, const t_numeric_type& i_start, const t_numeric_type& i_end) {
		t_numeric_type c = i_end - i_start;
		return (c * sinf(i_t * 3.14159f / 2.0f) + i_start);
	}

}
