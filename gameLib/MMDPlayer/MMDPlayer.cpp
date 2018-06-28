/*#include ".\soundeffect.h"
#include <stdio.h>
#include <tchar.h>

namespace th5w{

CSoundEffect::CSoundEffect(void)
{
}

CSoundEffect::~CSoundEffect(void)
{
}

bool CSoundEffect::Initialize(HWND hWnd)
{
	if (m_manager.Initialize(hWnd,DSSCL_PRIORITY)!=S_OK)
		return false;

	*m_pMIDISound = NULL;
	return true;
}
bool CSoundEffect::LoadMMDData(char *pbgmFileName)
{
	TCHAR fileName[1000]={0};
	wsprintf(fileName,_T("BGM/%s"),&pbgmFileName);
	if (m_manager.Create(&m_pMIDISound,fileName,DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLFREQUENCY|
											  DSBCAPS_GLOBALFOCUS|DSBCAPS_CTRLPOSITIONNOTIFY|DSBCAPS_LOCSOFTWARE)!=S_OK)
		return false;
	return true;
	
}
bool UnloadMMDData();
{
	m_pMIDISound = NULL;
	return true;
}
void Play();
{
	m_pMIDISound->Play();
}
void Pause();
{
	
}
void Resume();
{
	
}
void Finalize();
{
	
}
void SetFrequency(int newFreq);
{
	
}
void SetVolume(float volume);		//0 silence, 100 normal, no amplification
{
	
}
/*
void CSoundEffect::PlaySound(int soundIdx)
{

	if (m_pMIDISound==NULL)
		return;

	m_pMIDISound->Stop();
	m_pMIDISound->Reset();
}

}*/