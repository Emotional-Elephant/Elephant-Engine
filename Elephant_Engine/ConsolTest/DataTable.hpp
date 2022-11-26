#include "DataTable.h"
#include "DataTableLocalLoader.h"
#include <string>

template <typename K, typename V>
bool DataTable<K, V>::Init(const std::string& sourcePath)
{
	rows_ = DataTableLocalLoader<K, V>::Run(sourcePath);
	return true;
}