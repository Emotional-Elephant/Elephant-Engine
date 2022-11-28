#include "TableManager.h"

void TableManager::set_complete_callback(std::function<void()> callback)
{
	complete_callback_ = callback;
}

void TableManager::Init()
{
	LoadAll();
	if (complete_callback_ != nullptr)
	{
		complete_callback_();
	}
}