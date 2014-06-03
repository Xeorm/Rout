#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <string>
#include <D3DX10Math.h>

using namespace std;

class AudioManager
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	AudioManager();
	AudioManager(const AudioManager&);

	bool Initialize(HWND);
	bool Play(string, D3DXVECTOR3);
	bool PlayBackground(string, D3DXVECTOR3);
	bool PlayFootSteps(string, D3DXVECTOR3);
	bool PlayBoneWheel(string, D3DXVECTOR3, float);
	bool PlayFaded(string, D3DXVECTOR3, float);
	bool PlayEater(string, D3DXVECTOR3, float);
	bool PlayDeathScream(string, D3DXVECTOR3);
	bool AdjustBackgroundVolume(float);
	bool StopBackground();
	bool Stop();
	void Shutdown();
	
	static AudioManager *getInstance();
	~AudioManager(void);

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(char*, IDirectSoundBuffer8**, IDirectSound3DBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

	bool PlayWaveFile(D3DXVECTOR3);
	bool PlayBackgroundWaveFile(D3DXVECTOR3, IDirectSoundBuffer8**, IDirectSound3DBuffer8**);
	bool AdjustBufferVolume(float, IDirectSoundBuffer8**);
	
	static AudioManager *am_instance;

private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSound3DListener8* m_listener;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	IDirectSoundBuffer8* m_secondaryBufferFootSteps;
	IDirectSoundBuffer8* m_secondaryBufferBoneWheel;
	IDirectSoundBuffer8* m_secondaryBufferEater;
	IDirectSoundBuffer8* m_secondaryBufferFaded;
	IDirectSoundBuffer8* m_secondaryBufferDeathScream;
	IDirectSound3DBuffer8* m_secondary3DBuffer1;
	IDirectSound3DBuffer8* m_secondary3DBufferFootSteps;
	IDirectSound3DBuffer8* m_secondary3DBufferBoneWheel;
	IDirectSound3DBuffer8* m_secondary3DBufferEater;
	IDirectSound3DBuffer8* m_secondary3DBufferFaded;
	IDirectSound3DBuffer8* m_secondary3DBufferDeathScream;
	string m_fileLocation;
};

#endif

