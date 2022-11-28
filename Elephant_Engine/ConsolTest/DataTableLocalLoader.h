#pragma once
#include <map>
#include <string>
#include <memory>

template <typename K, typename V>
class DataTableLocalLoader
{
public:
	static std::map<K, std::shared_ptr<V>> Run(const std::string& path);
};

#include "DataTableLocalLoader.hpp"