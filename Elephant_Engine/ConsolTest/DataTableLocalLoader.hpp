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
	std::map<K, V> data_container;
	std::string line;
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		throw std::invalid_argument(path);
	}

	std::vector<std::string> fields;
	std::vector<int> except_index;
	int row = 0;
	while (std::getline(ifs, line))
	{
		std::vector<std::string> cols;
		cols = Split(line, ',');
		if (row == 0)
		{
			for (int i = 0; i < cols.size(); ++i)
			{
				if (cols.at(i).at(0) == '~')
				{
					except_index.push_back(i);
				}
				else
				{
					fields.push_back(cols[i]);
				}
			}
		}

		if (row++ < 2)
		{
			continue;
		}

		for (auto index : except_index)
		{
			cols.erase(cols.begin() + index);
		}

		std::unordered_map<std::string, std::string> col_values;
		for (int i = 0; i < fields.size(); ++i)
		{
			col_values.emplace(fields[i], cols[i]);
		}

		V data;
		data.Serialize(col_values);

		K key = Lexical_cast<K>(cols[0]);
		if (data_container.contains(key) == true)
		{
			throw new std::exception("invalid key value");
		}

		data_container.emplace(key, data);
	}

	return data_container;
}
