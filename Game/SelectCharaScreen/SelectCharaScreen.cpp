#include ".\selectcharascreen.h"
#include "../Game.h"
#include "../../gameLib/CommonFunction/CommonFunctionMusicSE.h"
#include "../../gameLib/CommonFunction/CommonFunctionInput.h"
#include "../../gameLib/CommonFunction/CommonFunctionGraphic.h"
#include "../../gameLib/Graphic/2DImageArray.h"
#include "../../gameLib/Graphic/PC98Font.h"
#include "../../gameLib/Graphic/Th5ExtFont.h"
namespace th5w {

	CSelectCharaScreen::CSelectCharaScreen(void)
	{
		m_pExtendBgImg = NULL;
	}

	CSelectCharaScreen::~CSelectCharaScreen(void)
	{
		if (m_pBGImage != NULL)
			m_pBGImage->Destroy();
		m_pBGImage = NULL;
		if (m_pExtendBgImg != NULL)
			m_pExtendBgImg->Destroy();
		m_pExtendBgImg = NULL;
	}

	void CSelectCharaScreen::Initialize()
	{
		m_bQuit = false;
		m_quitCode = 0;
		m_lastKeyState = 0;
		m_curMenu = 0;
		m_cursorPos = 0;

		m_difficulty = CGame::GVar().m_playDifficulty;
		for (int i = 0; i < 4; i++)
			m_bCharaClearFlag[i] = CGame::GVar().m_bClear[i][m_difficulty];
		
		if (m_difficulty != 4)
			for (int i = 0; i < 4; i++)
				m_bCharaSelectable[i] = true;
		else
			for (int i = 0; i < 4; i++)
				m_bCharaSelectable[i] = CGame::GVar().m_bExtraPlayable[i];
		
		for (int i = 0; i < 4; i++)
			if (m_bCharaSelectable[i])
				m_charaDisplayImg[i] = i;
			else
				m_charaDisplayImg[i] = 4;
		
		for (int i = 0; i < 4; i++)
				m_nPracticeEnableStage[i] = CGame::GVar().m_nPracticeEnableStage[i][m_difficulty];

		unsigned char pc[] = { 0,0,0 };
		CCommonFunctionGraphic::LoadBinaryImageFile(&m_pExtendBgImg, pc, "selectbg.bmp");


		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, m_palette, &CGame::s_pCurGame->m_th5Dat1, "SLB1.PI");

		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SL00.CDG", m_palette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SL01.CDG", m_palette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SL02.CDG", m_palette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SL03.CDG", m_palette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SL04.CDG", m_palette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "SLCL.CDG", m_palette);

