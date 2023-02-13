#include"Plugin.h"
#include<iostream>

const char* plugin::getName()
{
	return "NAME";
}

void plugin::onLoad()
{
	std::cout << "onLoad";
}

void plugin::onUpdate(float deltaTime)
{
	std::cout << "Delta" << deltaTime;
}