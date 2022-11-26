#pragma once
#include "Singleton.h"
#include <string>
#include <map>

template<typename K, typename V>
class DataTable : public Singleton<DataTable<K, V>>
{
private:
	std::map<K, V> rows_;

public:
	bool Init(const std::string& sourcePath);
};

#include "DataTable.hpp"

