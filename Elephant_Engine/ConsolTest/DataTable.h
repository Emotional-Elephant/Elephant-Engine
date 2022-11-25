#pragma once
#include "Singleton.h"
#include "DataTableLocalLoader.h"
#include <map>

template<typename T, typename V>
class DataTable : public Singleton<DataTable<T, V>>
{
private:
	std::map<T, V> rows_;

public:
	bool Init(const std::string& sourcePath)
	{
		rows_ = DataTableLocalLoader<T, V>.Run(sourcePath);
		return true;
	}
};

