#ifndef __FLORAL_SIMPLE_CALLBACK_H__
#define __FLORAL_SIMPLE_CALLBACK_H__

namespace floral {

template <typename _RetType, typename ... _Params>
class SimpleCallback {
private:
	typedef _RetType(*InvokerType)(void*, _Params...);

public:
	SimpleCallback()
		: m_Invoker(nullptr)
		, m_Callee(nullptr)
	{}

	explicit SimpleCallback(InvokerType invoker)
		: m_Invoker(invoker)
		, m_Callee(nullptr)
	{}

	SimpleCallback(void* pObj, InvokerType invoker)
		: m_Invoker(invoker)
		, m_Callee(pObj)
	{}

	template <typename __ObjectType, _RetType(__ObjectType::*__MemFunc)(_Params...)>
	static SimpleCallback<_RetType, _Params...> MakeCallback(__ObjectType* pObj) {
		SimpleCallback<_RetType, _Params...> retCb;
		retCb.Bind<__ObjectType, __MemFunc>(pObj);
		return retCb;
	}

	template <_RetType(*__MemFunc)(_Params...)>
	static SimpleCallback<_RetType, _Params...> MakeCallback() {
		SimpleCallback<_RetType, _Params...> retCb;
		retCb.Bind<__MemFunc>();
		return retCb;
	}

	template <typename __ObjectType, _RetType(__ObjectType::*__MemFunc)(_Params...)>
	void Bind(__ObjectType* pObj) {
		m_Callee = pObj;
		m_Invoker = &MemberFunctionInvoker<__ObjectType, __MemFunc>;
	}

	template <_RetType(*__MemFunc)(_Params...)>
	void Bind() {
		m_Callee = nullptr;
		m_Invoker = &FreeFunctionInvoker<__MemFunc>;
	}

	_RetType operator()(_Params ... params) {
		return (*m_Invoker)(m_Callee, params...);
	}

private:
	template <typename __ObjectType, _RetType(__ObjectType::*__MemFunc)(_Params...)>
	static _RetType MemberFunctionInvoker(void* pObj, _Params ... params) {
		__ObjectType* callee = (__ObjectType*)pObj;
		return (callee->*__MemFunc)(params...);
	}

	template <_RetType(*__MemFunc)(_Params...)>
	static _RetType FreeFunctionInvoker(void*, _Params ... params) {
		return (*__MemFunc)(params...);
	}

private:
	void*										m_Callee;
	InvokerType									m_Invoker;
};

// But when put MakeSimpleCallback outside of the struct, we can make callback in a magnificent way:
// MakeSimpleCallback(pObj, &Obj::Func);
// or MakeSimpleCallback(&Obj::Func);

// WARNING: DO NOT USE THIS AS THEY ARE WRONG
// Why they are wrong? Because we are trying to assign a run-time function pointer to
// a compile-time template parameter. It simply does not work!
template <class _ObjectType, class _RetType>
SimpleCallback<_RetType> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)()) {
	return SimpleCallback<_RetType>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0>
SimpleCallback<_RetType, _P0> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0)) {
	return SimpleCallback<_RetType, _P0>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0, class _P1>
SimpleCallback<_RetType, _P0, _P1> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0, _P1)) {
	return SimpleCallback<_RetType, _P0, _P1>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0, class _P1, class _P2>
SimpleCallback<_RetType, _P0, _P1, _P2> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0, _P1, _P2)) {
	return SimpleCallback<_RetType>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0, class _P1, class _P2, class _P3>
SimpleCallback<_RetType, _P0, _P1, _P2, _P3> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3)) {
	return SimpleCallback<_RetType>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0, class _P1, class _P2, class _P3, class _P4>
SimpleCallback<_RetType, _P0, _P1, _P2, _P3, _P4> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3, _P4)) {
	return SimpleCallback<_RetType>(pObj, pFunc);
}

template <class _ObjectType, class _RetType, class _P0, class _P1, class _P2, class _P3, class _P4, class _P5>
SimpleCallback<_RetType, _P0, _P1, _P2, _P3, _P4, _P5> MakeSimpleCallback(_ObjectType* pObj, 
	_RetType(_ObjectType::*pFunc)(_P0, _P1, _P2, _P3, _P4, _P5)) {
	return SimpleCallback<_RetType>(pObj, pFunc);
}

}

#endif // __FLORAL_SIMPLE_CALLBACK_H__