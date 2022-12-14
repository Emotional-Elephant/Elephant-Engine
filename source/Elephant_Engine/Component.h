#pragma once
#include <unordered_map>
#include <memory>

#include "BaseObject.h"

class Component : public BaseObject
{
private:
	static unsigned __int64 alloc_index_;

private:
	std::weak_ptr<Component> parent_;
	unsigned __int64 index_;
	std::unordered_map<unsigned __int64, std::shared_ptr<Component>> component_list_;
	Transform transform_;

public:
	std::weak_ptr<Component> parent() { return parent_; }
	unsigned __int64 index() const;
	Transform& transform();

	template<typename T>
	void CreateComponent()
	{
		std::shared_ptr<T> component;
		component = new T();


	}

private:
	Component() = default;
	virtual ~Component() = default;
};

