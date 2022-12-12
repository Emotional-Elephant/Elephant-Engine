#include "ConstantData.h"
#include "TableManager.h"
#include "DataTable.h"
#include "Utils.h"

ConstantData::init_ ConstantData::_initializer;

ConstantData::init_::init_()
{
	DataTable<int, ConstantData>::GetInstance().set_name("ConstantData");
	TableManager::GetInstance().Add(&DataTable<int, ConstantData>::GetInstance());
}

void ConstantData::Serialize(std::unordered_map<std::string, std::string>& data)
{
	auto iter = data.find("id");
	if (iter != data.end())
	{
		id = Lexical_cast<int>(iter->second);
	}
	iter = data.find("test_int");
	if (iter != data.end())
	{
		test_int = Lexical_cast<int>(iter->second);
	}
	iter = data.find("test_string");
	if (iter != data.end())
	{
		test_string = iter->second;
	}
}
