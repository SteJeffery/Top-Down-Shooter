#include "AudioManager.h"

#include "SoundEffect.h"
#include "StreamedAudio.h"

#include "../Utils/Utils.h"

//#define DISABLE_AUDIO

const int MAX_AUDIO_OBJECTS = 256;

AudioManager::AudioManager()
	:m_NumAudioObjects(0)
{
}

AudioManager::~AudioManager()
{
	RemoveAllAudioObjects();
}

void AudioManager::PlaySoundFX(const char* filename, bool loop)
{
#ifdef DISABLE_AUDIO
	return;
#endif

	if(m_NumAudioObjects >= MAX_AUDIO_OBJECTS)
	{
		return;
	}

	++m_NumAudioObjects;

	soundEffect = new SoundEffect();
	soundEffect->Initialise(filename, loop);
	soundEffect->Play();

	m_SoundEffects.push_back(soundEffect);
}

void AudioManager::PlayMusic(const char* filename, bool loop)
{
#ifdef DISABLE_AUDIO
	return; //temp
#endif

	if (m_NumAudioObjects >= MAX_AUDIO_OBJECTS)
	{
		return;
	}

	++m_NumAudioObjects;

	streamedAudio = new StreamedAudio();
	streamedAudio->Initialise(filename,loop);
	streamedAudio->Play();

	m_StreamedAudio.push_back(streamedAudio);
}

void AudioManager::SetMusicVolume(float volume)
{
	streamedAudio->SetVolume(volume);
}

void AudioManager::SetSFXVolume(float volume)
{
	soundEffect->SetVolume(volume);
}

void AudioManager::Update()
{
	//check if audio has finished playing and delete if it has
	//TODO: If the audio is to loop then dont delete it>	
	for (std::vector<SoundEffect*>::iterator sfxIter = m_SoundEffects.begin(); sfxIter != m_SoundEffects.end(); )
	{
		if ((*sfxIter)->HasFinished())
		{
			SAFE_DELETE_PTR(*sfxIter);
			sfxIter = m_SoundEffects.erase(sfxIter);
			--m_NumAudioObjects;
		}
		else
		{ 
			sfxIter++;
		}
	}
		
	for (std::vector<StreamedAudio*>::iterator streamedAudioIter = m_StreamedAudio.begin(); streamedAudioIter != m_StreamedAudio.end(); )
	{
		if ((*streamedAudioIter)->HasFinished())
		{
			SAFE_DELETE_PTR(*streamedAudioIter);
			streamedAudioIter = m_StreamedAudio.erase(streamedAudioIter);
			--m_NumAudioObjects;
		}
		else
		{
			streamedAudioIter++;
		}
	}
}

void AudioManager::RemoveAllAudioObjects()
{
	for (std::vector<SoundEffect*>::iterator sfxIter = m_SoundEffects.begin(); sfxIter != m_SoundEffects.end(); )
	{
		(*sfxIter)->Stop();
		SAFE_DELETE_PTR(*sfxIter);
		sfxIter = m_SoundEffects.erase(sfxIter);
		--m_NumAudioObjects;
	}

	for (std::vector<StreamedAudio*>::iterator streamedAudioIter = m_StreamedAudio.begin(); streamedAudioIter != m_StreamedAudio.end(); )
	{
		(*streamedAudioIter)->Stop();
		SAFE_DELETE_PTR(*streamedAudioIter);
		streamedAudioIter = m_StreamedAudio.erase(streamedAudioIter);
		--m_NumAudioObjects;
	}
}

void AudioManager::RemoveAllMusicObjects()
{
	for (std::vector<StreamedAudio*>::iterator streamedAudioIter = m_StreamedAudio.begin(); streamedAudioIter != m_StreamedAudio.end(); )
	{
		(*streamedAudioIter)->Stop();
		SAFE_DELETE_PTR(*streamedAudioIter);
		streamedAudioIter = m_StreamedAudio.erase(streamedAudioIter);
		--m_NumAudioObjects;
	}
}

void AudioManager::RemoveAllSFXObjects()
{
	for (std::vector<SoundEffect*>::iterator sfxIter = m_SoundEffects.begin(); sfxIter != m_SoundEffects.end(); )
	{
		(*sfxIter)->Stop();
		SAFE_DELETE_PTR(*sfxIter);
		sfxIter = m_SoundEffects.erase(sfxIter);
		--m_NumAudioObjects;
	}
}
