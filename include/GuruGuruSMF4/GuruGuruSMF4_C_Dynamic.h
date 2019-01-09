// GuruGuruSMF ver.4.0.0 ヘッダ(ダイナミックリンク・Cスタイル)

#ifndef _GURUGURUSMF4H_
#define _GURUGURUSMF4H_

#include <windows.h>

#define GGSPLAY_LOOP				1
#define GGSPLAY_SKIPBEGINNING		2
#define GGSPLAY_SKIPENDING			4
#define GGSPLAY_MASTERPITCH			8
#define GGSPLAY_NORMALIZE			16
#define GGSPLAY_EXCLUSIVE			32

#define GGSLOAD_BUFFERED			1

#define GGSDEVICE_DIRECTMUSIC		-1100

typedef enum {
	GGSERROR_NOERROR,
	GGSERROR_FAILED,
	GGSERROR_FILENOTFOUND,
	GGSERROR_CANNOT_OPENFILE,
	GGSERROR_BADFILESIZE,
	GGSERROR_NOSMF,
	GGSERROR_BADSMF,
	GGSERROR_UNMATCHED_SMF,
	GGSERROR_CANNOT_OPENDEVICE,
	GGSERROR_CANNOT_STARTTIMER,
	GGSERROR_ILLEGAL_POINTER,
	GGSERROR_TRACKLIMIT,
	GGSERROR_NOTREADY,
	GGSERROR_UNDEFINED_ID,
	GGSERROR_API_NULL
} GGSERROR;

typedef enum {
	GGSSTATE_STOP,
	GGSSTATE_PLAY,
	GGSSTATE_PAUSE
} GGSPLAYERSTATE;


typedef struct {
	GGSPLAYERSTATE State;
	int Tempo;
	int Tick;
	int Time;
	int LoopCount;
} GGS4PLAYERSTATUS;

typedef struct {
	int TimeBase;
	int TotalTick;
	int TotalTime;
	int FirstNoteTick;
	int FirstNoteTime;
	int LastNoteTick;
	int LastNoteTime;
	int LoopTick;
	int LoopTime;
} GGS4SMFINFORMATION;

typedef struct {
	int Count;
	int* Keys;
} GGS4SMFLISTKEYS;

#ifdef __cplusplus
extern "C" {
#endif

	GGSERROR GGS4OpenDevice(int deviceId, HWND handle);
	void GGS4CloseDevice();
	GGSERROR GGS4AddDlsW(LPCWSTR fileName);
	GGSERROR GGS4AddDlsA(LPCSTR fileName);
	GGSERROR GGS4Play(int option, int musicId, int seek, int fadeInTime, int keyShift);
	void GGS4Stop(int fadeOutTime);
	void GGS4Pause();
	void GGS4Restart();
	void GGS4SetMasterTempo(float tempo);
	void GGS4SetMasterVolume(int volume);
	void GGS4SetMasterPitch(int pitch);
	void GGS4GetPlayerStatus(GGS4PLAYERSTATUS* status);
	GGSERROR GGS4AddListFromFileW(LPCWSTR fileName, int option, int musicId);
	GGSERROR GGS4AddListFromFileA(LPCSTR fileName, int option, int musicId);
	GGSERROR GGS4AddListFromMemory(LPCBYTE smfBinary, int length, int option, int musicId);
	void GGS4DeleteListItem(int musicId);
	void GGS4ClearList();
	const GGS4SMFLISTKEYS* GGS4EnumList();
	GGSERROR GGS4GetSmfInformation(GGS4SMFINFORMATION* info, int musicId);

	GGSERROR GGS4Initialize();
	void GGS4Free();

#ifdef __cplusplus
}
#endif

#endif



