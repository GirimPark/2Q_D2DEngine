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
	constexpr float threshold = 0.2f; // �Ӱ谪�� ����

	if (thumbValue > threshold) return 1;
	if (thumbValue < -threshold) return -1;

	return 0;
}

/// <summary>
/// ��Ʈ�ѷ� ��� �׽�Ʈ
/// </summary>
/// <param name="controllerIndex"></param>
void MovementComponent::XBOXController(int controllerIndex)
{
	/// A B X Y
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::A))
		std::cout << std::to_string(controllerIndex + 1) << "P�� A ��ư PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::A))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� A ��ư HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::A))
		std::cout << std::to_string(controllerIndex + 1) << "P�� A ��ư END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::B))
		std::cout << std::to_string(controllerIndex + 1) << "P�� B ��ư PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::B))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� B ��ư HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::B))
		std::cout << std::to_string(controllerIndex + 1) << "P�� B ��ư END" << std::endl;

	/// L1 R1
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::L1))
		std::cout << std::to_string(controllerIndex + 1) << "P�� L1 ��ư PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::L1))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� L1 ��ư HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::L1))
	{
		std::cout << std::to_string(controllerIndex + 1) << "P�� L1 ��ư END" << std::endl;
		InputManager::SetControllerVib(controllerIndex, 0, 0);
	}

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::R1))
		std::cout << std::to_string(controllerIndex + 1) << "P�� R1 ��ư PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::R1))
		// std::cout << std::to_string(controllerIndex + 1) <<"P�� R1 ��ư HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::R1))
	{
		std::cout << std::to_string(controllerIndex + 1) << "P�� R1 ��ư END" << std::endl;
		InputManager::SetControllerVib(controllerIndex, 0, 0);
	}

	/// L3 R3
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::L3))
		std::cout << std::to_string(controllerIndex + 1) << "P�� L3 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::L3))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� L3 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::L3))
		std::cout << std::to_string(controllerIndex + 1) << "P�� L3 END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::R3))
		std::cout << std::to_string(controllerIndex + 1) << "P�� R3 PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::R3))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� R3 HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::R3))
		std::cout << std::to_string(controllerIndex + 1) << "P�� R3 END" << std::endl;

	/// START BACK
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::START))
		std::cout << std::to_string(controllerIndex + 1) << "P�� START PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::START))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� START HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::START))
		std::cout << std::to_string(controllerIndex + 1) << "P�� START END" << std::endl;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::BACK))
		std::cout << std::to_string(controllerIndex + 1) << "P�� BACK PUSH" << std::endl;
	// else if (InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::BACK))
		// std::cout << std::to_string(controllerIndex + 1) << "P�� BACK HOLD" << std::endl;
	else if (InputManager::GetInstance()->IsPadButtonEnd(controllerIndex, GamePadButtonCode::BACK))
		std::cout << std::to_string(controllerIndex + 1) << "P�� BACK END" << std::endl;

	/// ���� / ������ ��ƽ
	thumbLeft = InputManager::GetPadAxisLeftThumb(controllerIndex);
	thumbRight = InputManager::GetPadAxisRightThumb(controllerIndex);

	/// �̵� ��ư
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

	// 1P ~ 4P������ ��Ʈ�ѷ� �Է��� �޾ƿ´�
	if (m_pOwner->GetName() == L"PlayerObject1")
		XBOXController(0);
	else if (m_pOwner->GetName() == L"PlayerObject2")
		XBOXController(1);
	else if (m_pOwner->GetName() == L"PlayerObject3")
		XBOXController(2);
	else if (m_pOwner->GetName() == L"PlayerObject4")
		XBOXController(3);

	/// Move Direction ����

	// ���� ��ƽ�� �Է°�
	float rawLX = max(-1, thumbLeft.x);
	float rawLY = max(-1, (-1) * thumbLeft.y);	// ���� -1���� �۾����� ��� -1�� ������ �Ѵ�

	// ���� ��ư���� �̵��ϴ� ���
	if (rawBX != 0 || rawBY != 0)
		m_MoveDir = { rawBX, rawBY };	// ���� ��ư�� �̿��� �̵�
	else
		m_MoveDir = { rawLX, rawLY };	// ��ƽ�� �̿��� �̵�

	// �̵� ������ ���� ���͸� ���Ѵ�
	m_MoveDir.Normalize();

	/// Look Direction ����

	// ������ ��ƽ�� �Է°�
	float rawRX = max(-1, thumbRight.x);
	float rawRY = max(-1, (-1) * thumbRight.y);	// ���� -1���� �۾����� ��� -1�� ������ �Ѵ�

	// ������ ��ƽ�� �Է°��� �ִ� ��쿡�� ������ �ٲ��ش�
	 if(rawRX != 0.f || rawRY != 0.f)
	 	m_LookDir = { rawRX, rawRY };

	// �̵� ������ ���� ���͸� ���Ѵ�
	m_LookDir.Normalize();

	// �÷��̾� �̵�
	m_pOwner->GetRootComponent()->AddRelativeLocation(m_MoveDir * m_Velocity * deltaTime);
}