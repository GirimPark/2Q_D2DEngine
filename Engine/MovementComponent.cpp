#include "pch.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SceneComponent.h"

framework::Vector2D thumbLeft = { 0.f, 0.f };
framework::Vector2D thumbRight = { 0.f, 0.f };

int rawBX = 0;
int rawBY = 0;

float triggerL = 0.f;
float triggerR = 0.f;

int ConvertToRaw(float& thumbValue)
{
	constexpr float threshold = 0.2f; // 임계값을 설정

	if (thumbValue > threshold) return 1;
	if (thumbValue < -threshold) return -1;

	return 0;
}

/// <summary>
/// 컨트롤러 기능 테스트
/// </summary>
/// <param name="controllerIndex"></param>
void MovementComponent::XBOXController(int controllerIndex)
{
	/// A B X Y
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::A))
		std::cout << std::to_string(controllerIndex + 1) << "P의 A 버튼 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::A))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 A 버튼 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::A))
		std::cout << std::to_string(controllerIndex + 1) << "P의 A 버튼 END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::B))
		std::cout << std::to_string(controllerIndex + 1) << "P의 B 버튼 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::B))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 B 버튼 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::B))
		std::cout << std::to_string(controllerIndex + 1) << "P의 B 버튼 END" << std::endl;

	/// L1 R1
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::L1))
		std::cout << std::to_string(controllerIndex + 1) << "P의 L1 버튼 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::L1))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 L1 버튼 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::L1))
	{
		std::cout << std::to_string(controllerIndex + 1) << "P의 L1 버튼 END" << std::endl;
		InputManager::SetControllerVib(controllerIndex, 0, 0);
	}

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::R1))
		std::cout << std::to_string(controllerIndex + 1) << "P의 R1 버튼 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::R1))
		// std::cout << std::to_string(controllerIndex + 1) <<"P의 R1 버튼 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::R1))
	{
		std::cout << std::to_string(controllerIndex + 1) << "P의 R1 버튼 END" << std::endl;
		InputManager::SetControllerVib(controllerIndex, 0, 0);
	}

	/// L3 R3
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::L3))
		std::cout << std::to_string(controllerIndex + 1) << "P의 L3 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::L3))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 L3 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::L3))
		std::cout << std::to_string(controllerIndex + 1) << "P의 L3 END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::R3))
		std::cout << std::to_string(controllerIndex + 1) << "P의 R3 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::R3))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 R3 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::R3))
		std::cout << std::to_string(controllerIndex + 1) << "P의 R3 END" << std::endl;

	/// START BACK
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::START))
		std::cout << std::to_string(controllerIndex + 1) << "P의 START PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::START))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 START HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::START))
		std::cout << std::to_string(controllerIndex + 1) << "P의 START END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::BACK))
		std::cout << std::to_string(controllerIndex + 1) << "P의 BACK PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::BACK))
		// std::cout << std::to_string(controllerIndex + 1) << "P의 BACK HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::BACK))
		std::cout << std::to_string(controllerIndex + 1) << "P의 BACK END" << std::endl;

	/// 왼쪽 / 오른쪽 스틱
	thumbLeft = InputManager::GetPadAxisLeftThumb(controllerIndex);
	thumbRight = InputManager::GetPadAxisRightThumb(controllerIndex);

	/// 이동 버튼
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::UP) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::UP))
		rawBY = -1;
	else if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::DOWN) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::DOWN))
		rawBY = 1;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::LEFT) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::LEFT))
		rawBX = -1;
	else if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::RIGHT) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::RIGHT))
		rawBX = 1;

	/// L2 R2
	triggerL = InputManager::GetPadAxisLeftTrigger(controllerIndex);
	triggerR = InputManager::GetPadAxisRightTrigger(controllerIndex);

	if (triggerL > 0.2f || triggerR > 0.2f)
	{
		InputManager::SetControllerVib(controllerIndex, static_cast<WORD>(triggerL * 65535),
			static_cast<WORD>(triggerR * 65535));
	}
}

void MovementComponent::Update(const float deltaTime)
{
	m_MoveDir = { 0.f, 0.f };

	// 1P ~ 4P까지의 컨트롤러 입력을 받아온다
	if (m_pOwner->GetName() == L"PlayerObject1")
		XBOXController(0);
	else if (m_pOwner->GetName() == L"PlayerObject2")
		XBOXController(1);
	else if (m_pOwner->GetName() == L"PlayerObject3")
		XBOXController(2);
	else if (m_pOwner->GetName() == L"PlayerObject4")
		XBOXController(3);

	/// Move Direction 설정

	// 왼쪽 스틱의 입력값
	float rawLX = max(-1, thumbLeft.x);
	float rawLY = max(-1, (-1) * thumbLeft.y);	// 값이 -1보다 작아지는 경우 -1을 값으로 한다

	// 왼쪽 버튼으로 이동하는 경우
	if (rawBX != 0 || rawBY != 0)
		m_MoveDir = { rawBX, rawBY };	// 왼쪽 버튼을 이용한 이동
	else
		m_MoveDir = { rawLX, rawLY };	// 스틱을 이용한 이동

	// 이동 방향의 단위 벡터를 구한다
	m_MoveDir.Normalize();

	/// Look Direction 설정

	// 오른쪽 스틱의 입력값
	float rawRX = max(-1, thumbRight.x);
	float rawRY = max(-1, (-1) * thumbRight.y);	// 값이 -1보다 작아지는 경우 -1을 값으로 한다

	// 오른쪽 스틱에 입력값이 있는 경우에만 방향을 바꿔준다
	 if(rawRX != 0.f || rawRY != 0.f)
	 	m_LookDir = { rawRX, rawRY };

	// 이동 방향의 단위 벡터를 구한다
	m_LookDir.Normalize();

	// 플레이어 이동
	m_pOwner->GetRootComponent()->AddRelativeLocation(m_MoveDir * m_Velocity * deltaTime);
}