#include "Input.h"
#include "Window.h"

bool Input::Init()
{
    ZeroMemory(key_state_, sizeof(DWORD) * 256);
    return true;
}

bool Input::Frame()
{
    ::GetCursorPos(&mouse_pos_);
    ::ScreenToClient(I_Window.GetHWindow(), &mouse_pos_);

    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey);
        if (sKey & 0x8000)
        {
            if (key_state_[iKey] == KEY_FREE ||
                key_state_[iKey] == KEY_UP)
                key_state_[iKey] = KEY_PUSH;
            else
                key_state_[iKey] = KEY_HOLD;
        }
        else
        {
            if (key_state_[iKey] == KEY_PUSH ||
                key_state_[iKey] == KEY_HOLD)
                key_state_[iKey] = KEY_UP;
            else
                key_state_[iKey] = KEY_FREE;
        }
    }

    return true;
}

bool Input::Render()
{
#ifdef _DEBUG

#endif
    return true;
}

bool Input::Release()
{
    return true;
}

DWORD Input::GetKey(DWORD key)
{
    return key_state_[key];
}
