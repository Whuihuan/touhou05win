//#include "..\..\include\cxxmidi/file.hpp"
//#include "..\..\include\cxxmidi/output/default.hpp"
//#include "..\..\include\cxxmidi/player/asynchronous.hpp"
//#include "..\..\include\cxxmidi/callback.hpp"
#include ".\commonfunctionmusicse.h"
#include "../../Game/Game.h"
//#pragma comment(lib,"winmm.lib")
//CxxMidi::Output::Default midioutput(0);
//CxxMidi::Player::Asynchronous midiplayer(&midioutput);
//CxxMidi::File midifile;

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
		sprintf(bgmFileName, "BGM/%s.mid", musicFileName);
		//if (midiplayer.isPlaying())
		//	midiplayer.pause();
		//midifile.load(bgmFileName);
		//midiplayer.setFile(&midifile);
		//return true;
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
	/*else if (music == 3)
	{
		//if(midifile!=NULL)
			midiplayer.play();
		return true;
	}*/
	else
	{
		return false;
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
	/*else if (music == 3)
	{
		midiplayer.pause();
		return true;
	}*/
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
	/*else if (music == 3)
	{
		midiplayer.play();
		return true;
	}*/
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
	/*else if (music == 3)
	{
		//midiplayer.goTo(CxxMidi::Time::Point::zero());
		midiplayer.pause();
	}*/
	return false;
}
}
