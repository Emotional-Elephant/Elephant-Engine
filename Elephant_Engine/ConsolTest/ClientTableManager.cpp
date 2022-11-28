#include "ClientTableManager.h"
#include "DataTable.h"
#include "TestData.h"
#include <memory>


void ClientTableManager::LoadComplete()
{
	//Table Load �Ϸ� �� �۾� �� ���� ����
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