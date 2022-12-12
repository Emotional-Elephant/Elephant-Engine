#include <memory>

#include "TableManager.h"
#include "Config.h"
#include "DataTable.h"
#include "TableManager.h"
#include "DataTableInterface.h"

void TableManager::set_complete_callback(std::function<void()> callback)
{
	complete_callback_ = callback;
}

void TableManager::Add(DataTableInterface* data_table)
{
	table_list_.push_back(data_table);
}

void TableManager::LoadAll()
{
	std::string local_path = Config::GetInstance().local_path_;
	for (auto& data_table : table_list_)
	{
		data_table->Init(local_path + "/" + data_table->name() + ".csv");
	}
}

void TableManager::Init()
{
	LoadAll();
	if (complete_callback_ != nullptr)
	{
		complete_callback_();
	}
}