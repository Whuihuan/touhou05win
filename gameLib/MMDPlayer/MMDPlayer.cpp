#include ".\MMDPlayer.h"
#include <stdio.h>
namespace th5w {
	GuruGuruSmf::Ggs4* CMMDPlayer::m_manager = NULL;

	CMMDPlayer::CMMDPlayer(void)
	{
	}

	CMMDPlayer::~CMMDPlayer(void)
	{
	}

	bool CMMDPlayer::Initialize(HWND hWnd)
	{
		if (m_manager->Initialize() != GuruGuruSmf::GgsError::NoError)
			return false;
		m_manager->OpenDevice(-1100, hWnd);
		m_manager->SetMasterVolume(100);
		return true;
	}
	bool CMMDPlayer::LoadMMDData(char *bgmFileName)
	{
		m_manager->AddListFromFileA(bgmFileName, 1, 0);
		return true;

	}
	bool CMMDPlayer::UnloadMMDData()
	{
		//m_pMIDISound = NULL;
		return true;
	}
	void CMMDPlayer::Play()
	{
		m_manager->Play(GuruGuruSmf::PlayOption::SkipBeginning|GuruGuruSmf::PlayOption::Loop,0,0,0,0);
	}
	void CMMDPlayer::Pause()
	{
		m_manager->Pause();
	}
	void CMMDPlayer::Resume()
	{
		m_manager->Restart();
	}
	void CMMDPlayer::Finalize()
	{
		m_manager->Stop(0);
	}
	void CMMDPlayer::SetFrequency(int newFreq)
	{

	}
	void CMMDPlayer::SetVolume(float volume)		//0 silence, 100 normal, no amplification
	{

		m_manager->SetMasterVolume((int)volume);
	}
}