#include<Windows.h>
#include"LoaderWin.h"

namespace win
{
	namespace dll
	{
		void* LoadDLL(const wchar_t* filename)
		{
			return reinterpret_cast<void*>(LoadLibrary(filename));
		}
		void FreeDll(void* HINST)
		{
			FreeLibrary(reinterpret_cast<HINSTANCE>(HINST));
		}
		void* GetProcAdd(void*HINST, const char*Name)
		{
			return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HINSTANCE>(HINST), Name));
		}
	}
	
}
//LPCSTR
//GetProcAddress
//GetProcAddress(reinterpret_cast<HINSTANCE>(m_lib), "getName");
//GetProcAddress();