#pragma once
#include "struct.h"

enum eEventType;

class Event
{
public:
	eEventType eventID;
	framework::EVENT_ANIMATION_INFO animationInfo;
	framework::EVENT_MOVEMENT_INFO movementInfo;

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
};
