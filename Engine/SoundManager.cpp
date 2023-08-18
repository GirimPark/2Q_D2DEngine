#include "pch.h"
#include "SoundManager.h"

void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const char* music)
{
	System_Create(&m_pSystem);
	m_pSystem->init(2, FMOD_INIT_NORMAL, 0);

	if (loopcheck)
	{
		m_pSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &m_pSoundList[static_cast<int>(soundlist)]);
	}
	else
	{
		m_pSystem->createSound(music, FMOD_LOOP_OFF, 0, &m_pSoundList[static_cast<int>(soundlist)]);
	}
}

void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel, float volume)
{
	// 전에 실행되던 사운드 멈추고 실행
	m_pChannel[static_cast<int>(channel)]->stop();
	m_pSystem->playSound(m_pSoundList[static_cast<int>(soundlist)], NULL, 0, &m_pChannel[static_cast<int>(channel)]);
	m_pChannel[static_cast<int>(channel)]->setVolume(volume);
}

void SoundManager::StopMusic(eSoundChannel channel)
{
	m_pChannel[static_cast<int>(channel)]->stop();
}

void SoundManager::SetVolume(float volume, eSoundChannel channel)
{
	m_pChannel[static_cast<int>(channel)]->setVolume(volume);

}