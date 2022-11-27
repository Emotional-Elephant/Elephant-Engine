#pragma once
#include <unordered_map>

class TableManager
{
public:
	void Init();
private:
	virtual void LoadAll() final;
	virtual void LoadComplete() = 0;
};


