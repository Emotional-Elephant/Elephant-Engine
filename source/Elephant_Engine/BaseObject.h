#pragma once
#include <string>
#include <memory>

class BaseObject abstract
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

