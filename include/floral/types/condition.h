#pragma once

namespace floral
{
// ----------------------------------------------------------------------------

template <bool t_test_cond, class t_type0, class t_type1>
struct conditional
{
	using type = t_type0;
};

template <class t_type0, class t_type1>
struct conditional<false, t_type0, t_type1>
{
	using type = t_type1;
};

template <bool t_test_cond, class t_type0, class t_type1>
using conditional_t = typename conditional<t_test_cond, t_type0, t_type1>::type;

// ----------------------------------------------------------------------------
}
