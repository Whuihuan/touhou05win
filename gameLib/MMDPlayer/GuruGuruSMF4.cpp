
#include "stdafx.h"
#include "GuruGuruSMF4.h"

namespace GuruGuruSmf {
	
	Ggs4* Ggs4::instance = 0;	// インスタンス置き場
	
	// インスタンス取得(Singleton)
	Ggs4* Ggs4::GetInstance()
	{
		if(instance == 0){
			instance = new Ggs4();
		}
		return instance;
	}
	
	// インスタンス破棄
	void Ggs4::FreeInstance()
	{
		delete instance;
		instance = 0;
	}
	
	// 初期化(static版では何もしない)
	GGSERROR Ggs4::Initialize()
	{
		return GgsError::NoError;
	}
	
	// デストラクタ
	Ggs4::~Ggs4()
	{
		CloseDevice();
	}
	
	// デバイスを開く
	GGSERROR Ggs4::OpenDevice(int deviceId, HWND handle)
	{
		return GGS4OpenDevice(deviceId, handle);
	}
	
	// デバイスを閉じる
	void Ggs4::CloseDevice()
	{
		GGS4CloseDevice();
	}
	
	// DLSを追加(UNICODE)
	GGSERROR Ggs4::AddDlsW(LPCWSTR fileName)
	{
		return GGS4AddDlsW(fileName);
	}
	
	// DLSを追加(Ansi)
	GGSERROR Ggs4::AddDlsA(LPCSTR fileName)
	{
		return GGS4AddDlsA(fileName);
	}
	
	// 演奏！
	GGSERROR Ggs4::Play(int option, int musicId, int seek, int fadeInTime, int keyShift)
	{
		return GGS4Play(option, musicId, seek, fadeInTime, keyShift);
	}
	
	// 停止
	void Ggs4::Stop(int fadeOutTime)
	{
		GGS4Stop(fadeOutTime);
	}
	
	// 一時停止
	void Ggs4::Pause()
	{
		GGS4Pause();
	}
	
	// 一時停止解除
	void Ggs4::Restart()
	{
		GGS4Restart();
	}
	
	// マスターテンポ
	void Ggs4::SetMasterTempo(float tempo)
	{
		GGS4SetMasterTempo(tempo);
	}
	
	// マスターボリューム
	void Ggs4::SetMasterVolume(int volume)
	{
		GGS4SetMasterVolume(volume);
	}
	
	// マスターピッチ
	void Ggs4::SetMasterPitch(int pitch)
	{
		GGS4SetMasterPitch(pitch);
	}
	
	// 演奏情報取得
	void Ggs4::GetPlayerStatus(PlayerStatus* status)
	{
		GGS4GetPlayerStatus(status, sizeof(PlayerStatus));
	}
	
	// ファイルからリストへ追加(UNICODE)
	GGSERROR Ggs4::AddListFromFileW(LPCWSTR fileName, int option, int musicId)
	{
		return GGS4AddListFromFileW(fileName, option, musicId);
	}
	
	// ファイルからリストへ追加(Ansi)
	GGSERROR Ggs4::AddListFromFileA(LPCSTR fileName, int option, int musicId)
	{
		return GGS4AddListFromFileA(fileName, option, musicId);
	}
	
	// メモリからリストへ追加
	GGSERROR Ggs4::AddListFromMemory(LPCBYTE smfBinary, int length, int option, int musicId)
	{
		return GGS4AddListFromMemory(smfBinary, length, option, musicId);
	}
	
	// リストから1つ削除
	void Ggs4::DeleteListItem(int musicId)
	{
		GGS4DeleteListItem(musicId);
	}
	
	// リストをクリア
	void Ggs4::ClearList()
	{
		GGS4ClearList();
	}
	
	// リストを列挙
	const SmfListKeys* Ggs4::EnumList()
	{
		return EnumList();
	}
	
	// SMFの情報を取得
	GGSERROR Ggs4::GetSmfInformation(SmfInformation* info, int musicId)
	{
		return GGS4GetSmfInformation(info, sizeof(SmfInformation), musicId);
	}

}

