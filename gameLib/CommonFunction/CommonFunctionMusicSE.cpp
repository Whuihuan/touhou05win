#include ".\commonfunctionmusicse.h"
#include "../../Game/Game.h"

namespace th5w{

CCommonFunctionMusicSE::CCommonFunctionMusicSE(void)
{
}

CCommonFunctionMusicSE::~CCommonFunctionMusicSE(void)
{
}
bool CCommonFunctionMusicSE::LoadMusicFromDat(Cth5DatFile *pDatFile, char *musicFileName)
{
	char bgmFileName[20] = { 0 };
	strcpy(bgmFileName, musicFileName);
	int music = CGame::GVar().m_initMusic;
	if (music == 1)
	{
		strcat(bgmFileName, ".M");
		return CCommonFunctionMusicSE::LoadMusicToPMDFromDat(pDatFile, bgmFileName);
	}
	else if (music == 2)
	{
		strcat(bgmFileName, ".M2");
		return CCommonFunctionMusicSE::LoadMusicToPMDFromDat(pDatFile, bgmFileName);
	}
	else
	{
		bgmFileName[0] = 0;
		return CCommonFunctionMusicSE::LoadMusicToPMDFromDat(pDatFile, bgmFileName);
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
bool CCommonFunctionMusicSE::Play()
{
	int music = CGame::GVar().m_initMusic;
	if (music == 1 || music == 2)
	{
		th5w::CPMDPlayer::Play();
		return true;
	}
	return false;
}
}
