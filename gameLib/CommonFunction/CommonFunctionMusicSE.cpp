#include ".\commonfunctionmusicse.h"
#include "../../Game/Game.h"

namespace th5w{

CCommonFunctionMusicSE::CCommonFunctionMusicSE(void)
{
}

CCommonFunctionMusicSE::~CCommonFunctionMusicSE(void)
{
}
bool CCommonFunctionMusicSE::LoadMusicFromDat(Cth5DatFile *pDatFile, char *musicFileName, bool m2exist)
{
	char bgmFileName[20] = { 0 };
	strcpy(bgmFileName, musicFileName);
	int music = CGame::GVar().m_initMusic;
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
		//strcat(bgmFileName, ".MID");//or mmd...
		
		strcat(bgmFileName, ".WAV");//or mmd...
		//return th5w::CMMDPlayer::LoadMMDData(bgmFileName);
		return false;
	}
	else
	{
			return true;
	}
		
}


bool CCommonFunctionMusicSE::LoadMusicToPMDFromDat(Cth5DatFile *pDatFile,char *musicFileName)
{
	int musicFileIdx;
	musicFileIdx=pDatFile->GetChildFileIndex(musicFileName);
	if (musicFileIdx==-1)
		return false;

	if (th5w::CPMDPlayer::LoadPMDData(pDatFile->GetChildFileContentPointer(musicFileIdx),
										pDatFile->GetChildFileLength(musicFileIdx))==false)
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
	else if (music == 3)
	{
		//th5w::CMMDPlayer::UnloadMMDData();
		//return true;
		return false;
	}
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
		//th5w::CMMDPlayer::Play();
		//return true;
		return false;
	}
	else
	{
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
		//th5w::CMMDPlayer::Pause();
		//return true;
		return false;
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
		//th5w::CMMDPlayer::Resume();
		//return true;
		return false;
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
		//th5w::CMMDPlayer::Fianlize();
		//return true;
		return false;
	}
	return false;
}
}
