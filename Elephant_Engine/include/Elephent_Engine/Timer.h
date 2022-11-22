#pragma once
#include "Singleton.h"
#include <string>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
class Timer : public Singleton<Timer>
{
	friend class Singleton<Timer>;
private:
	LARGE_INTEGER	frequency_;
	LARGE_INTEGER	current_;
	LARGE_INTEGER	before_;
private:
	float			total_play_time_ = 0.0f;
	float			frame_interval_ = 10.0f;
	UINT			fps_ = 0;
private:
	UINT			fps_counter_ = 0;
	float			fps_timer_ = 0.0f;
public:
	std::wstring	timer_info_;
public:
	float		 GetTotalPlayTime() { return total_play_time_; };
	float		 GetFrameInterval() { return frame_interval_; };
	UINT		 GetFPS() { return fps_; };
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
private:
	Timer() {};
	~Timer() = default;
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
};

#define I_Timer Timer::GetInstance()