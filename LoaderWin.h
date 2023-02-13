#pragma once


namespace win
{
	namespace dll
	{
		extern void* LoadDLL(const wchar_t* filename);
		extern void FreeDll(void* m_lib);
		extern void* GetProcAdd(void* HINST, const char* Name);
	}
}