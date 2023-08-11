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
	LBUTTON = VK_LBUTTON, // ���� ���콺 ��ư
	RBUTTON = VK_RBUTTON, // ������ ���콺 ��ư
	CANCEL = VK_CANCEL,   // ��� Ű
	MBUTTON = VK_MBUTTON, // ��� ���콺 ��ư

	BACK = VK_BACK,       // �齺���̽� Ű
	TAB = VK_TAB,		  // �� Ű
	CLEAR = VK_CLEAR,	  // CLEAR Ű
	RETURN = VK_RETURN,	  // ���� Ű

	SHIFT = VK_SHIFT,     // Shift Ű
	CONTROL = VK_CONTROL, // Ctrl Ű
	ALT = VK_MENU,		  // Alt Ű
	PAUSE = VK_PAUSE,	  // Pause Ű

	ESCAPE = VK_ESCAPE,   // Esc Ű

	SPACE = VK_SPACE,     // �����̽��� Ű
	LEFT = VK_LEFT,		  // ���� ȭ��ǥ Ű
	UP = VK_UP,			  // ���� ȭ��ǥ Ű
	RIGHT = VK_RIGHT,	  // ������ ȭ��ǥ Ű
	DOWN = VK_DOWN,		  // �Ʒ��� ȭ��ǥ Ű

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

	// ��Ʈ�ѷ� ��ư ����
	static XINPUT_STATE GetControllerState(DWORD controllerIndex)
	{
		XINPUT_STATE controllerState;
		ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

		// �ش� �ε����� ��Ʈ�ѷ��� ���� ��������
		XInputGetState(controllerIndex, &controllerState);
		return controllerState;
	}

	// ��Ʈ�ѷ� ���� ���
	static XINPUT_VIBRATION SetControllerVib(DWORD controllerIndex, WORD leftMotorSpeed, WORD rightMotorSpeed)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		// �ִ밪�� 65535
		vibration.wLeftMotorSpeed = leftMotorSpeed;  // ���� ������ ���� �ӵ�
		vibration.wRightMotorSpeed = rightMotorSpeed; // ������ ������ ���� �ӵ�

		// �ش� �ε����� ��Ʈ�ѷ��� ������ ����
		XInputSetState(controllerIndex, &vibration);
		return vibration;
	}

	// ����Ǿ��ִ� ��Ʈ�ѷ��� ���� ��������
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