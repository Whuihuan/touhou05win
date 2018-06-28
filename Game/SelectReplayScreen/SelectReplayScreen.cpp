#include ".\selectreplayscreen.h"
#include "../Game.h"
#include "../../gameLib/CommonFunction/CommonFunctionInput.h"
#include "../../gameLib/CommonFunction/CommonFunctionGraphic.h"
#include "../../gameLib/CommonFunction/CommonFunctionMusicSE.h"
#include "../../gameLib/Graphic/PC98Font.h"
#include "../../gameLib/Graphic/Th5ExtFont.h"
#include <time.h>
#include <math.h>
#include <shlwapi.h>
#include <tchar.h>
#define PI 3.1415926535897932384626433832795

namespace th5w{

	unsigned char charTable[3][17];
CSelectReplayScreen::CSelectReplayScreen(void)
{
	m_pBGImage=NULL;
	m_bEnterNameMode=false;
}

CSelectReplayScreen::~CSelectReplayScreen(void)
{
	if (m_pBGImage)
		m_pBGImage->Destroy();
	m_pBGImage=NULL;
}

void CSelectReplayScreen::Initialize(bool bLoadMode,bool bSwitchMusic)
{
	//make sure replay sub directory exists
	TCHAR subdir[1000];
	wsprintf(subdir,_T("%S%S\\"),CGame::GVar().m_workingPath,
								 CGame::GVar().m_replaySubDir);
	if (::PathFileExists(subdir)==FALSE)
		::CreateDirectory(subdir,NULL);

	m_curFrame=0;
	m_lastKeyState=0;
	m_curKeyState=0;
	m_bQuit=false;
	m_curScrFade=0;
	m_bStageSelect = false;
	m_bLoadMode=bLoadMode;
	m_nFilePerPage=15;
	m_nPage=6;
	m_listUpperLeftX=2;
	m_listUpperLeftY=4;
	SwitchPage(0);
	m_curCursorPos=0;
	m_curCursorColPos=0;

	if (CGame::GVar().m_bCanSaveReplay==false&&m_bLoadMode==false)
	{
		m_quitCode=SELECTREPLAYSCREEN_END_SAVE_REPLAY_SKIPPED;
		m_bQuit=true;
		return;
	}

	CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage,NULL,&CGame::s_pCurGame->m_th5Dat1,"MS.PI");
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_shineArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"ZUN01.BFT",0);
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_shineArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"ZUN02.BFT",0);

	if (bSwitchMusic)
	{
		if (bLoadMode)
			CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1,"OP");
		else
			CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1,"NAME");
		th5w::CCommonFunctionMusicSE::Play();
	}
}

void CSelectReplayScreen::SwitchPage(int pageIdx)
{
	m_curPage=pageIdx;
	for (int i=0;i<m_nFilePerPage;i++)
	{
		int fileIdx=m_curPage*m_nFilePerPage+i;
		char repFileName[1000];
		sprintf(repFileName,"%s%s\\replay%02d.rpy",CGame::GVar().m_workingPath,
												   CGame::GVar().m_replaySubDir,
												   fileIdx);
		m_bCurPageRepFileExist[i]=CReplay::GetRepFileInfo(&m_repInfo[i],repFileName);
	}
}

