#include "TestData.h"
#include "TableManager.h"
#include "DataTable.h"
#include "Utils.h"

TestData::init_ TestData::_initializer;

TestData::init_::init_()
{
	DataTable<int, TestData>::GetInstance().set_name("TestData");
	TableManager::GetInstance().Add(&DataTable<int, TestData>::GetInstance());
}

void TestData::Serialize(std::unordered_map<std::string, std::string>& data)
{
	auto iter = data.find("id");
	if (iter != data.end())
	{
		id = Lexical_cast<int>(iter->second);
	}
	iter = data.find("test1");
	if (iter != data.end())
	{
		test1 = Lexical_cast_boolean(iter->second);
	}
	iter = data.find("test2");
	if (iter != data.end())
	{
		test2 = Lexical_cast<short>(iter->second);
	}
	iter = data.find("test3");
	if (iter != data.end())
	{
		test3 = Lexical_cast<unsigned short>(iter->second);
	}
	iter = data.find("test4");
	if (iter != data.end())
	{
		test4 = Lexical_cast<int>(iter->second);
	}
	iter = data.find("test5");
	if (iter != data.end())
	{
		test5 = Lexical_cast<unsigned int>(iter->second);
	}
	iter = data.find("test6");
	if (iter != data.end())
	{
		test6 = Lexical_cast<float>(iter->second);
	}
	iter = data.find("test7");
	if (iter != data.end())
	{
		test7 = Lexical_cast<double>(iter->second);
	}
	iter = data.find("test8");
	if (iter != data.end())
	{
		test8 = StringTotm(iter->second);
	}
	iter = data.find("test9");
	if (iter != data.end())
	{
		test9 = Lexical_cast<char>(iter->second);
	}
	iter = data.find("test10");
	if (iter != data.end())
	{
		test10 = Lexical_cast<unsigned char>(iter->second);
	}
	iter = data.find("test11");
	if (iter != data.end())
	{
		test11 = iter->second;
	}
	iter = data.find("test12");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test12.push_back(Lexical_cast_boolean(data));
		}
	}
	iter = data.find("test13");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test13.push_back(Lexical_cast<short>(data));
		}
	}
	iter = data.find("test14");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test14.push_back(Lexical_cast<unsigned short>(data));
		}
	}
	iter = data.find("test15");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test15.push_back(Lexical_cast<int>(data));
		}
	}
	iter = data.find("test16");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test16.push_back(Lexical_cast<unsigned int>(data));
		}
	}
	iter = data.find("test17");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test17.push_back(Lexical_cast<float>(data));
		}
	}
	iter = data.find("test18");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test18.push_back(Lexical_cast<double>(data));
		}
	}
	iter = data.find("test19");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test19.push_back(StringTotm(data));
		}
	}
	iter = data.find("test20");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test20.push_back(Lexical_cast<char>(data));
		}
	}
	iter = data.find("test21");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test21.push_back(Lexical_cast<unsigned char>(data));
		}
	}
	iter = data.find("test22");
	if (iter != data.end())
	{
		std::vector<std::string> result = Split(iter->second, '|');
		for (auto& data : result)
		{
			test22.push_back(data);
		}
	}
}
