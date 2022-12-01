#include "RenderManager.h"

bool RenderManager::Init()
{
    return true;
}

bool RenderManager::Frame()
{
    return true;
}

bool RenderManager::Render()
{
    for (auto render_object : render_list_)
        (*render_object)->Render();
    return true;
}

bool RenderManager::Release()
{
    render_list_.clear();
    return true;
}
