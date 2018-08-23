#include ".\MMDPlayer.h"
#include "../../include/GuruGuruSMF4/GuruGuruSMF4_C_Static.h"
#pragma comment(lib,"GuruGuruSMF4.lib")
//#include <stdio.h>
namespace th5w {
	//GuruGuruSmf::Ggs4* CMMDPlayer::m_manager = NULL;

	CMMDPlayer::CMMDPlayer(void)
	{
	}

	CMMDPlayer::~CMMDPlayer(void)
	{
	}

	bool CMMDPlayer::Initialize(HWND hWnd)
	{
		//if (GGS4Initialize() != GGSERROR_NOERROR)
		//	return false;
		GGS4OpenDevice(-1100, hWnd);
		GGS4SetMasterVolume(100);
		return true;
	}
	
	bool CMMDPlayer::LoadMMDData(char *bgmFileName)
	{
		GGS4AddListFromFileA(bgmFileName, 1, 0);
		return true;

	}
	
	bool CMMDPlayer::UnloadMMDData()
	{
		//m_pMIDISound = NULL;
		return true;
	}
	
	void CMMDPlayer::Play()
	{
		GGS4Play(GGSPLAY_SKIPBEGINNING|GGSPLAY_LOOP,0,0,0,0);
	}
	
	void CMMDPlayer::Pause()
	{
		GGS4Pause();
	}
	
	void CMMDPlayer::Resume()
	{
		GGS4Restart();
	}
	
	void CMMDPlayer::Finalize()
	{
		GGS4Stop(0);
	}
	
	void CMMDPlayer::FadeIn(int time)
	{
		GGS4Play(GGSPLAY_SKIPBEGINNING|GGSPLAY_LOOP,0,0,time,0);
	}
	
	void CMMDPlayer::FadeOut(int time)
	{
		GGS4Stop(time);
	}
	
	void CMMDPlayer::SetFrequency(int newFreq)
	{

	}
	
	void CMMDPlayer::SetVolume(float volume)		//0 silence, 100 normal, no amplification
	{

		GGS4SetMasterVolume((int)volume);
	}
}