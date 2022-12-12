#include <string>

#include "DataTable.h"
#include "DataTableLocalLoader.h"

template<typename K, typename V>
void DataTable<K, V>::set_name(const std::string& name)
{
	name_ = name;
}

template<typename K, typename V>
std::string DataTable<K, V>::name()
{
	return name_;
}

template <typename K, typename V>
bool DataTable<K, V>::Init(const std::string& sourcePath)
{
	rows_ = DataTableLocalLoader<K, V>::Run(sourcePath);
	return true;
}

template <typename K, typename V>
bool DataTable<K, V>::ContainKey(K key)
{
	if (rows_.contains(key) == false)
	{
		return false;
	}

	return true;
}

template <typename K, typename V>
std::weak_ptr<V> DataTable<K, V>::GetData(K key)
{
	auto iter = rows_.find(key);
	if (iter == rows_)
	{
		return nullptr;
	}
	return iter.second;
}

template <typename K, typename V>
std::vector<std::weak_ptr<V>> DataTable<K, V>::GetData(
	std::function<bool(std::shared_ptr<V>)> match)
{
	std::vector<std::weak_ptr<V>> result;
	for (auto& data : rows_)
	{
		if (match(data.second))
		{
			result.push_back(data.second);
		}
	}
	return result;
}