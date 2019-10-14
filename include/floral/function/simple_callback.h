#pragma once

#include "floral/stdaliases.h"

namespace floral {

template <typename t_ret, typename ... t_params>
class simple_callback {
private:
	typedef t_ret(*invoker_t)(voidptr, t_params...);

public:
	simple_callback()
		: m_callee(nullptr)
		, m_invoker(nullptr)
	{}

	explicit simple_callback(invoker_t invoker)
		: m_callee(nullptr)
		, m_invoker(invoker)
	{}

	simple_callback(voidptr pObj, invoker_t invoker)
		: m_callee(pObj)
		, m_invoker(invoker)
	{}

	template <typename t_object, t_ret(t_object::*t_func)(t_params...)>
	static simple_callback<t_ret, t_params...> make(t_object* pObj) {
		simple_callback<t_ret, t_params...> retCb;
		retCb.bind<t_object, t_func>(pObj);
		return retCb;
	}

	template <t_ret(*t_object)(t_params...)>
	static simple_callback<t_ret, t_params...> make() {
		simple_callback<t_ret, t_params...> retCb;
		retCb.bind<t_object>();
		return retCb;
	}

	template <typename t_object, t_ret(t_object::*t_func)(t_params...)>
	void bind(t_object* pObj) {
		m_callee = pObj;
		m_invoker = &member_function_invoker<t_object, t_func>;
	}

	template <t_ret(*t_object)(t_params...)>
	void bind() {
		m_callee = nullptr;
		m_invoker = &free_function_invoker<t_object>;
	}

	t_ret operator()(t_params ... params) {
		return (*m_invoker)(m_callee, params...);
	}

private:
	template <typename t_object, t_ret(t_object::*t_func)(t_params...)>
	static t_ret member_function_invoker(voidptr pObj, t_params ... params) {
		t_object* callee = (t_object*)pObj;
		return (callee->*t_func)(params...);
	}

	template <t_ret(*t_object)(t_params...)>
	static t_ret free_function_invoker(voidptr, t_params ... params) {
		return (*t_object)(params...);
	}

private:
	voidptr										m_callee;
	invoker_t									m_invoker;
};

// But when put MakeSimpleCallback outside of the struct, we can make callback in a magnificent way:
// MakeSimpleCallback(pObj, &Obj::Func);
// or MakeSimpleCallback(&Obj::Func);

// WARNING: DO NOT USE THIS AS THEY ARE WRONG
// Why they are wrong? Because we are trying to assign a run-time function pointer to
// a compile-time template parameter. It simply does not work!
template <class _ObjectType, class t_ret>
simple_callback<t_ret> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)()) {
	return simple_callback<t_ret>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0>
simple_callback<t_ret, _P0> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0)) {
	return simple_callback<t_ret, _P0>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0, class _P1>
simple_callback<t_ret, _P0, _P1> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0, _P1)) {
	return simple_callback<t_ret, _P0, _P1>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0, class _P1, class _P2>
simple_callback<t_ret, _P0, _P1, _P2> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0, _P1, _P2)) {
	return simple_callback<t_ret>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0, class _P1, class _P2, class _P3>
simple_callback<t_ret, _P0, _P1, _P2, _P3> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3)) {
	return simple_callback<t_ret>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0, class _P1, class _P2, class _P3, class _P4>
simple_callback<t_ret, _P0, _P1, _P2, _P3, _P4> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3, _P4)) {
	return simple_callback<t_ret>(pObj, pFunc);
}

template <class _ObjectType, class t_ret, class _P0, class _P1, class _P2, class _P3, class _P4, class _P5>
simple_callback<t_ret, _P0, _P1, _P2, _P3, _P4, _P5> MakeSimpleCallback(_ObjectType* pObj, 
	t_ret(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3, _P4, _P5)) {
	return simple_callback<t_ret>(pObj, pFunc);
}

}