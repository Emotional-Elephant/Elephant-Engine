#pragma once
#include <unordered_map>
#include <memory>

#include "BaseObject.h"

class Component : public BaseObject<Component>
{
private:
	static unsigned __int64 alloc_index_;

private:
	Component* parent_ = nullptr;
	unsigned __int64 index_ = 0;
	std::unordered_map<unsigned __int64, std::shared_ptr<Component>> component_list_;

public:
	unsigned __int64 index() const;

private:
	Component() = default;
	virtual ~Component() = default;
};

