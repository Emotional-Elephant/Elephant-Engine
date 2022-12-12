#pragma once
#include <unordered_map>
#include <string>

class TableDataInterface abstract
{
public:
	virtual void Serialize(std::unordered_map<std::string, std::string>& data) = 0;
};
