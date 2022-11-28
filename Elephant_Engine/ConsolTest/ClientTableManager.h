#pragma once
#include "Singleton.h"
#include "TableManager.h"

class ClientTableManager : public Singleton<ClientTableManager>
{
private:
	// TODO : LoadComplete에서 변환하여 저장 할 컨테이너 기입 및 사용하기

public:
	virtual void Init();

private:
	virtual void LoadComplete();
};
