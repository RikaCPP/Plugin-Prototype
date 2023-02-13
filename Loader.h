#pragma once
#include"LoaderWin.h"

class Plugin
{
private:
	bool isOld = false;
	bool IsCoppy = false;
	typedef const char* (*getNameType)();
	typedef void (*onLoadType)();
	typedef void (*onUpdateType)(float);
	void* m_lib;

public:
	Plugin(const wchar_t* filename);
	Plugin(const Plugin& p);
	~Plugin();
	getNameType getName;
	onLoadType onLoad;
	onUpdateType onUpdate;
private:

};