void CSelectReplayScreen::StepEnterNameMode()
{
	if (abs(m_curRowY-(m_listUpperLeftY+4)*16)>8)
	{
		if (m_curRowY<(m_listUpperLeftY+4)*16)
			m_curRowY+=8;
		else
			m_curRowY-=8;
		if (abs(m_curRowY-(m_listUpperLeftY+4)*16)<8)
			m_curRowY=(m_listUpperLeftY+4)*16;
		return;
	}
	else
		m_curRowY=(m_listUpperLeftY+4)*16;

	if (CCommonFunctionInput::ESCPressed(m_curKeyState,m_lastKeyState))
		m_bEnterNameMode=false;
	if (CCommonFunctionInput::LeftPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		m_curCharX=(m_curCharX+16)%17;
	}
	if (CCommonFunctionInput::RightPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		m_curCharX=(m_curCharX+1)%17;
	}
	if (CCommonFunctionInput::UpPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		m_curCharY=(m_curCharY+2)%3;
	}
	if (CCommonFunctionInput::DownPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		m_curCharY=(m_curCharY+1)%3;
	}
	if (CCommonFunctionInput::ZPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(11);

		if (m_curCharX==16&&m_curCharY==2)
		{
			memcpy(CGame::GVar().m_replay.m_playerName,m_curEnterName,8);
			char repFileName[1000];
			sprintf(repFileName,"%s%s\\replay%02d.rpy",CGame::GVar().m_workingPath,
													   CGame::GVar().m_replaySubDir,
													   m_curPage*m_nFilePerPage+m_selectedSlot);
			CGame::GVar().m_replay.SaveFile(repFileName);
			memcpy(CGame::GVar().m_defaultReplayName,m_curEnterName,10);
			CGame::GVar().SaveConfig();
			m_bEnterNameMode=false;

			CGame::s_pCurGame->m_soundEffect.PlaySound(14);
			m_bCurPageRepFileExist[m_selectedSlot]=CReplay::GetRepFileInfo(&m_repInfo[m_selectedSlot],repFileName);
		}
		else
		{
			m_curEnterName[m_nameCursorPos]=charTable[m_curCharY][m_curCharX];
			if (m_nameCursorPos<7)
				m_nameCursorPos++;
		}
	}
	if (CCommonFunctionInput::XPressed(m_curKeyState,m_lastKeyState))
	{
		CGame::s_pCurGame->m_soundEffect.PlaySound(11);
		if (m_curEnterName[m_nameCursorPos]!=0)
			m_curEnterName[m_nameCursorPos]=0;
		else
			if (m_nameCursorPos>0)
			{
				m_nameCursorPos--;
				m_curEnterName[m_nameCursorPos]=0;
			}
	}
}

int CSelectReplayScreen::Step()
{
	m_curFrame++;
	if(m_bStageSelect)
	{
	if (abs(m_curRowY - (m_listUpperLeftY + 4) * 16)>8)
	{
		if (m_curRowY<(m_listUpperLeftY + 4) * 16)
			m_curRowY += 8;
		else
			m_curRowY -= 8;
		if (abs(m_curRowY - (m_listUpperLeftY + 4) * 16)<8)
			m_curRowY = (m_listUpperLeftY + 4) * 16;
		return 0;
	}
	else
		m_curRowY = (m_listUpperLeftY + 4) * 16;
	}
	if (m_bQuit)
	{
		if (m_curScrFade>0)
		{
			m_curScrFade-=6;
			if (m_curScrFade<0)
				m_curScrFade=0;
			return 0;
		}
		else
			return m_quitCode;
	}

	if (m_curScrFade<100)
	{
		m_curScrFade+=6;
		if (m_curScrFade>100)
			m_curScrFade=100;
		return 0;
	}

	m_lastKeyState=m_curKeyState;
	m_curKeyState=CCommonFunctionInput::GetAllKeyState();

	if (m_bEnterNameMode)
	{
		StepEnterNameMode();
		return 0;
	}

	if (CCommonFunctionInput::LeftPressed(m_curKeyState,m_lastKeyState))
	{
			SwitchPage((m_curPage+m_nPage - 1) % m_nPage);
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
	}
	if (CCommonFunctionInput::RightPressed(m_curKeyState,m_lastKeyState))
	{
			SwitchPage((m_curPage+1)%m_nPage);
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
	}
	if (CCommonFunctionInput::UpPressed(m_curKeyState,m_lastKeyState))
	{
		if (m_bStageSelect == false) {
		CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		m_curCursorPos=(m_curCursorPos+m_nFilePerPage-1)%m_nFilePerPage;
		}
		else
		{
			m_curCursorColPos = (m_curCursorColPos + 6) % 7;
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		}

	}
	if (CCommonFunctionInput::DownPressed(m_curKeyState,m_lastKeyState))
	{
		if (m_bStageSelect == false) {
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
			m_curCursorPos = (m_curCursorPos + 1) % m_nFilePerPage;
		}
		else {
			m_curCursorColPos = (m_curCursorColPos + 1) % 7;
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		}
	}
	if (CCommonFunctionInput::ESCPressed(m_curKeyState,m_lastKeyState)
		||CCommonFunctionInput::XPressed(m_curKeyState,m_lastKeyState))
	{
		if (m_bStageSelect == true) {
			m_bStageSelect = false;
		}
		else {
		m_bQuit=true;
		m_quitCode=SELECTREPLAYSCREEN_END_BACK;
		if (!m_bLoadMode)
			m_quitCode=SELECTREPLAYSCREEN_END_SAVE_REPLAY_END;
		}
	}
	if (CCommonFunctionInput::ZPressed(m_curKeyState,m_lastKeyState))
	{
		if (m_bLoadMode)
		{
			CGame::s_pCurGame->m_soundEffect.PlaySound(11);
			if ((m_bStageSelect == false)&& (m_bCurPageRepFileExist[m_curCursorPos]==true))
			{
				m_curCharY = 0;
				m_selectedSlot = m_curCursorPos;
				m_curRowY = (m_listUpperLeftY +4+ m_selectedSlot) * 16;
				m_bStageSelect = true;
			}
			else
			{
				if (m_repInfo[m_curCursorPos].stageFlag[m_curCursorColPos] != 0)
				{
					int fileIdx = m_curPage * m_nFilePerPage + m_curCursorPos;
					char repFileName[1000];
					sprintf(repFileName, "%s%s\\replay%02d.rpy", CGame::GVar().m_workingPath,
						CGame::GVar().m_replaySubDir,
						fileIdx);
					if (CGame::GVar().m_replay.LoadFile(repFileName))
					{
						CGame::GVar().m_bReplayMode = true;
						CGame::GVar().m_playStage = m_curCursorColPos;
						CGame::GVar().OnBeginGame();
						m_bQuit = true;
						m_quitCode = SELECTREPLAYSCREEN_END_SELECTED_REPLAY;

					}
				}
			}
		}
		else
		{
			CGame::s_pCurGame->m_soundEffect.PlaySound(11);
			m_curCharX=0;
			m_curCharY=0;
			m_selectedSlot=m_curCursorPos;
			m_curRowY=(m_listUpperLeftY+4+m_selectedSlot)*16;
			memcpy(m_curEnterName,CGame::GVar().m_defaultReplayName,10);
			m_nameCursorPos=(int)strlen(m_curEnterName);
			if (m_nameCursorPos>7)
				m_nameCursorPos=7;
			m_bEnterNameMode=true;
		}
	}
	return 0;
}

