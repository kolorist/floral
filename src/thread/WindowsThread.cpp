#include "thread/WindowsThread.h"
#include "thread/Thread.h"						// api

namespace floral {

	DWORD WINAPI WindowsThreadFunction(LPVOID lpParam)
	{
		ThreadPtr myThread = (ThreadPtr)lpParam;
		(*myThread->EntryPoint)(myThread->Data);
		return 0;
	}

	void InitThread(ThreadRef rThread)
	{
		rThread.EntryPoint = nullptr;
		rThread.Data = nullptr;
		rThread.Id = 0;
		rThread.Handle = NULL;
	}

	void StartThread(ThreadRef rThread)
	{
		rThread.Handle = CreateThread(
				NULL,
				0,
				WindowsThreadFunction,
				&rThread,
				0,
				&(rThread.Id));
	}

	void WaitForThread(ThreadRef rThread)
	{
		WaitForSingleObject(rThread.Handle, INFINITE);
	}

	void ReleaseThread(ThreadRef rThread)
	{
		// nothing for now
	}
	////////////////////////////////////////////
}
