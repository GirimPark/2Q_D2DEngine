#pragma once
#include "struct.h"
#include "GameObject.h"

enum eEventType;
class GameObject;

/// <summary>
///	Event 정보를 가진 클래스
///	이벤트타입에 따라 필요한 정보가 달라 생성자 오버로딩으로 구현한다.
///	</summary>
class Event
{
public:
	eEventType eventID;
	framework::EVENT_ANIMATION_INFO animationInfo;
	framework::EVENT_MOVEMENT_INFO movementInfo;
	GROUP_TYPE objGroup;
	GameObject* obj;

	Event(eEventType eventId)
	{
		this->eventID = eventId;
	}

	Event(eEventType eventId, framework::EVENT_ANIMATION_INFO animationInfo)
	{
		this->eventID = eventId;
		this->animationInfo = animationInfo;
	}

	Event(eEventType eventId, framework::EVENT_MOVEMENT_INFO movementInfo)
	{
		this->eventID = eventId;
		this->movementInfo = movementInfo;
	}

	Event(eEventType eventId, GROUP_TYPE objGroup, GameObject* obj)
	{
		this->eventID = eventId;
		this->objGroup = objGroup;
		this->obj = obj;
	}
};
