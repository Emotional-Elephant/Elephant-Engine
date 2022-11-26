#pragma once
#include <unordered_map>

class ITableData abstract
{
public:
	virtual void Serialize(std::unordered_map<std::string, std::string>& data) = 0;
};
