#pragma once
#include "Singleton.h"
#include "TableManager.h"

class ClientTableManager : public TableManager,
	public Singleton<ClientTableManager>
{
private:
	// TODO : LoadComplete���� ��ȯ�Ͽ� ���� �� �����̳� ���� �� ����ϱ�

protected:
	virtual void LoadComplete() override;
};
