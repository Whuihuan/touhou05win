#pragma once
#include <windows.h>
#include "../../include/DSUtil/dsutil.h"
using namespace std;

#pragma comment(lib,"Winmm.lib")
//#pragma comment(lib,"dxerr9.lib")

namespace th5w{

class CMMDPlayer
{
protected:
	CSoundManager m_manager;
	CSound *m_pMIDISound;
public:
	static bool Initialize(HWND hWnd);
	static bool LoadMMDData(char *bgmFileName);
	static bool UnloadMMDData();
	static void Play();
	static void Pause();
	static void Resume();
	static void Finalize();
	static void SetFrequency(int newFreq);
	static void SetVolume(float volume);		//0 silence, 100 normal, no amplification

	void PlaySound(int soundIdx);
public:
	CSoundEffect(void);
	~CSoundEffect(void);
};

