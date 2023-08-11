#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	:m_PreviousTime{ 0 }, m_CurrentTime{ 0 }, m_Frequency{ 0 }, m_DeltaTime(0.f)
{
}

void TimeManager::Initialize()
{
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_PreviousTime);
	QueryPerformanceCounter(&m_CurrentTime);
}

void TimeManager::Update()
{
	m_PreviousTime = m_CurrentTime;
	QueryPerformanceCounter(&m_CurrentTime);
	m_DeltaTime = (float)(m_CurrentTime.QuadPart - m_PreviousTime.QuadPart) / (float)m_Frequency.QuadPart;

#ifdef _DEBUG
    if (m_DeltaTime > (1. / 60.))
        m_DeltaTime = (1. / 60.);
#endif
}

const float TimeManager::GetFrameRate() const
{
    static int frameCnt = -1;
    static float timeElapsed = 0.f;
    static float fps = 0;;

    frameCnt++;
    if (frameCnt == 0)
        return 0;

    timeElapsed += m_DeltaTime;

    if (timeElapsed >= 1.0f)
    {
        fps = (float)frameCnt;
        frameCnt = 0;
        timeElapsed -= 1.0f;
    }
    return fps;
}