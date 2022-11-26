#include "Utils.h"

std::tm StringTotm(const std::string& str, std::string format)
{
	static std::istringstream iss;
	std::tm tm;
	memset(&tm, 0, sizeof(std::tm));
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

std::string Tolower(const std::string& str)
{
	std::string result;

	for (auto& word : str)
	{
		result += std::tolower(word);
	}

	return result;
}

bool Lexical_cast_boolean(const std::string& str)
{
	std::istringstream iss;
	bool var;
	iss.str(Tolower(str));
	iss >> std::boolalpha >> var;
	return var;
}