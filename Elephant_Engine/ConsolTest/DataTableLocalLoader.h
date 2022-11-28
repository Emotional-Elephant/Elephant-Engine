#pragma once
#include <map>
#include <memory>
#include <string>

template <typename K, typename V>
class DataTableLocalLoader
{
public:
	static std::map<K, std::shared_ptr<V>> Run(const std::string& path);
};

#include "DataTableLocalLoader.hpp"