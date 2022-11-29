#pragma once
#include <string>

class DataTableInterface abstract
{
public:
	virtual void set_name(const std::string& name) = 0;
	virtual std::string name() = 0;
	virtual bool Init(const std::string& sourcePath) = 0;
};
