#pragma once
#include"stdafx.h"
#include"Renderable.h"

class RenderManager : public Singleton<RenderManager>
{
	friend class Singleton<RenderManager>;
	friend class Renderable;
private:
	std::vector<std::shared_ptr<Renderable*>> render_list_;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
private:
	RenderManager() {};
	~RenderManager() = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
};

