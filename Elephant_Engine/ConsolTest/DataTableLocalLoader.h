#pragma once
#include <map>
#include <string>

template <typename K, typename V>
class DataTableLocalLoader
{
public:
	static std::map<K, V> Run(const std::string& path);
};

#include "DataTableLocalLoader.hpp"