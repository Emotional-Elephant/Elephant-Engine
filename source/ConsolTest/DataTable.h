#pragma once
#include <string>
#include <functional>
#include <map>

#include "DataTableInterface.h"
#include "TableDataInterface.h"
#include "Singleton.h"

template <typename K, typename V>
class DataTable : public Singleton<DataTable<K, V>>, public DataTableInterface
{
private:
	std::string name_;
	std::map<K, std::shared_ptr<V>> rows_;

public:
	virtual void set_name(const std::string& name);
	virtual std::string name();
	virtual bool Init(const std::string& source_path);
	bool ContainKey(K key);
	std::weak_ptr<V> GetData(K key);
	std::vector<std::weak_ptr<V>> GetData(std::function<bool(std::shared_ptr<V>)> match);
};

#include "DataTable.hpp"
