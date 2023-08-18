#pragma once

#include "Event.h"

#include <list>
#include <map>

/// <summary>
///	�̺�Ʈ Ÿ�Կ� enum
///	�̺�Ʈ �Ǻ��� ����Ѵ�, Ÿ�� ���� ���ڷ� ������ �������� �ٸ���
///	</summary>
enum eEventType
{
	// FSMComponent - AnimationComponent
	P1SetDefaultAnimation,
	P2SetDefaultAnimation,
	P3SetDefaultAnimation,
	P4SetDefaultAnimation,

	P1ChangeAnimation,
	P2ChangeAnimation,
	P3ChangeAnimation,
	P4ChangeAnimation,

	P1KeepAnimation,
	P2KeepAnimation,
	P3KeepAnimation,
	P4KeepAnimation,

	// FSMComponent - PlayerMovement
	P1TransperMovement,
	P2TransperMovement,
	P3TransperMovement,
	P4TransperMovement,

	// UIComponent - ButtonUIComponent
	// ���� ��ȯ
	ChangeWorld_Start,
	ChangeWorld,
	ChangeWorldToMain,				// MainWorld�� ��ȯ(����ȭ��)
	ChangeWorldToInstruction,		// GameMethonWorld�� ��ȯ(���ӹ��)
	ChangeWorldToMadeBy,			// MadeByWorld�� ��ȯ(����)
	ChangeWorldToGameSetting,		// GameSettingWorld�� ��ȯ(���Ӽ���)
	ChangeWorldToInGame,			// InGameWorld�� ��ȯ(�ΰ���)
	ChangeWorld_End,

	// ���� �����Ұ��� �� �Ұ���
	CheckQuitGame,
	QuitGame,
	ResumeGame,

	// ������ ������ �԰� ������ ��
	DeleteThrow,
	DeleteInstallation,
	DeleteReinforced,
	DeleteMoney,

	// World Pause ���� ���� ON OFF
	PauseOn,
	PauseOff,

	// DeleteObject
	DeleteGameObject,
};


class EventListener;
class GameObject;

/// <summary>
///	1. RegisterListener()�� �̺�ƮŸ�԰� �����ʸ� ���
///	2. SendEvent()�� �̺�Ʈ�� �����ϰ� EventManager.Update()���� ������ m_EventList�� �߰�
///	3. Update()���� �̺�Ʈ Execute
/// </summary>
class EventManager
{
private:
	// �����ڿ� �� �̺�Ʈ�� ���� ���
	std::multimap<eEventType, EventListener*> m_WholeEvents;
	// ó���Ǿ�� �ϴ� �̺�Ʈ ť
	std::list<Event> m_EventList;

	/// ChagneWorld Event�� ��� WorldManager::ChangeWorld()�� �����ϸ鼭 �̺�Ʈ�Ŵ����� �ʱ�ȭ�Ѵ�.
	///	�� ��� �߻��ϴ� ������ ���� ����ó���� �������
	bool m_bChangingWorld = false;

private:
	static EventManager* m_pInstance;

public:
	static EventManager* GetInstance();

	// �ش� eventType�� listener ���, ����
	void RegisterListener(eEventType eventType, EventListener* listener);
	void UnregisterListener(eEventType eventType, EventListener* listener);

	// �ش� listener�� ��ϵ� ��� �̺�Ʈ ����
	void UnregisterAll(EventListener* listener);
	// �̺�Ʈ ���, �̺�Ʈ ����Ʈ �ʱ�ȭ
	void ClearEvents();

	void Initialize();	// ���� Initialize���� ��ϵ� Event ����
	void Update();	// �̺�Ʈ ť ����
	void Finalize();

	// �̺�Ʈ Ÿ�� �� �̺�Ʈ�� �ʿ��� ���� ����
	void SendEvent(eEventType eventId);
	void SendEvent(eEventType eventId, framework::EVENT_ANIMATION_INFO animationInfo);
	void SendEvent(eEventType eventId, framework::EVENT_MOVEMENT_INFO movementInfo);
	void SendEvent(eEventType eventId, GROUP_TYPE group, GameObject* obj);

private:
	// �̹� ��ϵ� �̺�Ʈ���� Ȯ��
	bool IsRegistered(eEventType eventType, EventListener* listener);

	// �̺�Ʈ ���࿡ ���
	void ExecuteEvent(Event* event);
};

