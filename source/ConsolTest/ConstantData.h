#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

#include "TableDataInterface.h"

class ConstantData : public TableDataInterface
{
public:
	int id;
	int test_int;
	std::string test_string;

public:
	virtual void Serialize(std::unordered_map<std::string, std::string>& data);
	static class init_
	{
	public:
		init_();
	} _initializer;
};
