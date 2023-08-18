#pragma once

// FMOD
#ifndef _WIN64
#include "../inc/fmod.hpp"
#pragma comment (lib, "../library/x86/fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "../Resource/inc/fmod.hpp"
#pragma comment (lib, "../Resource/library/_x64/fmod_vc.lib")
using namespace FMOD;
#endif

/// <summary>
/// 사운드 관리하는 매니저
/// BGM과 효과음 따로 enum class로 관리해서 
/// </summary>

enum class eSoundChannel
{
	BGM,
	Effect,
	Size
};

enum class eSoundList
{
	StartBGM,
	PageEffect,
	Size
};

class SoundManager
{
public:
	void LoadMusic(eSoundList list, bool loopcheck, const char* music);
	void PlayMusic(eSoundList list, eSoundChannel channel, float volume);
	void StopMusic(eSoundChannel channel);

	void SetVolume(float volume, eSoundChannel channel);

private:
	FMOD::System* m_pSystem;
	FMOD::Channel* m_pChannel[static_cast<int>(eSoundChannel::Size)];
	FMOD::Sound* m_pSoundList[static_cast<int>(eSoundList::Size)];
};

