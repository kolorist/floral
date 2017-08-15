#ifndef __FLORAL_FUNCTOR_H__
#define __FLORAL_FUNCTOR_H__

#include <types/type_traits.h>
#include <types/type_list.h>

template <typename _ReturnType, typename _Params = null_type> class function_base;

template <typename _ReturnType>
class function_base<_ReturnType, null_type> {
public:
	virtual _ReturnType Execute() = 0;
};

template <typename _ReturnType, typename _P0>
class function_base<_ReturnType, type_list_1(_P0)> {
public:
	virtual _ReturnType Execute(_P0) = 0;
};

template <typename _ReturnType, typename _P0, typename _P1>
class function_base<_ReturnType, type_list_2(_P0, _P1)> {
public:
	virtual _ReturnType Execute(_P0, _P1) = 0;
};

//////////////////////////////////////////////////////////////////////////
template <typename _ObjectType, typename _ReturnType, typename _Params = null_type> class functor_impl;

template <typename _ObjectType, typename _ReturnType>
class functor_impl<_ObjectType, _ReturnType, null_type> : public function_base<_ReturnType, null_type> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef ReturnType(ObjectType::*MemFuncType)();

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute()
	{
		return (m_pObj->*m_Func)();
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

template <typename _ObjectType, typename _ReturnType, typename _P0>
class functor_impl<_ObjectType, _ReturnType, type_list_1(_P0)> : public function_base<_ReturnType, type_list_1(_P0)> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef _P0									Param0;
	typedef ReturnType(ObjectType::*MemFuncType)(Param0);

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute(Param0 p0)
	{
		return (m_pObj->*m_Func)(p0);
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

template <typename _ObjectType, typename _ReturnType, typename _P0, typename _P1>
class functor_impl<_ObjectType, _ReturnType, type_list_2(_P0, _P1)> : public function_base<_ReturnType, type_list_2(_P0, _P1)> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef _P0									Param0;
	typedef _P1									Param1;
	typedef ReturnType(ObjectType::*MemFuncType)(Param0, Param1);

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute(Param0 p0, Param1 p1)
	{
		return (m_pObj->*m_Func)(p0, p1);
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

template <typename _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2>
class functor_impl<_ObjectType, _ReturnType, type_list_3(_P0, _P1, _P2)> : 
	public function_base<_ReturnType, type_list_3(_P0, _P1, _P2)> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef _P0									Param0;
	typedef _P1									Param1;
	typedef _P2									Param2;
	typedef ReturnType(ObjectType::*MemFuncType)(Param0, Param1, Param2);

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute(Param0 p0, Param1 p1, Param2 p2)
	{
		return (m_pObj->*m_Func)(p0, p1, p2);
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

template <typename _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2, typename _P3>
class functor_impl<_ObjectType, _ReturnType, type_list_4(_P0, _P1, _P2, _P3)> : 
	public function_base<_ReturnType, type_list_4(_P0, _P1, _P2, _P3)> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef _P0									Param0;
	typedef _P1									Param1;
	typedef _P2									Param2;
	typedef _P3									Param3;
	typedef ReturnType(ObjectType::*MemFuncType)(Param0, Param1, Param2, Param3);

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute(Param0 p0, Param1 p1, Param2 p2, Param3 p3)
	{
		return (m_pObj->*m_Func)(p0, p1, p2, p3);
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

template <typename _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2, typename _P3, typename _P4>
class functor_impl<_ObjectType, _ReturnType, type_list_5(_P0, _P1, _P2, _P3, _P4)> : 
	public function_base<_ReturnType, type_list_5(_P0, _P1, _P2, _P3, _P4)> {
protected:
	typedef _ObjectType							ObjectType;
	typedef _ReturnType							ReturnType;
	typedef _P0									Param0;
	typedef _P1									Param1;
	typedef _P2									Param2;
	typedef _P3									Param3;
	typedef _P4									Param4;
	typedef ReturnType(ObjectType::*MemFuncType)(Param0, Param1, Param2, Param3, Param4);

public:
	functor_impl(to_pointer_t<ObjectType> pObj, MemFuncType func)
		: m_pObj(pObj)
		, m_Func(func)
	{

	}

	ReturnType Execute(Param0 p0, Param1 p1, Param2 p2, Param3 p3, Param4 p4)
	{
		return (m_pObj->*m_Func)(p0, p1, p2, p3, p4);
	}

private:
	to_pointer_t<ObjectType>					m_pObj;
	MemFuncType									m_Func;
};

//////////////////////////////////////////////////////////////////////////
template <typename _ObjectType, typename _ReturnType, typename _Params>
class functor_handler : public functor_impl<_ObjectType, _ReturnType, _Params> {

	typedef typename functor_impl<_ObjectType, _ReturnType, _Params>		FImpl;
	typedef typename tl_fb_type_at_t<0, _Params, null_type> param0;
	typedef typename tl_fb_type_at_t<1, _Params, null_type> param1;
	typedef typename tl_fb_type_at_t<2, _Params, null_type> param2;
	typedef typename tl_fb_type_at_t<3, _Params, null_type> param3;
	typedef typename tl_fb_type_at_t<4, _Params, null_type> param4;

	typedef _ObjectType						object_type;
	typedef _ReturnType						return_type;

public:
	typedef typename FImpl::MemFuncType	mem_function_type;

public:
	functor_handler(to_pointer_t<object_type> pObj, mem_function_type func)
		: functor_impl(pObj, func)
	{
		m_Impl = this;
	}

	return_type operator()() {
		return m_Impl->Execute();
	}

	return_type operator()(param0 p0) {
		return m_Impl->Execute(p0);
	}

	return_type operator()(param0 p0, param1 p1) {
		return m_Impl->Execute(p0, p1);
	}

	return_type operator()(param0 p0, param1 p1, param2 p2) {
		return m_Impl->Execute(p0, p1, p2);
	}

	return_type operator()(param0 p0, param1 p1, param2 p2, param3 p3) {
		return m_Impl->Execute(p0, p1, p2, p3);
	}

	return_type operator()(param0 p0, param1 p1, param2 p2, param3 p3, param4 p4) {
		return m_Impl->Execute(p0, p1, p2, p3, p4);
	}

private:
	FImpl*									m_Impl;
};

//////////////////////////////////////////////////////////////////////////
template <class _ObjectType, typename _ReturnType> class functor;

template <class _ObjectType, typename _ReturnType>
class functor<_ObjectType, _ReturnType()> : public functor_handler<_ObjectType, _ReturnType, null_type> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};

template <class _ObjectType, typename _ReturnType, typename _P0>
class functor<_ObjectType, _ReturnType(_P0)> : public functor_handler<_ObjectType, _ReturnType, type_list_1(_P0)> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};

template <class _ObjectType, typename _ReturnType, typename _P0, typename _P1>
class functor<_ObjectType, _ReturnType(_P0, _P1)> : public functor_handler<_ObjectType, _ReturnType, type_list_2(_P0, _P1)> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};

template <class _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2>
class functor<_ObjectType, _ReturnType(_P0, _P1, _P2)> : public functor_handler<_ObjectType, _ReturnType, type_list_3(_P0, _P1, _P2)> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};

template <class _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2, typename _P3>
class functor<_ObjectType, _ReturnType(_P0, _P1, _P2, _P3)> : 
	public functor_handler<_ObjectType, _ReturnType, type_list_4(_P0, _P1, _P2, _P3)> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};

