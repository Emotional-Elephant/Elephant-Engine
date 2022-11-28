#include "DataTable.h"
#include "TestData.h"
#include "ClientTableManager.h"

int main()
{
	ClientTableManager::GetInstance().Init();
	return 0;
}