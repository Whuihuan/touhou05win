
#include "GuruGuruSMF4_C_Dynamic.h"


// 関数ポインタの型定義
typedef GGSERROR (WINAPI *FunctionOpenDevice)(int deviceId, HWND handle);
typedef void (WINAPI *FunctionCloseDevice)();
typedef GGSERROR (WINAPI *FunctionAddDlsW)(LPCWSTR fileName);
typedef GGSERROR (WINAPI *FunctionAddDlsA)(LPCSTR fileName);
typedef GGSERROR (WINAPI *FunctionPlay)(int option, int musicId, int seek, int fadeInTime, int keyShift);
typedef void (WINAPI *FunctionStop)(int fadeOutTime);
typedef void (WINAPI *FunctionPause)();
typedef void (WINAPI *FunctionRestart)();
typedef void (WINAPI *FunctionSetMasterTempo)(float tempo);
typedef void (WINAPI *FunctionSetMasterVolume)(int volume);
typedef void (WINAPI *FunctionSetMasterPitch)(int pitch);
typedef void (WINAPI *FunctionGetPlayerStatus)(GGS4PLAYERSTATUS* status, int size);
typedef GGSERROR (WINAPI *FunctionAddListFromFileW)(LPCWSTR fileName, int option, int musicId);
typedef GGSERROR (WINAPI *FunctionAddListFromFileA)(LPCSTR fileName, int option, int musicId);
typedef GGSERROR (WINAPI *FunctionAddListFromMemory)(LPCBYTE smfBinary, int length, int option, int musicId);
typedef void (WINAPI *FunctionDeleteListItem)(int musicId);
typedef void (WINAPI *FunctionClearList)();
typedef const GGS4SMFLISTKEYS* (WINAPI *FunctionEnumList)();
typedef GGSERROR (WINAPI *FunctionGetSmfInformation)(GGS4SMFINFORMATION* info, int size, int musicId);

// 関数ポインタ置き場
static FunctionOpenDevice DllOpenDevice = 0;
static FunctionCloseDevice DllCloseDevice = 0;
static FunctionAddDlsW DllAddDlsW = 0;
static FunctionAddDlsA DllAddDlsA = 0;
static FunctionPlay DllPlay = 0;
static FunctionStop DllStop = 0;
static FunctionPause DllPause = 0;
static FunctionRestart DllRestart = 0;
static FunctionSetMasterTempo DllSetMasterTempo = 0;
static FunctionSetMasterVolume DllSetMasterVolume = 0;
static FunctionSetMasterPitch DllSetMasterPitch = 0;
static FunctionGetPlayerStatus DllGetPlayerStatus = 0;
static FunctionAddListFromFileW DllAddListFromFileW = 0;
static FunctionAddListFromFileA DllAddListFromFileA = 0;
static FunctionAddListFromMemory DllAddListFromMemory = 0;
static FunctionDeleteListItem DllDeleteListItem = 0;
static FunctionClearList DllClearList = 0;
static FunctionEnumList DllEnumList = 0;
static FunctionGetSmfInformation DllGetSmfInformation = 0;

static HMODULE DllHandle = 0;	// DLLハンドル置き場

// 初期化
GGSERROR GGS4Initialize()
{
	if(DllHandle) return GGSERROR_NOERROR;	// 念のため
	
	// アプリケーションのフォルダを取得しフルパス合成(脆弱性対策)
	wchar_t Path[_MAX_PATH];
	wchar_t Drive[_MAX_DRIVE];
	wchar_t Dir[_MAX_DIR];
	GetModuleFileNameW(NULL, Path, sizeof(Path));
	_wsplitpath_s(Path, Drive, _MAX_DRIVE, Dir, _MAX_DIR, NULL, 0, NULL, 0);
	swprintf_s(Path, _MAX_PATH, L"%s%s%s", Drive, Dir, L"GuruGuruSMF4.dll");
	
	DllHandle = LoadLibraryW(Path);
	if(DllHandle == 0) return GGSERROR_FAILED;
	
	/*	Ansi版・Windows9xをターゲットにする場合はこちらにしてみてください
	char Path[_MAX_PATH];
	char Drive[_MAX_DRIVE];
	char Dir[_MAX_DIR];
	GetModuleFileNameA(NULL, Path, sizeof(Path));
	_splitpath_s(Path, Drive, _MAX_DRIVE, Dir, _MAX_DIR, NULL, 0, NULL, 0);
	sprintf_s(Path, _MAX_PATH, "%s%s%s", Drive, Dir, "GuruGuruSMF4.dll");
	
	DllHandle = LoadLibraryA(Path);
	if(DllHandle == 0) return GGSERROR_FAILED;
	*/
	
	
	DllOpenDevice = (FunctionOpenDevice)GetProcAddress(DllHandle, "GGS4OpenDevice");
	DllCloseDevice = (FunctionCloseDevice)GetProcAddress(DllHandle, "GGS4CloseDevice");
	DllAddDlsW = (FunctionAddDlsW)GetProcAddress(DllHandle, "GGS4AddDlsW");
	DllAddDlsA = (FunctionAddDlsA)GetProcAddress(DllHandle, "GGS4AddDlsA");
	DllPlay = (FunctionPlay)GetProcAddress(DllHandle, "GGS4Play");
	DllStop = (FunctionStop)GetProcAddress(DllHandle, "GGS4Stop");
	DllPause = (FunctionPause)GetProcAddress(DllHandle, "GGS4Pause");
	DllRestart = (FunctionRestart)GetProcAddress(DllHandle, "GGS4Restart");
	DllSetMasterTempo = (FunctionSetMasterTempo)GetProcAddress(DllHandle, "GGS4SetMasterTempo");
	DllSetMasterVolume = (FunctionSetMasterVolume)GetProcAddress(DllHandle, "GGS4SetMasterVolume");
	DllSetMasterPitch = (FunctionSetMasterPitch)GetProcAddress(DllHandle, "GGS4SetMasterPitch");
	DllGetPlayerStatus = (FunctionGetPlayerStatus)GetProcAddress(DllHandle, "GGS4GetPlayerStatus");
	DllAddListFromFileW = (FunctionAddListFromFileW)GetProcAddress(DllHandle, "GGS4AddListFromFileW");
	DllAddListFromFileA = (FunctionAddListFromFileA)GetProcAddress(DllHandle, "GGS4AddListFromFileA");
	DllAddListFromMemory = (FunctionAddListFromMemory)GetProcAddress(DllHandle, "GGS4AddListFromMemory");
	DllDeleteListItem = (FunctionDeleteListItem)GetProcAddress(DllHandle, "GGS4DeleteListItem");
	DllClearList = (FunctionClearList)GetProcAddress(DllHandle, "GGS4ClearList");
	DllEnumList = (FunctionEnumList)GetProcAddress(DllHandle, "GGS4EnumList");
	DllGetSmfInformation = (FunctionGetSmfInformation)GetProcAddress(DllHandle, "GGS4GetSmfInformation");
	
	return GGSERROR_NOERROR;
}

