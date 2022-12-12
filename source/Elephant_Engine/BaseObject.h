#pragma once
#include <string>
#include <memory>

template <typename T>
class BaseObject abstract : std::enable_shared_from_this<T>
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

public:
	//Active �� ��
	virtual void OnEnable() abstract;
	//DeActive �� ��
	virtual void OnDisable() abstract;

public:
	//������ �� �� ȣ�� �ؾ��� �͵� ����
	virtual void Construct() abstract;
	//�ı��� ȣ�⿡�� �ؾ��� �͵� ����
	virtual void Destruct() abstract;
};

