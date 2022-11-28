#pragma once
#include <unordered_map>
#include <vector>
#include <functional>

#include "Singleton.h"

class DataTableInterface;
class TableManager : public Singleton<TableManager>
{
private:
	std::vector<DataTableInterface*> table_list_;
	std::function<void()> complete_callback_ = nullptr;

public:
	void Add(DataTableInterface* table);
	void set_complete_callback(std::function<void()> callback);
	void Init();

private:
	void LoadAll();
};