void CSelectReplayScreen::DrawEnterNameMode()
{
	CReplay *pRep=&CGame::GVar().m_replay;
	int x=m_listUpperLeftX*8;
	int y=m_curRowY;
	char strBuf[100];
	for (int i = 0; i<17; i++)
		charTable[0][i] = 0xaa + i;
	for (int i = 0; i<11; i++)
		charTable[1][i] = 0xbb + i;
	charTable[1][11] = 0xd0;
	charTable[1][12] = 0xc9;
	charTable[1][13] = 0xc6;
	charTable[1][14] = 0xc7;
	charTable[1][15] = 0xc8;
	charTable[1][16] = 0xcc;
	for (int i = 0; i<10; i++)
		charTable[2][i] = 0xa0 + i;
	charTable[2][10] = 0x70;
	charTable[2][11] = 0x71;
	charTable[2][12] = 0x72;
	charTable[2][13] = 0xce;
	charTable[2][14] = 0xcf;
	charTable[2][15] = 0xcd;
	charTable[2][16] = 0xd5;
	
	float color[]={1.0f,1.0f,1.0f};
	float sc[]={0.2f,0.2f,0.2f};
	float salpha=0.5f;
	int soffx=2,soffy=2;

	unsigned char numberText[] = { gb_N_,gb_O_,gb_PERIOD,gb_0_, gb_0_, 0 };
	numberText[3] += (m_curPage * m_nFilePerPage + m_selectedSlot) / 10;
	numberText[4] += (m_curPage * m_nFilePerPage + m_selectedSlot) % 10;
	CTh5ExtFont::DrawExtString(numberText, 100, x, y, color[0], color[1], color[2]);
	x += 6 * 16;


	unsigned char playerName[11] = { 0,0,0,0,0,0,0,0,0,0 };
	memcpy(playerName, m_curEnterName, 10);
	CTh5ExtFont::DrawExtString(playerName, 100, x, y, color[0], color[1], color[2]);
	CCommonFunctionGraphic::DrawRectangle((float)x+m_nameCursorPos*16,(float)y+16,(float)x+m_nameCursorPos*16+7,(float)y+17,1,1,1);
	x += 10 * 16;

	{
		time_t tt = time(NULL);
		tm *ptm = localtime(&tt);
		unsigned char dateText[] = { gb_0_, gb_0_,2, gb_0_, gb_0_ ,0 };
		dateText[0] += (ptm->tm_mon + 1) / 10;
		dateText[1] += (ptm->tm_mon + 1) % 10;
		dateText[3] += (ptm->tm_mday) / 10;
		dateText[4] += (ptm->tm_mday) % 10;
		sprintf(strBuf, "/");//this will be changed to fullwidth /
		CTh5ExtFont::DrawExtString(dateText, 100, x, y, color[0], color[1], color[2]);
		CPC98Font::DrawString(strBuf, 100, x + 32, y, color[0], color[1], color[2]);
		x += 6 * 16;
	}
	{
		unsigned char charaName[][10] = { { gb_R_,gb_E_,gb_I_,gb_M_,gb_U_,0 },{ gb_M_,gb_A_,gb_R_,gb_I_,gb_S_,gb_A_,0 },{ gb_M_,gb_I_,gb_M_,gb_A_,0 },{ gb_Y_,gb_U_,gb_K_,gb_A_,0 } };
		CTh5ExtFont::DrawExtString(charaName[pRep->m_playChara], 100, x, y, color[0], color[1], color[2]);
		x += 7 * 16;
	}
	{
		unsigned char difficultyName[][10] = { { gb_E_, gb_A_, gb_S_, gb_Y_ ,0 },{ gb_N_, gb_O_, gb_R_, gb_M_, gb_A_, gb_L_,0 },{ gb_H_, gb_A_, gb_R_, gb_D_,0 },{ gb_L_, gb_U_, gb_N_, gb_A_, gb_T_, gb_I_, gb_C_,0 },{ gb_E_, gb_X_, gb_T_, gb_R_, gb_A_,0 } };
		CTh5ExtFont::DrawExtString(difficultyName[pRep->m_playDifficulty], 100, x, y, color[0], color[1], color[2]);
		x += 8 * 16;
	}


	if (m_curRowY!=(m_listUpperLeftY+4)*16)
		return;

	int ulx=(m_listUpperLeftX+18)*8;
	int uly=(m_listUpperLeftY+12)*16;
	for (int i=0;i<3;i++)
		for (int j=0;j<17;j++)
		{
			int len=1;
			if (i==6&&j==12)
				len=100;
			CTh5ExtFont::DrawExtString(&charTable[i][j],len,ulx+j*16+soffx,uly+i*16+soffy,sc[0],sc[1],sc[2],salpha);
			if (i==m_curCharY&&j==m_curCharX)
			{
				color[0]=1.0f;
				color[1]=1.0f;
				color[2]=0.5f;
			}
			else
			{
				color[0]=0.3f;
				color[1]=0.7f;
				color[2]=0.3f;
			}
			CTh5ExtFont::DrawExtString(&charTable[i][j],len,ulx+j*16,uly+i*16,color[0],color[1],color[2]);
		}
}

