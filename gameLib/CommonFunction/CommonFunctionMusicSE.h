#pragma once
#include "../th5DatFile/th5DatFile.h"
namespace th5w{

class CCommonFunctionMusicSE
{
public:
	static bool LoadMusicToPMDFromDat(Cth5DatFile *pDatFile,char *musicFileName);
	static bool LoadMusicFromDat(Cth5DatFile *pDatFile, char *musicFileName, bool m2exist = true);
	static bool UnloadData();
	static bool Play();
	static bool Pause();
	static bool Resume();
	static bool Finalize();
	static bool SetVolume(float volume);
	static void PlaySe(int soundIdx);
public:
	CCommonFunctionMusicSE(void);
	~CCommonFunctionMusicSE(void);
};

}
