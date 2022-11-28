#include <memory>

#include "Config.h"
#include "DataTable.h"
#include "TableManager.h"
#include "DataTableInterface.h"

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