void CSelectReplayScreen::Draw()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	if (m_curScrFade == 0)
		return;

	m_pBGImage->Draw(0, 80);
	CCommonFunctionGraphic::DrawRectangle(0, 0, 639, 79, 51.0f / 255.0f, 34.0f / 255.0f, 34.0f / 255.0f);
	
		if (m_bLoadMode)
		{
			unsigned char extLoadReplay[] = { 0xb5,0xb8,0xaa,0xad,0x02,0xbb,0xae,0xb9,0xb5,0xaa,0xc2,0 };
			CTh5ExtFont::DrawExtString(extLoadReplay, 100, (m_listUpperLeftX) * 8 + 4, (m_listUpperLeftY - 2) * 16 + 4, 0, 0, 0, 0.5);
			CTh5ExtFont::DrawExtString(extLoadReplay, 100, (m_listUpperLeftX) * 8, (m_listUpperLeftY - 2) * 16, 1, 1, 1);
		}
		else
		{
			unsigned char extSaveReplay[] = { 0xbc,0xaa,0xbf,0xae,0x02,0xbb,0xae,0xb9,0xb5,0xaa,0xc2,0 };
			CTh5ExtFont::DrawExtString(extSaveReplay, 100, (m_listUpperLeftX) * 8 + 4, (m_listUpperLeftY - 2) * 16 + 4, 0, 0, 0, 0.5);
			CTh5ExtFont::DrawExtString(extSaveReplay, 100, (m_listUpperLeftX) * 8, (m_listUpperLeftY - 2) * 16, 1, 1, 1);
		}

	if (m_bEnterNameMode)
	{
		DrawEnterNameMode();
		return;
	}
	if (m_bStageSelect == false) {
		for (int i = 0; i < m_nFilePerPage; i++)
		{
			int x = m_listUpperLeftX * 8;
			int y = (m_listUpperLeftY + 4 + i) * 16;
			char strBuf[100];

			float color[] = { 118.0f / 255.0f,118.0f / 255.0f,118.0f / 255.0f };
			float sc[] = { 0.2f,0.2f,0.2f };
			float salpha = 0.5f;
			int soffx = 2, soffy = 2;
			if (i == m_curCursorPos)
			{
				color[0] = color[1] = color[2] = 1.0f;
			}
			unsigned char numberText[] = { gb_N_,gb_O_,gb_PERIOD,gb_0_, gb_0_, 0 };
			numberText[3] += (m_curPage * m_nFilePerPage + i) / 10;
			numberText[4] += (m_curPage * m_nFilePerPage + i) % 10;
			CTh5ExtFont::DrawExtString(numberText, 100, x, y, color[0], color[1], color[2]);
			x += 6 * 16;

			if (!m_bCurPageRepFileExist[i])
			{
				char *outInfo = NULL;
				unsigned char errorInfo[] = { gb_BULLET,gb_BULLET ,gb_BULLET ,gb_BULLET ,
											gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET,
											2,2,gb_BULLET ,gb_BULLET ,2,gb_BULLET, gb_BULLET ,
											2,gb_BULLET,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET ,
											2,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET ,gb_BULLET,0 };
				/*char errorInfo[][100] = { "-------- -------------- ------ -------",
									   "          Invalid replay file          ",
									   "    Replay under other game version    ",
									   "      Replay under other mod file      ",
				};
				switch (m_repInfo[i].infoRes)
				{
				case InfoRes_FileNotExist:
					outInfo = errorInfo[0];
					break;
				case InfoRes_InvalidReplay:
					outInfo = errorInfo[1];
					break;
				case InfoRes_GameVersionMismatch:
					outInfo = errorInfo[2];
					break;
				case InfoRes_ModFileMisMatch:
					outInfo = errorInfo[3];
					break;
				}
				CPC98Font::DrawString(outInfo, 100, x, y, color[0], color[1], color[2]);*/
				CTh5ExtFont::DrawExtString(errorInfo, 100, x, y, color[0], color[1], color[2]);
				sprintf(strBuf, "/");//this will be changed to fullwidth /
				CPC98Font::DrawString(strBuf, 100, x + 192, y, color[0], color[1], color[2]);
			}
			else
			{
				unsigned char playerName[9] = { 0,0,0,0,0,0,0,0 };
				memcpy(playerName, m_repInfo[i].playerName, 8);
				playerName[8] = 0;
				CTh5ExtFont::DrawExtString(playerName, 100, x, y, color[0], color[1], color[2]);
				x += 10 * 16;

				{
					time_t tt = (time_t)m_repInfo[i].saveTime;
					tm *ptm = localtime(&tt);
					unsigned char dateText[] = { gb_0_, gb_0_,2, gb_0_, gb_0_ ,0 };
					dateText[0] += (ptm->tm_mon + 1) / 10;
					dateText[1] += (ptm->tm_mon + 1) % 10;
					dateText[3] += (ptm->tm_mday) / 10;
					dateText[4] += (ptm->tm_mday) % 10;
					sprintf(strBuf, "/");//this will be changed to fullwidth /
					CTh5ExtFont::DrawExtString(dateText, 100, x, y, color[0], color[1], color[2]);
					CPC98Font::DrawString(strBuf, 100, x+32, y, color[0], color[1], color[2]);
					x += 6 * 16;
				}
				{
					unsigned char charaName[][10] = { {gb_R_,gb_E_,gb_I_,gb_M_,gb_U_,0},{gb_M_,gb_A_,gb_R_,gb_I_,gb_S_,gb_A_,0},{ gb_M_,gb_I_,gb_M_,gb_A_,0},{ gb_Y_,gb_U_,gb_K_,gb_A_,0 } };
					CTh5ExtFont::DrawExtString(charaName[m_repInfo[i].playChara], 100, x, y, color[0], color[1], color[2]);
					x += 7 * 16;
				}
				{
					unsigned char difficultyName[][10] = { { gb_E_, gb_A_, gb_S_, gb_Y_ ,0}, { gb_N_, gb_O_, gb_R_, gb_M_, gb_A_, gb_L_,0}, { gb_H_, gb_A_, gb_R_, gb_D_,0}, { gb_L_, gb_U_, gb_N_, gb_A_, gb_T_, gb_I_, gb_C_,0}, { gb_E_, gb_X_, gb_T_, gb_R_, gb_A_,0} };
					CTh5ExtFont::DrawExtString(difficultyName[m_repInfo[i].playDifficulty], 100, x, y, color[0], color[1], color[2]);
					x += 8 * 16;
				}


			}
		}
	}
	else if (m_bCurPageRepFileExist[m_curCursorPos] && m_bStageSelect == true)
	{
		char str[100];
		char ss[7][20];
		int x = (m_listUpperLeftX) * 8;
		int y = m_curRowY;
		unsigned char numberText[] = { gb_N_,gb_O_,gb_PERIOD,gb_0_, gb_0_, 0 };
		numberText[3] += (m_curPage * m_nFilePerPage + m_curCursorPos) / 10;
		numberText[4] += (m_curPage * m_nFilePerPage + m_curCursorPos) % 10;
		CTh5ExtFont::DrawExtString(numberText, 100, x, y, 1, 1, 1);
		x += 6 * 16;
		unsigned char playerName[9] = { 0,0,0,0,0,0,0,0 };
		memcpy(playerName, m_repInfo[m_curCursorPos].playerName, 8);
		playerName[8] = 0;
		CTh5ExtFont::DrawExtString(playerName, 100, x, y, 1, 1, 1);
		x += 10 * 16;

		time_t tt = (time_t)m_repInfo[m_curCursorPos].saveTime;
		tm *ptm = localtime(&tt);
		unsigned char dateText[] = { gb_0_, gb_0_,gb_BULLET, gb_0_, gb_0_ ,0 };
		dateText[0] += (ptm->tm_mon + 1) / 10;
		dateText[1] += (ptm->tm_mon + 1) % 10;
		dateText[3] += (ptm->tm_mday) / 10;
		dateText[4] += (ptm->tm_mday) % 10;
		CTh5ExtFont::DrawExtString(dateText, 100, x, y, 1, 1, 1);
		x += 6 * 16;

		unsigned char charaName[][10] = { { gb_R_,gb_E_,gb_I_,gb_M_,gb_U_,0 },{ gb_M_,gb_A_,gb_R_,gb_I_,gb_S_,gb_A_,0 },{ gb_M_,gb_I_,gb_M_,gb_A_,0 },{ gb_Y_,gb_U_,gb_K_,gb_A_,0 } };
		CTh5ExtFont::DrawExtString(charaName[m_repInfo[m_curCursorPos].playChara], 100, x, y, 1, 1,1);
		x += 7 * 16;
		
		unsigned char difficultyName[][10] = { { gb_E_, gb_A_, gb_S_, gb_Y_ ,0 },{ gb_N_, gb_O_, gb_R_, gb_M_, gb_A_, gb_L_,0 },{ gb_H_, gb_A_, gb_R_, gb_D_,0 },{ gb_L_, gb_U_, gb_N_, gb_A_, gb_T_, gb_I_, gb_C_,0 },{ gb_E_, gb_X_, gb_T_, gb_R_, gb_A_,0 } };
		CTh5ExtFont::DrawExtString(difficultyName[m_repInfo[m_curCursorPos].playDifficulty], 100, x, y, 1, 1, 1);
		
		for (int i = 0; i < 7; i++)
		{
			x = (m_listUpperLeftX + 1) * 8;
			//y = (m_listUpperLeftY + 5 + i) * 16;
			y = m_curRowY + (3 + i) * 16;
			if (m_repInfo[m_curCursorPos].stageFlag[i] != 0)
				sprintf(ss[i], "%08d0", m_repInfo[m_curCursorPos].stageScore[i]);
			else
				sprintf(ss[i], "---------");

			if (i == 6)
				sprintf(str, "STAGE EXTRA  %s", ss[i]);
			else
				sprintf(str, "STAGE %d      %s", i + 1, ss[i]);
			if (y <= (m_listUpperLeftY + 13) * 16)
			{
				if (m_curCursorColPos == i)
					CPC98Font::DrawString(str, 100, x, y, 1, 1, 1);
				else
					CPC98Font::DrawString(str, 100, x, y, 118.0f / 255.0f, 118.0f / 255.0f, 118.0f / 255.0f);
			}

		}
	}

	
	CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
	}

}
























