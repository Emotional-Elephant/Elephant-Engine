#pragma once
#include"Camera.h"
#include"stdafx.h"

class DebugCamera : public Camera
{
private:
	virtual bool SetValues() override;
public:
	virtual bool Frame() override;
};

