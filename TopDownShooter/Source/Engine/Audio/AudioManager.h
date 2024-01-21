#ifndef _AUDIO_MANAGER_H
#define _AUDIO_MANAGER_H

#include <vector>

class SoundEffect;
class StreamedAudio;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySoundFX(const char* filename, bool loop);
	void PlayMusic(const char* filename, bool loop);
	void SetMusicVolume(float volume);
	void SetSFXVolume(float volume);

	void Update();

	void RemoveAllAudioObjects();
	void RemoveAllMusicObjects();
	void RemoveAllSFXObjects();

private:

	std::vector<SoundEffect*> m_SoundEffects;
	std::vector<StreamedAudio*> m_StreamedAudio;

	SoundEffect* soundEffect;
	StreamedAudio* streamedAudio;

	int m_NumAudioObjects;
};

#endif
