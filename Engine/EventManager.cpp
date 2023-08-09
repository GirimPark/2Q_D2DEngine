#include "pch.h"
#include "EventManager.h"

#include "Event.h"
#include "EventListener.h"

EventManager* EventManager::m_pInstance = nullptr;

EventManager* EventManager::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new EventManager;
	return m_pInstance;
}

void EventManager::RegisterListener(eEventType eventType, EventListener* listener)
{
	// listener nullptr Ȯ��, �̹� ��ϵǾ� �ִ��� Ȯ��
	assert(listener);
	if(IsRegistered(eventType, listener))
	{
		return;
	}

	m_WholeEvents.insert(std::make_pair(eventType, listener));
}

void EventManager::UnregisterListener(eEventType eventType, EventListener* listener)
{
	std::pair<std::multimap<eEventType, EventListener*>::iterator,
			  std::multimap<eEventType, EventListener*>::iterator> range;
	range = m_WholeEvents.equal_range(eventType);

	for(auto& iter = range.first; iter!=range.second; ++iter)
	{
		if(iter->second == listener)
		{
			iter = m_WholeEvents.erase(iter);
			break;
		}
	}
}

void EventManager::UnregisterAll(EventListener* listener)
{
	auto iter = m_WholeEvents.begin();

	while(iter!=m_WholeEvents.end())
	{
		if(iter->second == listener)
		{
			iter = m_WholeEvents.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void EventManager::ClearEventList()
{
	m_EventList.clear();
}

void EventManager::Initialize()
{
	while (!m_EventList.empty())
	{
		ExecuteEvent(&m_EventList.front());
		m_EventList.pop_front();
	}
}

void EventManager::Update()
{
	while(!m_EventList.empty())
	{
		ExecuteEvent(&m_EventList.front());
		m_EventList.pop_front();
	}
}

void EventManager::Finalize()
{
	delete m_pInstance;

	//m_WholeEvents.clear();
	//m_EventList.clear();
}

void EventManager::SendEvent(eEventType eventId)
{
	Event newEvent(eventId);
	m_EventList.emplace_back(newEvent);
}

void EventManager::SendEvent(eEventType eventId, framework::EVENT_ANIMATION_INFO animationInfo)
{
	Event newEvent(eventId, animationInfo);
	m_EventList.emplace_back(newEvent);
}

void EventManager::SendEvent(eEventType eventId, framework::EVENT_MOVEMENT_INFO movementInfo)
{
	Event newEvent(eventId, movementInfo);
	m_EventList.emplace_back(newEvent);
}

bool EventManager::IsRegistered(eEventType eventType, EventListener* listener)
{
	bool alreadyRegistered = false;

	// �ش� �̺�Ʈ Ÿ���� Ű������ ���� �ּ� ����, �ִ� ������ ��ȯ
	// Ž�� ���� ���
	std::pair<std::multimap<eEventType, EventListener*>::iterator,
			  std::multimap<eEventType, EventListener*>::iterator> range;
	range = m_WholeEvents.equal_range(eventType);	

	// �̹� ��ϵ� �̺�Ʈ���� Ȯ��
	for(auto& iter = range.first; iter!=range.second; ++iter)
	{
		
		if(iter->second == listener)
		{
			alreadyRegistered = true;
			break;
		}
	}

	return alreadyRegistered;
}

void EventManager::ExecuteEvent(Event* event)
{
	std::pair<std::multimap<eEventType, EventListener*>::iterator,
		std::multimap<eEventType, EventListener*>::iterator> range;
	range = m_WholeEvents.equal_range(event->eventID);

	for(auto& iter = range.first; iter!=range.second; ++iter)
	{
		// �ش� ��ü�� HandleEvent �Լ� ����
		iter->second->HandleEvent(event);
	}
}
