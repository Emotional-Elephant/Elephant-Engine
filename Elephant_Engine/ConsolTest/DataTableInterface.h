#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

class DataTableInterface abstract
{
public:
	virtual void set_name(const std::string& name) = 0;
	virtual std::string name() = 0;
	virtual bool Init(const std::string& sourcePath) = 0;
};
