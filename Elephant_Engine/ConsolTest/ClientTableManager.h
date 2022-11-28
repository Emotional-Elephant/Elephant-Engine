#pragma once
#include "Singleton.h"
#include "TableManager.h"

class ClientTableManager : public TableManager,
	public Singleton<ClientTableManager>
{
private:
	// TODO : LoadComplete에서 변환하여 저장 할 컨테이너 기입 및 사용하기

protected:
	virtual void LoadComplete() override;
};
