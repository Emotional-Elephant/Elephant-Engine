#include "Timer.h"

bool Timer::Init()
{
    total_play_time_ = 0.0f;
    frame_interval_ = 10.0f;
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&before_);
    return true;
}

bool Timer::Frame()
{
    QueryPerformanceCounter(&current_);
    frame_interval_ = (float)(current_.QuadPart - before_.QuadPart) /
        (float)frequency_.QuadPart;
    total_play_time_ += frame_interval_;

    {
        fps_counter_++;
        fps_timer_ += frame_interval_;
        if (fps_timer_ >= 1.0f) {
            fps_ = fps_counter_;
            fps_counter_ = 0;
            fps_timer_ = fps_timer_ - 1.0f;
        }
    }

    before_ = current_;
    return true;
}

bool Timer::Render()
{
#ifdef _DEBUG
    timer_info_ = std::to_wstring(total_play_time_);
    timer_info_ += L"   ";
    timer_info_ += std::to_wstring(fps_);
    timer_info_ += L"\n";
#endif
    return false;
}

bool Timer::Release()
{
    return false;
}
