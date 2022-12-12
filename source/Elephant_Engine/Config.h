#pragma once
#include <filesystem>
#include <string>

#include "Singleton.h"

class Config : public Singleton<Config>
{
private:
	std::string local_path_

public:
	std::string shader_path_;

public:
	Config() : local_path_{ std::filesystem::current_path().generic_string() } {}
};
