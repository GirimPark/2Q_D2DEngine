#pragma once

#include <Xinput.h>
#include <vector>

enum class eKeyState
{
	NONE,
	PUSH,
	HOLD,
	END
};

enum eKeyCode
{
	LBUTTON = VK_LBUTTON, // 왼쪽 마우스 버튼
	RBUTTON = VK_RBUTTON, // 오른쪽 마우스 버튼
	CANCEL = VK_CANCEL,   // 취소 키
	MBUTTON = VK_MBUTTON, // 가운데 마우스 버튼

	BACK = VK_BACK,       // 백스페이스 키
	TAB = VK_TAB,		  // 탭 키
	CLEAR = VK_CLEAR,	  // CLEAR 키
	RETURN = VK_RETURN,	  // 엔터 키

	SHIFT = VK_SHIFT,     // Shift 키
	CONTROL = VK_CONTROL, // Ctrl 키
	ALT = VK_MENU,		  // Alt 키
	PAUSE = VK_PAUSE,	  // Pause 키

	ESCAPE = VK_ESCAPE,   // Esc 키

	SPACE = VK_SPACE,     // 스페이스바 키
	LEFT = VK_LEFT,		  // 왼쪽 화살표 키
	UP = VK_UP,			  // 위쪽 화살표 키
	RIGHT = VK_RIGHT,	  // 오른쪽 화살표 키
	DOWN = VK_DOWN,		  // 아래쪽 화살표 키

	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
};

struct KeyInfo
{
	bool prevPushed;
	eKeyState keyState;
};

enum class GamePadButtonCode
{
	A = 0,
	B,
	X,
	Y,

	UP,
	DOWN,
	LEFT,
	RIGHT,

	START,
	BACK,

	L3,
	R3,

	L1,
	R1,

	XINPUT_BUTTON_COUNT
};

struct GamePadButtonInfo
{
	bool prevPushed;
	eKeyState padState;
};

class InputManager
{
public:
	InputManager();

public:
	static InputManager* GetInstance()
	{
		if (m_pInputInstance == nullptr)
			m_pInputInstance = new InputManager;

		return m_pInputInstance;
	}

	void Initialize();
	void Update();
	void Finalize();

public:
	inline bool IsKeyNone(eKeyCode keyCode) const;
	inline bool IsKeyPush(eKeyCode keyCode) const;
	inline bool IsKeyHold(eKeyCode keyCode) const;
	inline bool IsKeyEnd(eKeyCode keyCode) const;

	inline const POINT& GetMousePos() const;

public:
	float GetAxisRaw(const std::string& axis) const;

public:
	static framework::Vector2D GetPadAxisLeftThumb(DWORD controllerIndex);
	static framework::Vector2D GetPadAxisRightThumb(DWORD controllerIndex);
	static float GetPadAxisLeftTrigger(DWORD controllerIndex);
	static float GetPadAxisRightTrigger(DWORD controllerIndex);

private:
	static InputManager* m_pInputInstance;
	KeyInfo m_KeyState[256];
	POINT m_mousePos;

private:
	std::vector<int> m_PadButtonList;
	GamePadButtonInfo m_PadState[4][static_cast<int>(GamePadButtonCode::XINPUT_BUTTON_COUNT)];

	/// <summary>
	/// XBOX XBOXController Function
	/// </summary>
public:
	inline bool IsPadButtonNone(DWORD controllerIndex, GamePadButtonCode buttonCode) const;
	inline bool IsPadButtonPush(DWORD controllerIndex, GamePadButtonCode buttonCode) const;
	inline bool IsPadButtonHold(DWORD controllerIndex, GamePadButtonCode buttonCode) const;
	inline bool IsPadButtonEnd(DWORD controllerIndex, GamePadButtonCode buttonCode) const;

	// 컨트롤러 버튼 상태
	static XINPUT_STATE GetControllerState(DWORD controllerIndex)
	{
		XINPUT_STATE controllerState;
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		// 해당 인덱스의 컨트롤러의 상태 가져오기
		XInputGetState(controllerIndex, &controllerState);
		return controllerState;
	}

	// 컨트롤러 진동 기능
	static XINPUT_VIBRATION SetControllerVib(DWORD controllerIndex, WORD leftMotorSpeed, WORD rightMotorSpeed)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		// 최대값은 65535
		vibration.wLeftMotorSpeed = leftMotorSpeed;  // 왼쪽 모터의 진동 속도
		vibration.wRightMotorSpeed = rightMotorSpeed; // 오른쪽 모터의 진동 속도

		// 해당 인덱스의 컨트롤러에 진동을 적용
		XInputSetState(controllerIndex, &vibration);
		return vibration;
	}

	// 연결되어있는 컨트롤러의 개수 가져오기
	static DWORD GetMaxControllerCount()
	{
		DWORD count = 0;
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE controllerState;
			ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
			if (XInputGetState(i, &controllerState) == ERROR_SUCCESS)
				count++;
		}
		return count;
	}
};

bool InputManager::IsKeyNone(eKeyCode keyCode) const
{
	return m_KeyState[keyCode].keyState == eKeyState::NONE;
}

bool InputManager::IsKeyPush(eKeyCode keyCode) const
{
	return m_KeyState[keyCode].keyState == eKeyState::PUSH;
}

bool InputManager::IsKeyHold(eKeyCode keyCode) const
{
	return m_KeyState[keyCode].keyState == eKeyState::HOLD;
}

bool InputManager::IsKeyEnd(eKeyCode keyCode) const
{
	return m_KeyState[keyCode].keyState == eKeyState::END;
}

bool InputManager::IsPadButtonNone(DWORD controllerIndex, GamePadButtonCode buttonCode) const
{
	return m_PadState[controllerIndex][static_cast<int>(buttonCode)].padState == eKeyState::NONE;
}

bool InputManager::IsPadButtonPush(DWORD controllerIndex, GamePadButtonCode buttonCode) const
{
	return m_PadState[controllerIndex][static_cast<int>(buttonCode)].padState == eKeyState::PUSH;
}

bool InputManager::IsPadButtonHold(DWORD controllerIndex, GamePadButtonCode buttonCode) const
{
	return m_PadState[controllerIndex][static_cast<int>(buttonCode)].padState == eKeyState::HOLD;
}

bool InputManager::IsPadButtonEnd(DWORD controllerIndex, GamePadButtonCode buttonCode) const
{
	return m_PadState[controllerIndex][static_cast<int>(buttonCode)].padState == eKeyState::END;
}

const POINT& InputManager::GetMousePos() const
{
	return m_mousePos;
}