// 後始末
void GGS4Free()
{
	GGS4CloseDevice();
	if(DllHandle){
		FreeLibrary(DllHandle);
		DllHandle = 0;
	}
}

// デバイスを開く
GGSERROR GGS4OpenDevice(int deviceId, HWND handle)
{
	if(!DllOpenDevice) return GGSERROR_API_NULL;
	return DllOpenDevice(deviceId, handle);
}

// デバイスを閉じる
void GGS4CloseDevice()
{
	if(!DllCloseDevice) return;
	DllCloseDevice();
}

// DLSを追加(UNICODE)
GGSERROR GGS4AddDlsW(LPCWSTR fileName)
{
	if(!DllAddDlsW) return GGSERROR_API_NULL;
	return DllAddDlsW(fileName);
}

// DLSを追加(Ansi)
GGSERROR GGS4AddDlsA(LPCSTR fileName)
{
	if(!DllAddDlsA) return GGSERROR_API_NULL;
	return DllAddDlsA(fileName);
}

// 演奏！
GGSERROR GGS4Play(int option, int musicId, int seek, int fadeInTime, int keyShift)
{
	if(!DllPlay) return GGSERROR_API_NULL;
	return DllPlay(option, musicId, seek, fadeInTime, keyShift);
}

// 停止
void GGS4Stop(int fadeOutTime)
{
	if(!DllStop) return;
	DllStop(fadeOutTime);
}

// 一時停止
void GGS4Pause()
{
	if(!DllPause) return;
	DllPause();
}

// 一時停止解除
void GGS4Restart()
{
	if(!DllRestart) return;
	DllRestart();
}

// マスターテンポ
void GGS4SetMasterTempo(float tempo)
{
	if(!DllSetMasterTempo) return;
	DllSetMasterTempo(tempo);
}

// マスターボリューム
void GGS4SetMasterVolume(int volume)
{
	if(!DllSetMasterVolume) return;
	DllSetMasterVolume(volume);
}

// マスターピッチ
void GGS4SetMasterPitch(int pitch)
{
	if(!DllSetMasterPitch) return;
	DllSetMasterPitch(pitch);
}

// 演奏情報取得
void GGS4GetPlayerStatus(GGS4PLAYERSTATUS* status)
{
	if(!DllGetPlayerStatus) return;
	DllGetPlayerStatus(status, sizeof(GGS4PLAYERSTATUS));
}

// ファイルからリストへ追加(UNICODE)
GGSERROR GGS4AddListFromFileW(LPCWSTR fileName, int option, int musicId)
{
	if(!DllAddListFromFileW) return GGSERROR_API_NULL;
	return DllAddListFromFileW(fileName, option, musicId);
}

// ファイルからリストへ追加(Ansi)
GGSERROR GGS4AddListFromFileA(LPCSTR fileName, int option, int musicId)
{
	if(!DllAddListFromFileA) return GGSERROR_API_NULL;
	return DllAddListFromFileA(fileName, option, musicId);
}

// メモリからリストへ追加
GGSERROR GGS4AddListFromMemory(LPCBYTE smfBinary, int length, int option, int musicId)
{
	if(!DllAddListFromMemory) return GGSERROR_API_NULL;
	return DllAddListFromMemory(smfBinary, length, option, musicId);
}

// リストから1つ削除
void GGS4DeleteListItem(int musicId)
{
	if(!DllDeleteListItem) return;
	DllDeleteListItem(musicId);
}

// リストをクリア
void GGS4ClearList()
{
	if(!DllClearList) return;
	DllClearList();
}

// リストを列挙
const GGS4SMFLISTKEYS* GGS4EnumList()
{
	if(!DllEnumList) return 0;
	return DllEnumList();
}

// SMFの情報を取得
GGSERROR GGS4GetSmfInformation(GGS4SMFINFORMATION* info, int musicId)
{
	if(!DllGetSmfInformation) return GGSERROR_API_NULL;
	return DllGetSmfInformation(info, sizeof(GGS4SMFINFORMATION), musicId);
}



