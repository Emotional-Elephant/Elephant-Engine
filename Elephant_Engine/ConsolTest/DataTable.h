#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Singleton.h"

template <typename K, typename V>
class DataTable : public Singleton<DataTable<K, V>>
{
private:
	std::map<K, std::shared_ptr<V>> rows_;

public:
	bool Init(const std::string& sourcePath);
	bool ContainKey(K key);
	std::weak_ptr<V> GetData(K key);
	std::vector<std::weak_ptr<V>> GetData(
		std::function<bool(std::shared_ptr<V>)> match);
};

#include "DataTable.hpp"
