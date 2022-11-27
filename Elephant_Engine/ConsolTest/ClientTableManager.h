#pragma once
#include "TableManager.h"
#include "Singleton.h"

class ClientTableManager : public TableManager, public Singleton<ClientTableManager>
{
protected:
	virtual void LoadComplete
};
