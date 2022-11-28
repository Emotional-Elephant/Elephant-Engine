#include <memory>

#include "Config.h"
#include "DataTable.h"
#include "TableManager.h"
#include "TestData.h"

void TableManager::LoadAll()
{
	std::string local_path = Config::GetInstance().local_path_;
	DataTable<int, TestData>::GetInstance().Init(local_path + "/TestData.csv");
}