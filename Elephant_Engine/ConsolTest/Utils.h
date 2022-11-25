#pragma once
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>

template <typename T>
T Lexical_cast(const std::string& str)
{
	static std::istringstream iss;
	T var;
	iss.str(str);
	iss >> var;
	return var;
}

std::tm StringTotm(const std::string& str, std::string format = { "%Y-%m-%d %H:%M:%s" })
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