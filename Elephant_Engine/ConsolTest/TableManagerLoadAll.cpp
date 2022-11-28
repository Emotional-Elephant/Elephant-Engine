#include "TableManager.h"
#include "Config.h"
#include "DataTable.h"
#include "TestData.h"
#include <memory>


void TableManager::LoadAll()
{
	std::string local_path = Config::GetInstance().local_path_;
	DataTable<int, TestData>::GetInstance().Init(local_path + "/TestData.csv");
}