		m_curScrFade = 0;
	}

	int CSelectCharaScreen::Step()
	{
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
		if (m_curScrFade > 100)
		{
			m_curScrFade -= 6;
			if (m_curScrFade < 100)
				m_curScrFade = 100;
			return 0;
		}
		ParseKeyEvent();

		return 0;
	}

	void CSelectCharaScreen::Draw()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		if (m_pExtendBgImg != NULL)
		{
			m_pExtendBgImg->DrawColorScaled((float)0, (float)0, 0.33203125f, 0.1328125f, 0.33203125f);
			m_pExtendBgImg->DrawColorScaled((float)0, (float)400, 0.33203125f, 0.1328125f, 0.33203125f);

		}
		m_pBGImage->Draw(0, 40);


		float colornotplayable[] = { 0.4f,0.4f,0.4f };
		float colorselect[] = { 1.0f,1.0f,0.0f };
		float color[] = { 1.0f,1.0f,1.0f };
		float salpha = 0.5f;

		char strBuf[100];
		int charaX[] = { 16,272,160,400 };
		int charaY[] = { 48 + 40,48 + 40,224 + 40,224 + 40 };
		int tempscore = 0;
			for (int i = 0; i < 4; i++)
			{
				if (m_cursorPos == i)
				{
					CCommonFunctionGraphic::DrawRectangle((float)charaX[i], (float)charaY[i],
						(float)charaX[i] + m_spriteArray.GetImagePtr(m_charaDisplayImg[i])->m_width - 1,
						(float)charaY[i] + m_spriteArray.GetImagePtr(m_charaDisplayImg[i])->m_height - 1, 0, 0, 0);
					m_spriteArray.GetImagePtr(m_charaDisplayImg[i])->Draw((float)charaX[i] - 8, (float)charaY[i] - 8);
					if (m_bCharaClearFlag[i])
						m_spriteArray.GetImagePtr(5)->Draw((float)charaX[i] - 8 + 160, (float)charaY[i] - 8 + 144);
				}
				else
				{
					m_spriteArray.GetImagePtr(m_charaDisplayImg[i])->DrawColorScaled((float)charaX[i], (float)charaY[i], 0.5, 0.5, 0.5);
					if (m_bCharaClearFlag[i])
						m_spriteArray.GetImagePtr(5)->DrawColorScaled((float)charaX[i] + 160, (float)charaY[i] + 144, 0.5, 0.5, 0.5);
				}
			}
		
		if (m_curMenu == 1)
		{

			CCommonFunctionGraphic::DrawRectangle(320.0f-96.0f, 240.0f-120.0f,320.0f+96.0f,240.0f+120.0f,0, 0, 0,0.5f);
			for (int i = 0; i <m_nPracticeEnableStage[m_cursorPos]+1; i++)
			{
				sprintf(strBuf, "Stage %01d %07d0", i + 1, CGame::GVar().m_practiceHighScore[m_cursorPos][m_difficulty][i]);
				if (i == m_cursorstage) {
				CPC98Font::DrawString(strBuf, 100, 320.0f-96.0f, 240.0f-120.0f + 32 * i, colorselect[0], colorselect[1], colorselect[2]);
				}
				else {
				CPC98Font::DrawString(strBuf, 100, 320.0f-96.0f, 240.0f-120.0f + 32 * i, color[0], color[1], color[2]);
				}
				
			}
		}


		CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
	}

	void CSelectCharaScreen::ParseKeyEvent()
	{
		unsigned short curState = CCommonFunctionInput::GetAllKeyState();
		if (m_curMenu == 0)
		{
			if (CCommonFunctionInput::LeftPressed(curState, m_lastKeyState) || CCommonFunctionInput::RightPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(16);
				m_cursorPos = m_cursorPos / 2 * 2 + (1 - m_cursorPos % 2);
				m_lastKeyState = curState;
				return;
			}
			if (CCommonFunctionInput::UpPressed(curState, m_lastKeyState) || CCommonFunctionInput::DownPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(16);
				m_cursorPos = m_cursorPos % 2 + (2 - m_cursorPos + m_cursorPos % 2);
				m_lastKeyState = curState;
				return;
			}
			if (CCommonFunctionInput::ZPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(11);
				if (m_bCharaSelectable[m_cursorPos] == true)
				{
					CGame::GVar().m_playChara = m_cursorPos;
					if (CGame::GVar().m_bPracticeMode == true)
					{
						if(m_nPracticeEnableStage[m_cursorPos]!=-1)
						{
							m_curMenu = 1;
							m_cursorstage = 0;
						}
					}
					else
					{
						CGame::GVar().OnBeginGame();
						m_bQuit = true;
						m_quitCode = SELECTCHARASCREEN_END_SELECTED_CHARA;
					}
				}
				m_lastKeyState = curState;
				return;
			}
			if (CCommonFunctionInput::ESCPressed(curState, m_lastKeyState) || CCommonFunctionInput::XPressed(curState, m_lastKeyState))
			{
				m_bQuit = true;
				m_quitCode = SELECTCHARASCREEN_END_BACK;
				m_lastKeyState = curState;
				return;
			}

			m_lastKeyState = curState;
			return;
		}
		else if (m_curMenu == 1)
		{
			if (CCommonFunctionInput::UpPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(16);
				m_cursorstage = (m_cursorstage + m_nPracticeEnableStage[m_cursorPos]) %
									(m_nPracticeEnableStage[m_cursorPos]+1);
				m_lastKeyState = curState;
				return;
			}
			if (CCommonFunctionInput::DownPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(16);
				m_cursorstage = (m_cursorstage + 1) % (m_nPracticeEnableStage[m_cursorPos]+1);
				m_lastKeyState = curState;				
				return;
			}
			if (CCommonFunctionInput::ZPressed(curState, m_lastKeyState))
			{
				CCommonFunctionMusicSE::PlaySe(11);
				if (m_cursorstage<=m_nPracticeEnableStage[m_cursorPos])
				{
					CGame::GVar().m_playStage = m_cursorstage;
					CGame::GVar().OnBeginGame();
					m_bQuit = true;
					m_quitCode = SELECTCHARASCREEN_END_SELECTED_CHARA;
					m_lastKeyState = curState;
				}
				return;
			}
			if (CCommonFunctionInput::ESCPressed(curState, m_lastKeyState) || CCommonFunctionInput::XPressed(curState, m_lastKeyState))
			{

				m_curMenu = 0;
				m_lastKeyState = curState;
				m_curScrFade = 0;
				return;
			}

			m_lastKeyState = curState;
			return;
		}
	}

}
