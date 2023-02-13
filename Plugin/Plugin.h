#pragma once


namespace plugin
{
	extern "C"
	{
		__declspec(dllexport) const char* getName();
		__declspec(dllexport) void onLoad();
		__declspec(dllexport) void onUpdate(float deltaTime);
	}
}