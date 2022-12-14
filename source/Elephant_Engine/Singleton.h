#pragma once
#include "Component.h"

template<class T> 
class Singleton : public Component
{
public:
	static T& GetInstance()
	{
		static T theSingleInstance;
		return theSingleInstance;
	}
};