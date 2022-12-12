#include "DebugCamera.h"
#include "Timer.h"
#include "Input.h"

bool DebugCamera::SetValues()
{
	target_ = { 0, 0, 0 };
	position_ = target_;
	position_.z += 50.0f;
	near_plane_dist_ = 1.0f;
	far_plane_dist_ = 1000.0f;
	field_of_view_ = 3.141592f * 0.25f;
	aspect_ = (float)Window::GetInstance().GetRTClient().right / (float)Window::GetInstance().GetRTClient().bottom;
    return true;
}

bool DebugCamera::Frame()
{
	TVector3 pos_movement = { 0,0,0 };
	if (Input::GetInstance().GetKey('W') == KEY_HOLD)
	{
		pos_movement.z += 30.0f * Timer::GetInstance().GetFrameInterval();
	}
	if (Input::GetInstance().GetKey('S') == KEY_HOLD)
	{
		pos_movement.z -= 30.0f * Timer::GetInstance().GetFrameInterval();
	}
	if (Input::GetInstance().GetKey('A') == KEY_HOLD)
	{
		pos_movement.x -= 30.0f * Timer::GetInstance().GetFrameInterval();
	}
	if (Input::GetInstance().GetKey('D') == KEY_HOLD)
	{
		pos_movement.x += 30.0f * Timer::GetInstance().GetFrameInterval();
	}
	if (Input::GetInstance().GetKey('Q') == KEY_HOLD)
	{
		pos_movement.y -= 30.0f * Timer::GetInstance().GetFrameInterval();
	}
	if (Input::GetInstance().GetKey('E') == KEY_HOLD)
	{
		pos_movement.y += 30.0f * Timer::GetInstance().GetFrameInterval();
	}

	if (Input::GetInstance().GetKey(VK_SPACE) == KEY_HOLD) {
		pos_movement *= 50.0f;
	}
	position_ += pos_movement;
	target_ = position_;
	target_.z -= 50.0f;
    return true;
}
