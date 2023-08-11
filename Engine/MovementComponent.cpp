#include "pch.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "SceneComponent.h"
#include "EventManager.h"

/*
int ConvertToRaw(float& thumbValue)
{
	constexpr float threshold = 0.2f; // �Ӱ谪�� ����

	if (thumbValue > threshold) return 1;
	if (thumbValue < -threshold) return -1;

	return 0;
}
*/

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
	m_ThumbLeft = InputManager::GetPadAxisLeftThumb(controllerIndex);
	m_ThumbRight = InputManager::GetPadAxisRightThumb(controllerIndex);

	/// �̵� ��ư
	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::UP) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::UP))
		m_RawBY = -1;
	else if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::DOWN) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::DOWN))
		m_RawBY = 1;
	else if (!InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::UP) &&
		!InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::DOWN))
		m_RawBY = 0;

	if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::LEFT) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::LEFT))
		m_RawBX = -1;
	else if (InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::RIGHT) ||
		InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::RIGHT))
		m_RawBX = 1;
	else if (!InputManager::GetInstance()->IsPadButtonPush(controllerIndex, GamePadButtonCode::LEFT) &&
		!InputManager::GetInstance()->IsPadButtonHold(controllerIndex, GamePadButtonCode::RIGHT))
		m_RawBX = 0;

	/// L2 R2
	const float triggerL = InputManager::GetPadAxisLeftTrigger(controllerIndex);
	const float triggerR = InputManager::GetPadAxisRightTrigger(controllerIndex);

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

	/// Look Direction ����

	// ������ ��ƽ�� �Է°�
	float rawRX = max(-1, m_ThumbRight.x);
	float rawRY = max(-1, (-1) * m_ThumbRight.y);	// ���� -1���� �۾����� ��� -1�� ������ �Ѵ�

	// ������ ��ƽ�� �Է°��� �ִ� ��쿡�� ������ �ٲ��ش�
	if (rawRX != 0.f || rawRY != 0.f)
		m_LookDir = { rawRX, rawRY };

	// �ٶ󺸴� ������ ���� ���͸� ���Ѵ�
	m_LookDir.Normalize();

	/// Move Direction ����

	// ���� ��ƽ�� �Է°�
	float rawLX = max(-1, m_ThumbLeft.x);
	float rawLY = max(-1, (-1) * m_ThumbLeft.y);	// ���� -1���� �۾����� ��� -1�� ������ �Ѵ�

	// Ű���� �Է°�
	// float rawKeyInputX = InputManager::GetInstance()->GetAxisRaw("Horizontal");
	// float rawKeyInputY = InputManager::GetInstance()->GetAxisRaw("Vertical");

	if (m_RawBX != 0 || m_RawBY != 0)
		m_MoveDir = { m_RawBX, m_RawBY };	// ���� ��ư���� �̵��ϴ� ���
	else
		m_MoveDir = { rawLX, rawLY };		// ��ƽ���� �̵��ϴ� ���

	// �̵� ������ ���� ���͸� ���Ѵ�
	m_MoveDir.Normalize();

	// ������ ��ƽ�� �Է°��� ���� ��� �̵� ������ �ٶ󺸴� �������� �����Ѵ�
	if (rawRX == 0.f || rawRY == 0.f)
	{
		// �̵� ������ ���� ��쿡�� �ٶ󺸴� �������� �����Ѵ� (�ڵ����� �̵����� ������ �ٶ󺸴� ������ ���� �ٶ󺸴� �������� ������)
		if(m_MoveDir != framework::Vector2D::Zero())
			m_LookDir = m_MoveDir;
	}

	// �ӵ� ����
	m_Velocity = m_MoveDir * m_Speed;

	/// �÷��̾� �̵�
	m_pOwner->GetRootComponent()->AddRelativeLocation(m_Velocity * deltaTime);

	/// Transition�� ���� ����
	framework::EVENT_MOVEMENT_INFO movementInfo = { m_MoveDir, m_LookDir };
	EventManager::GetInstance()->SendEvent(eEventType::TransperMovement, movementInfo);
}