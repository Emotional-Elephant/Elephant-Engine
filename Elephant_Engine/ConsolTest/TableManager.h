#pragma once
#include <unordered_map>

class TableManager
{
public:
	virtual void Init() final;
private:
	virtual void LoadAll() final;
	virtual void LoadComplete() = 0;
};


