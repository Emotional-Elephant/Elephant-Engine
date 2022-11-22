#pragma once
#pragma once
#include <windows.h>
#include <string>
#include "Singleton.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
private:
	DWORD		key_state_[256];
	POINT		mouse_pos_;
public:
	POINT				GetMousePos() { return mouse_pos_; };
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
public:
	DWORD  GetKey(DWORD key);
private:
	Input() {};
	~Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
};
#define I_Input Input::GetInstance()
