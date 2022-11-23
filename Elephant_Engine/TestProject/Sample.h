#pragma once
#include "EngineCore.h"

class Sample : public EngineCore
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};
