#pragma once
#include "stdafx.h"
#include "Renderable.h"

class TestBox : public Renderable
{
public:
	TestBox() :Renderable() {};
protected:
	virtual void		InitData() override;
	virtual void		SetVertexData() override;
	virtual void		SetIndexData() override;
};

