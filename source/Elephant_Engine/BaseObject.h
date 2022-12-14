#pragma once
#include <string>
#include <memory>

class BaseObject abstract
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

public:
	//Active 될 때
	virtual void OnEnable() abstract;
	//DeActive 될 때
	virtual void OnDisable() abstract;

public:
	//생성자 이 후 호출 해야할 것들 정의
	virtual void Construct() abstract;
	//파괴자 호출에서 해야할 것들 정의
	virtual void Destruct() abstract;
};