template <class _ObjectType, typename _ReturnType, typename _P0, typename _P1, typename _P2, typename _P3, typename _P4>
class functor<_ObjectType, _ReturnType(_P0, _P1, _P2, _P3, _P4)> : 
	public functor_handler<_ObjectType, _ReturnType, type_list_5(_P0, _P1, _P2, _P3, _P4)> {
public:
	functor(to_pointer_t<_ObjectType> pObj, mem_function_type func)
		: functor_handler(pObj, func)
	{}
};
//////////////////////////////////////////////////////////////////////////
template <typename _FuncSig> class generic_callback;

template <typename _RetType>
class generic_callback<_RetType()> {
public:
	template <typename __ObjectType, typename FuncPtr = _RetType(__ObjectType::*)()>
	generic_callback(__ObjectType* pObj, FuncPtr func)
		: m_Function(new functor<__ObjectType, _RetType()>(pObj, func))
	{}

	_RetType operator()() {
		return m_Function->Execute();
	}
private:
	function_base<_RetType, null_type>*		m_Function;
};

template <typename _RetType, typename _Param0>
class generic_callback<_RetType(_Param0)> {
public:
	template <typename __ObjectType, typename FuncPtr = _RetType(__ObjectType::*)(_Param0)>
	generic_callback(__ObjectType* pObj, FuncPtr func)
		: m_Function(new functor<__ObjectType, _RetType()>(pObj, func))
	{}

	_RetType operator()(_Param0 p0) {
		return m_Function->Execute(p0);
	}
private:
	function_base<_RetType, null_type>*		m_Function;
};

template <typename _RetType, typename _Param0, typename _Param1>
class generic_callback<_RetType(_Param0, _Param1)> {
public:
	generic_callback()
		: m_Function(nullptr)
	{}

	template <typename __ObjectType, typename FuncPtr = _RetType(__ObjectType::*)(_Param0, _Param1)>
	generic_callback(__ObjectType* pObj, FuncPtr func)
		: m_Function(new functor<__ObjectType, _RetType()>(pObj, func))
	{}

	template <typename __ObjectType, typename FuncPtr = _RetType(__ObjectType::*)(_Param0, _Param1)>
	void bind(__ObjectType* pObj, FuncPtr func)
	{
		m_Function = new functor<__ObjectType, _RetType(_Param0, _Param1)>(pObj, func);
	}

	_RetType operator()(_Param0 p0, _Param1 p1) {
		return m_Function->Execute(p0, p1);
	}
private:
	function_base<_RetType, null_type>*		m_Function;
};

#endif // __FLORAL_FUNCTOR_H__