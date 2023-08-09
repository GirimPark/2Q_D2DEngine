#pragma once

class TimeManager
{
public:
	TimeManager();

public:
	void Initialize();
	void Update();
	const float GetDeltaTime() const { return m_DeltaTime; }
	const float GetFrameRate() const ;

private:
	LARGE_INTEGER m_PreviousTime;
	LARGE_INTEGER m_CurrentTime;
	LARGE_INTEGER m_Frequency;
	float m_DeltaTime;
};