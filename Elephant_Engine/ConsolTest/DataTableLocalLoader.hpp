#include "DataTableLocalLoader.h"
#include "Utils.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

template <typename K, typename V>
std::map<K, V> DataTableLocalLoader<K, V>::Run(const std::string& path)
{
	std::map<K, V> dataContainer;
	std::string line;
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		throw std::invalid_argument(path);
	}

	std::vector<std::string> fields;
	std::vector<int> exceptIndex;
	int row = 0;
	while (ifs.getline(line))
	{
		std::vector<std::string> cols;
		cols = Split(line, ',');
		if (row == 0)
		{
			for (int i = 0; i < cols.size(); ++i)
			{
				if (cols.at(i).at(0) == '~')
				{
					exceptIndex.push_back(i);
				}
				else
				{
					fields.push_back(i);
				}
			}
		}

		if (row++ < 2)
		{
			continue;
		}

		for (auto index : exceptIndex)
		{
			cols.erase(index);
		}

		std::unordered_map<std::string, std::string> colValues;
		for (int i = 0; i < fields.size(); ++i)
		{
			colValues.emplace({ fields[i], cols[i] });
		}

		V data;
		data.Serialize(colValues);

		K key = Lexical_cast<K>(cols[0]);
		if (dataContainer.contains(key) == true)
		{
			throw new std::exception("invalid key value");
		}

		dataContainer.emplace({ key, data });
	}
}
