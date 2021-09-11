#include ".\commonfunctionmusicse.h"
#include "../PMDPlayer/PMDPlayer.h"
#include "../MMDPlayer/MMDPlayer.h"
#include "../SE/soundeffect.h"
#include "../../Game/Game.h"
#pragma comment(lib,"GuruGuruSMF4.lib")

namespace th5w {

	CCommonFunctionMusicSE::CCommonFunctionMusicSE(void)
	{
	}

	CCommonFunctionMusicSE::~CCommonFunctionMusicSE(void)
	{
	}
	bool CCommonFunctionMusicSE::LoadMusicFromDat(Cth5DatFile* pDatFile, char* musicFileName, bool m2exist)
	{

		char bgmFileName[20] = { 0 };
		strcpy(bgmFileName, musicFileName);
		int music = CGame::GVar().m_initMusic;
		printf("当前播放BGM：%s\n", bgmFileName);
		if (music == 1 || (music == 2 && m2exist == false))
		{
			strcat(bgmFileName, ".M");
			return CCommonFunctionMusicSE::LoadMusicToPMDFromDat(pDatFile, bgmFileName);
		}
		else if (music == 2 && m2exist == true)
		{
			strcat(bgmFileName, ".M2");
			return CCommonFunctionMusicSE::LoadMusicToPMDFromDat(pDatFile, bgmFileName);
		}
		else if (music == 3)
		{
			sprintf(bgmFileName, "BGM/MIDI/%s.mid", musicFileName);
			//if (midiplayer.isPlaying())
			//	midiplayer.pause();
			//midifile.load(bgmFileName);
			//midiplayer.setFile(&midifile);
			//return true;
			th5w::CMMDPlayer::LoadMMDData(bgmFileName);
			return true;
		}
		else
		{
			return true;
		}
	}


	bool CCommonFunctionMusicSE::LoadMusicToPMDFromDat(Cth5DatFile* pDatFile, char* musicFileName)
	{
		int musicFileIdx;
		musicFileIdx = pDatFile->GetChildFileIndex(musicFileName);
		if (musicFileIdx == -1)
			return false;

		if (th5w::CPMDPlayer::LoadPMDData(pDatFile->GetChildFileContentPointer(musicFileIdx),
			pDatFile->GetChildFileLength(musicFileIdx)) == false)
			return false;

		return true;
	}

	bool CCommonFunctionMusicSE::UnloadData()
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::UnloadPMDData();
			return true;
		}
		/*else if (music == 3)
		{
			if (midiplayer.isPlaying())
				midiplayer.pause();
			return true;
		}*/
		return false;
	}
	bool CCommonFunctionMusicSE::Play()
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::Play();
			return true;
		}
		else if (music == 3)
		{
			//if(midifile!=NULL)
			th5w::CMMDPlayer::Play();
			return true;
		}
		return false;
	}
	bool CCommonFunctionMusicSE::Pause()
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::Pause();
			return true;
		}
		else if (music == 3)
		{
			th5w::CMMDPlayer::Pause();
			return true;
		}
		return false;
	}
	bool CCommonFunctionMusicSE::Resume()
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::Resume();
			return true;
		}
		else if (music == 3)
		{
			th5w::CMMDPlayer::Resume();
			return true;
		}
		return false;
	}
	bool CCommonFunctionMusicSE::Finalize()
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::Finalize();
			return true;
		}
		else if (music == 3)
		{
			//midiplayer.goTo(CxxMidi::Time::Point::zero());
			th5w::CMMDPlayer::Finalize();
		}
		return false;
	}
	bool CCommonFunctionMusicSE::SetVolume(float volume)
	{
		int music = CGame::GVar().m_initMusic;
		if (music == 1 || music == 2)
		{
			th5w::CPMDPlayer::SetVolume(volume);
			return true;
		}
		else if (music == 3)
		{
			th5w::CMMDPlayer::SetVolume(volume);
			return true;
		}
		return false;
	}
	void CCommonFunctionMusicSE::PlaySe(int soundIdx)
	{
		int se = CGame::GVar().m_initSe;
		if (se == 1)
		{
			CGame::s_pCurGame->m_soundEffect.PlaySound(soundIdx);
		}
		else 	if (se == 2)
		{
			CGame::s_pCurGame->m_soundEffect2.PlaySound(soundIdx);
		}
		printf("音效：%d\n",soundIdx);
	}

}
