#include <memory>

#include "ClientTableManager.h"
#include "DataTable.h"
#include "TableManager.h"
#include "TestData.h"

void ClientTableManager::Init()
{
	TableManager::GetInstance().set_complete_callback(std::bind(&ClientTableManager::LoadComplete, this));
	TableManager::GetInstance().Init();
}

void ClientTableManager::LoadComplete()
{
	//Table Load �Ϸ� �� �۾� �� ���� ���� �׽�Ʈ �ڵ�
	std::vector<std::weak_ptr<TestData>> returnValue;
	returnValue = DataTable<int, TestData>::GetInstance().GetData([](std::shared_ptr<TestData> value)
		{
			if (value->test1 == true)
			{
				return true;
			}
			return false;
		});
}