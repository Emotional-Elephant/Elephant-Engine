#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

template <typename T>
T Lexical_cast(const std::string& str)
{
	static std::istringstream iss;
	T var;
	iss.str(str);
	iss >> var;
	return var;
}

std::tm StringTotm(const std::string& str, std::string format = { "%Y-%m-%d %H:%M:%s" });

std::vector<std::string> Split(const std::string& str, char delimiter);