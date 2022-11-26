#include "DataTable.h"
#include "TestData.h"

int main()
{
	TestData a;
	DataTable<int, TestData>::GetInstance().Init("TestData.csv");
	return 0;
}