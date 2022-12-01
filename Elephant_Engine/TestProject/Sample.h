#pragma once
#include "stdafx.h"
#include "EngineCore.h"
#include "TestBox.h"
#include "DebugCamera.h"

struct SimpleVertex
{
	float p[3];
	float c[4];
	float t[2];
public:
	SimpleVertex() {};
};


class Sample : public EngineCore
{
	std::shared_ptr<DebugCamera> debug_camera_;
	std::shared_ptr<TestBox> test_box_;
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};
