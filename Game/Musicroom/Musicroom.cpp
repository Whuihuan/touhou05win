#include ".\MusicRoom.h"
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
//#define SEL_QUIT TRACK_COUNT + 1
#define MUSIC_POLYGONS 16

namespace th5w {
	char MusicRoom_TH[][36] = { "   ‘æ‚P’e?“Œ•ûèËˆÙ?  Arrange ver  ",
								"   ‘æ‚Q’e?“Œ•û••–‚?  Special MIX  ",
								"   ‘æ‚R’e?“Œ•û–²Žž‹ó  Special MIX  ",
								"   ‘æ‚S’e?“Œ•ûŒ¶‘z‹½  Special MIX  ",
								"   ‘æ‚T’e?“Œ•û‰ö?’k MysticSquare  " };
	CMusicRoom::CMusicRoom(void)
	{
		m_pBGImage = NULL;
		m_bEnterNameMode = false;
	}

	CMusicRoom::~CMusicRoom(void)
	{
		if (m_pBGImage)
			m_pBGImage->Destroy();
		m_pBGImage = NULL;
	}

	void CMusicRoom::Initialize(bool bLoadMode, bool bSwitchMusic)
	{
		//make sure replay sub directory exists
		TCHAR subdir[1000];
		wsprintf(subdir, _T("%S%S\\"), CGame::GVar().m_workingPath,
			CGame::GVar().m_replaySubDir);
		if (::PathFileExists(subdir) == FALSE)
			::CreateDirectory(subdir, NULL);

		m_curFrame = 0;
		m_lastKeyState = 0;
		m_curKeyState = 0;
		m_bQuit = false;
		m_curScrFade = 0;

		m_bLoadMode = bLoadMode;
		m_nFilePerPage = 20;
		m_nPage = 5;
		m_listUpperLeftX = 10;
		m_listUpperLeftY = 4;
		SwitchPage(4);
		m_curCursorPos = 0;
		m_curCursorColPos = 0;

		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, NULL, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_shineArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN01.BFT", 0);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_shineArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "ZUN02.BFT", 0);

		if (bSwitchMusic)
		{
			if (bLoadMode)
				CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1, "OP");
			else
				CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1, "NAME");
			th5w::CCommonFunctionMusicSE::Play();
		}
	}

	void CMusicRoom::SwitchPage(int pageIdx)
	{
		m_curPage = pageIdx;
		char strBuf[100];
		float color[] = { 1.0f,1.0f,1.0f };
		float salpha = 0.5f;
		sprintf(strBuf, "%s", MusicRoom_TH[pageIdx]);
		CPC98Font::DrawString(strBuf, 100, 160, 128, color[0], color[1], color[2]);
	}


	int CMusicRoom::Step()
	{
		m_curFrame++;

		if (m_bQuit)
		{
			if (m_curScrFade > 0)
			{
				m_curScrFade -= 6;
				if (m_curScrFade < 0)
					m_curScrFade = 0;
				return 0;
			}
			else
				return m_quitCode;
		}

		if (m_curScrFade < 100)
		{
			m_curScrFade += 6;
			if (m_curScrFade > 100)
				m_curScrFade = 100;
			return 0;
		}

		m_lastKeyState = m_curKeyState;
		m_curKeyState = CCommonFunctionInput::GetAllKeyState();


		if (CCommonFunctionInput::LeftPressed(m_curKeyState, m_lastKeyState))
		{
			SwitchPage((m_curPage + m_nPage - 1) % m_nPage);
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		}
		if (CCommonFunctionInput::RightPressed(m_curKeyState, m_lastKeyState))
		{
			SwitchPage((m_curPage + 1) % m_nPage);
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
		}
		if (CCommonFunctionInput::UpPressed(m_curKeyState, m_lastKeyState))
		{
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
			m_curCursorPos = (m_curCursorPos + m_nFilePerPage - 1) % m_nFilePerPage;
		}
		if (CCommonFunctionInput::DownPressed(m_curKeyState, m_lastKeyState))
		{
			CGame::s_pCurGame->m_soundEffect.PlaySound(1);
			m_curCursorPos = (m_curCursorPos + 1) % m_nFilePerPage;
		}
		if (CCommonFunctionInput::ESCPressed(m_curKeyState, m_lastKeyState)
			|| CCommonFunctionInput::XPressed(m_curKeyState, m_lastKeyState))
		{
			m_bQuit = true;
			m_quitCode = MUSICROOM_END_BACK;
		}
		if (CCommonFunctionInput::ZPressed(m_curKeyState, m_lastKeyState))
		{

			CGame::s_pCurGame->m_soundEffect.PlaySound(11);
			m_curCharX = 0;
			m_curCharY = 0;
			m_selectedSlot = m_curCursorPos;
			m_curRowY = (m_listUpperLeftY + m_selectedSlot) * 16;
			memcpy(m_curEnterName, CGame::GVar().m_defaultReplayName, 10);
			m_nameCursorPos = (int)strlen(m_curEnterName);
			if (m_nameCursorPos > 7)
				m_nameCursorPos = 7;
			m_bEnterNameMode = true;

		}
		return 0;
	}

	void CMusicRoom::Draw()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		if (m_curScrFade == 0)
			return;

		m_pBGImage->Draw(0, 80);

		for (int i = 0; i < m_nFilePerPage; i++)
		{
			int x = m_listUpperLeftX * 8;
			int y = (m_listUpperLeftY + i) * 16;
			char strBuf[100];

			float color[] = { 0.5f,1.0f,0.5f };
			float sc[] = { 0.2f,0.2f,0.2f };
			float salpha = 0.5f;
			int soffx = 2, soffy = 2;
			if (i == m_curCursorPos)
			{
				color[0] = color[1] = 1;
				x -= 1; y -= 1;
			}

			sprintf(strBuf, "No.%02d ", m_curPage*m_nFilePerPage + i);
			CPC98Font::DrawString(strBuf, 100, x + soffx, y + soffy, sc[0], sc[1], sc[2], salpha);
			CPC98Font::DrawString(strBuf, 100, x, y, color[0], color[1], color[2]);
			x += 6 * 8;

			if (!m_bCurPageRepFileExist[i])
			{
				char *outInfo = NULL;
				char errorInfo[][100] = { "-------- -------------- ------ ------- - - - - - - --",
					"          Invalid replay file          - - - - - - --",
					"    Replay under other game version    - - - - - - --",
					"      Replay under other mod file      - - - - - - --",
				};
				CPC98Font::DrawString(outInfo, 100, x + soffx, y + soffy, sc[0], sc[1], sc[2], salpha);
				CPC98Font::DrawString(outInfo, 100, x, y, color[0], color[1], color[2]);
			}
			else
			{
				x += 15 * 8;
			}

			{
				char charaName[][10] = { "Reimu","Marisa","Mima","Yuka" };
			}
			if (i == m_curCursorPos && m_bLoadMode)
			{
				x = (m_listUpperLeftX + 45) * 8 + m_curCursorColPos * 16 + 4 - 1;
				if (m_curCursorColPos == 6)
					x += 4;
				y += 8;		//no need to minus 1, as the original y already has 1 minused
				int imgIdx = 1;
				C2DImage *pImg = m_shineArray.GetImagePtr(imgIdx);
				float angle = ((float)(m_curFrame % 64) / 64.0f)*(float)PI*2.0f;
				float radius = fabs(8.0f - (float)(m_curFrame % 64) / 4.0f);
				float alpha = 0.5f + radius / 16.0f;
				radius += 4.0f;
				pImg->Draw((float)x - pImg->m_width / 2 + (float)cos(angle)*radius, (float)y - pImg->m_height / 2 + (float)sin(angle)*radius, alpha);
				angle += (float)PI;
				pImg->Draw((float)x - pImg->m_width / 2 + (float)cos(angle)*radius, (float)y - pImg->m_height / 2 + (float)sin(angle)*radius, alpha);

				pImg = m_shineArray.GetImagePtr(imgIdx + 8);
				angle += (float)PI / 2.0f;
				pImg->Draw((float)x - pImg->m_width / 2 + (float)cos(angle)*radius, (float)y - pImg->m_height / 2 + (float)sin(angle)*radius, alpha);
				angle += (float)PI;
				pImg->Draw((float)x - pImg->m_width / 2 + (float)cos(angle)*radius, (float)y - pImg->m_height / 2 + (float)sin(angle)*radius, alpha);
			}
		}
		if (m_bCurPageRepFileExist[m_curCursorPos])
		{
			char str[100];
			char ss[7][20];
		}

	}
}





















