#pragma once
#include "Singleton.h"
#include "TableManager.h"

class ClientTableManager : public Singleton<ClientTableManager>
{
private:
	// TODO : LoadComplete���� ��ȯ�Ͽ� ���� �� �����̳� ���� �� ����ϱ�

public:
	virtual void Init();

private:
	virtual void LoadComplete();
};
