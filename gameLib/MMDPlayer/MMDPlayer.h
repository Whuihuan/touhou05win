#pragma once
#include <windows.h>
using namespace std;

namespace th5w {
	class CMMDPlayer
	{
	protected:
	public:
//		static GuruGuruSmf::Ggs4* m_manager;
		static bool Initialize(HWND hWnd);
		static bool LoadMMDData(char *bgmFileName);
		static bool UnloadMMDData();
		static void Play();
		static void Pause();
		static void Resume();
		static void Finalize();
		static void FadeIn(int time);
		static void FadeOut(int time);
		static void SetFrequency(int newFreq);
		static void SetVolume(float volume);		//0 silence, 100 normal, no amplification
	public:
		CMMDPlayer(void);
		~CMMDPlayer(void);
	};
}