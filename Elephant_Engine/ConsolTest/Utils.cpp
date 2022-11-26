#include "Utils.h"

std::tm StringTotm(const std::string& str, std::string format)
{
	static std::istringstream iss;
	std::tm tm;
	iss.str(str);
	iss >> std::get_time(&tm, format.c_str());
	return tm;
}

std::vector<std::string> Split(const std::string& str, char delimiter)
{
	std::vector<std::string>  result;
	std::stringstream ss(str);
	std::string temp;

	while (std::getline(ss, temp, delimiter))
	{
		result.push_back(temp);
	}

	return result;
}