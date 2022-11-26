#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

std::tm StringTotm(const std::string& str, std::string format = { "%Y-%m-%d %H:%M:%s" });

std::vector<std::string> Split(const std::string& str, char delimiter);

std::string Tolower(const std::string& str);

template <typename T>
T Lexical_cast(const std::string& str)
{
	std::istringstream iss;
	T var;
	iss.str(str);
	iss >> var;
	return var;
}

bool Lexical_cast_boolean(const std::string& str);