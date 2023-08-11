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
	ChangeAnimation,
	KeepAnimation,
	SetDefaultAnimation,

	// FSMComponent - MovementComponent
	TransperMovement,

};


class EventListener;

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

private:
	static EventManager* m_pInstance;

public:
	static EventManager* GetInstance();

	// �ش� eventType�� listener ���, ����
	void RegisterListener(eEventType eventType, EventListener* listener);
	void UnregisterListener(eEventType eventType, EventListener* listener);

	// �ش� listener�� ��ϵ� ��� �̺�Ʈ ����
	void UnregisterAll(EventListener* listener);
	// ó���Ǿ�� �ϴ� �̺�Ʈ ť �ʱ�ȭ
	void ClearEventList();

	void Initialize();	// ���� Initialize���� ��ϵ� Event ����
	void Update();	// �̺�Ʈ ť ����
	void Finalize();

	// �̺�Ʈ Ÿ�� �� �̺�Ʈ�� �ʿ��� ���� ����
	void SendEvent(eEventType eventId);
	void SendEvent(eEventType eventId, framework::EVENT_ANIMATION_INFO animationInfo);
	void SendEvent(eEventType eventId, framework::EVENT_MOVEMENT_INFO movementInfo);

private:
	// �̹� ��ϵ� �̺�Ʈ���� Ȯ��
	bool IsRegistered(eEventType eventType, EventListener* listener);

	// �̺�Ʈ ���࿡ ���
	void ExecuteEvent(Event* event);
};
