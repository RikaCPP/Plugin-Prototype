#include"Loader.h"
#include"LoaderWin.h"
#include<iostream>

void ModConstBool(const bool* a, bool SetTo)
{
	bool* ptr;
	ptr = (bool*)(a);
	*ptr = SetTo;
}

Plugin::Plugin(const wchar_t* filename)
{
	m_lib = win::dll::LoadDLL(filename);
	if (m_lib == 0)
		throw "Could not Load Plugin";

	getName = (getNameType)win::dll::GetProcAdd(m_lib, "getName");
	onUpdate = (onUpdateType)win::dll::GetProcAdd(m_lib, "onUpdate");
	onLoad = (onLoadType)win::dll::GetProcAdd(m_lib, "onLoad");

	if (!getName)
		throw "No getName function in Plugin";
	if (!onUpdate)
		throw "No onUpdate function in Plugin";
	if (!onLoad)
		throw "No onLoad function in Plugin";
}

Plugin::~Plugin()
{
	std::cout << "isOld: " << isOld << "\n";
	std::cout << "~Plugin(): ";
	if (isOld == false)
	{
		std::cout << "isCoppy\n";
		win::dll::FreeDll(m_lib);
	}
	else
	{
		std::cout << "Original coppy\n";
	}
}

Plugin::Plugin(const Plugin& p)
{

	m_lib = p.m_lib;
	getName = p.getName;
	onUpdate = p.onUpdate;
	onLoad = p.onLoad;
	IsCoppy = true;
	ModConstBool(&p.isOld, 1);
}