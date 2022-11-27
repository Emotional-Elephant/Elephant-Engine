#pragma once
#include <string>
#include <filesystem>

#include "Singleton.h"

class Config : public Singleton<Config>
{
public:
	std::string local_path_;

public:
	Config() : local_path_{ std::filesystem::current_path().generic_string() }
	{}
};
