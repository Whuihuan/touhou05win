// GuruGuruSMF ver.4.0.0 ヘッダ(スタイティックリンク・Cスタイル)

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

	GGSERROR WINAPI GGS4OpenDevice(int deviceId, HWND handle);
	void WINAPI GGS4CloseDevice();
	GGSERROR WINAPI GGS4AddDlsW(LPCWSTR fileName);
	GGSERROR WINAPI GGS4AddDlsA(LPCSTR fileName);
	GGSERROR WINAPI GGS4Play(int option, int musicId, int seek, int fadeInTime, int keyShift);
	void WINAPI GGS4Stop(int fadeOutTime);
	void WINAPI GGS4Pause();
	void WINAPI GGS4Restart();
	void WINAPI GGS4SetMasterTempo(float tempo);
	void WINAPI GGS4SetMasterVolume(int volume);
	void WINAPI GGS4SetMasterPitch(int pitch);
	void WINAPI GGS4GetPlayerStatus(GGS4PLAYERSTATUS* status, int size);
	GGSERROR WINAPI GGS4AddListFromFileW(LPCWSTR fileName, int option, int musicId);
	GGSERROR WINAPI GGS4AddListFromFileA(LPCSTR fileName, int option, int musicId);
	GGSERROR WINAPI GGS4AddListFromMemory(LPCBYTE smfBinary, int length, int option, int musicId);
	void WINAPI GGS4DeleteListItem(int musicId);
	void WINAPI GGS4ClearList();
	const GGS4SMFLISTKEYS* WINAPI GGS4EnumList();
	GGSERROR WINAPI GGS4GetSmfInformation(GGS4SMFINFORMATION* info, int size, int musicId);

#ifdef __cplusplus
}
#endif


#endif


