#include "ClientTableManager.h"

#include <memory>

#include "DataTable.h"
#include "TestData.h"

void ClientTableManager::LoadComplete()
{
	// Table Load �Ϸ� �� �۾� �� ���� ����
	std::vector<std::weak_ptr<TestData>> returnValue;
	returnValue = DataTable<int, TestData>::GetInstance().GetData(
		[](std::shared_ptr<TestData> value)
		{
			if (value->test1 == true)
			{
				return true;
			}
			return false;
		});
}