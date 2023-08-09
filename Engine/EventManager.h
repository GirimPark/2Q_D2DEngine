#pragma once

#include "Event.h"

#include <list>
#include <map>

enum eEventType
{
	// FSMComponent - AnimationComponent
	AnimationEnd,
	ChangeCurAnimation,
	SetDefaultAnimation,

	// FSMComponent - MovementComponent
	TransperMovement,

};

class EventListener;

class EventManager
{
private:
	// 구독자와 그 이벤트에 대한 목록
	std::multimap<eEventType, EventListener*> m_WholeEvents;
	// 처리되어야 하는 이벤트 큐
	std::list<Event> m_EventList;

private:
	static EventManager* m_pInstance;

public:
	static EventManager* GetInstance();

	// 해당 eventType의 listener 등록, 해제
	void RegisterListener(eEventType eventType, EventListener* listener);
	void UnregisterListener(eEventType eventType, EventListener* listener);

	// 해당 listener에 등록된 모든 이벤트 해제
	void UnregisterAll(EventListener* listener);
	// 처리되어야 하는 이벤트 큐 초기화
	void ClearEventList();

	void Initialize();	// 각종 Initialize에서 등록된 Event 실행
	void Update();	// 이벤트 큐 실행
	void Finalize();

	// 이벤트 타입 및 이벤트에 필요한 정보 전달
	void SendEvent(eEventType eventId);
	void SendEvent(eEventType eventId, framework::EVENT_ANIMATION_INFO animationInfo);
	void SendEvent(eEventType eventId, framework::EVENT_MOVEMENT_INFO movementInfo);

private:
	// 이미 등록된 이벤트인지 확인
	bool IsRegistered(eEventType eventType, EventListener* listener);

	// 이벤트 실행에 사용
	void ExecuteEvent(Event* event);
};

