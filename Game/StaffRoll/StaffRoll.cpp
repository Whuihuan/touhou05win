#include ".\staffroll.h"
#include "../../gameLib/CommonFunction/CommonFunctionInput.h"
#include "../../gameLib/CommonFunction/CommonFunctionGraphic.h"
#include "../../gameLib/CommonFunction/CommonFunctionMusicSE.h"
#include "../Game.h"
#include "../../gameLib/Graphic/PC98Font.h"
#include "../../gameLib/Graphic/Th5ExtFont.h"
#include <time.h>
unsigned char stfpalette[48] = {
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x70, 0x70,
	0x50, 0xC0, 0xC0,
	0x00, 0x00, 0x50,
	0xA0, 0x20, 0x20,
	0x00, 0x00, 0x60,
	0x10, 0x10, 0x70,
	0x30, 0x30, 0x80,
	0x50, 0x50, 0x90,
	0x70, 0x70, 0xB0,
	0x90, 0x90, 0xC0,
	0xB0, 0xB0, 0xD0,
	0xD0, 0xD0, 0xF0,
	0xA0, 0xE0, 0xB0,
	0xF0, 0xF0, 0xF0
};

int m_playAreaUpperLeftY = 10 + 40;
int m_playAreaUpperLeftX = 11;
int m_playAreaBottomRightY = 0x170 + 40;
int m_playAreaBottomRightX = 140;
namespace th5w {

	CStaffRoll::CStaffRoll(void)
	{
	}

	CStaffRoll::~CStaffRoll(void)
	{
	}

	void CStaffRoll::Initialize()
	{
		m_curScrFade = 100;
		m_curFrame = 0;
		m_bQuit = false;

		m_playAreaUpperLeftY = 10 + 40;
		m_playAreaUpperLeftX = 11;
		m_playAreaBottomRightY = 0x170 + 40;
		m_playAreaBottomRightX = 639 - 11;

		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf00.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf01.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf02.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf03.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf04.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf05.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf06.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf07.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf08.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf09.CDG", stfpalette);
		CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf10.CDG", stfpalette);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "stf01.BFT", 0);
		CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray, NULL, &CGame::s_pCurGame->m_th5Dat1, "stf00.BFT", 0);
		CGame::s_pCurGame->SetVSYNC(true);

		CGame::s_pCurGame->m_fpsLimit = 58;
		CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1, "STAFF");
		th5w::CCommonFunctionMusicSE::Play();

	}

	int CStaffRoll::Step()
	{
		if (m_curScrFade < 100)
		{
			m_curScrFade += 2;
			if (m_curScrFade > 100)
				m_curScrFade = 100;
			return 0;
		}
		//if (m_curFrame==64)
		//return 1;
		return 1;
	}

	void CStaffRoll::Draw()
	{
		m_curFrame++;
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		if (m_curScrFade == 0)
			return;
		char strbuf[1000];
		sprintf(strbuf, "%d", m_curFrame);
		CPC98Font::DrawString(strbuf, 100, 320, 32, 1, 1, 1, 1);

		CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
		CCommonFunctionGraphic::DrawRectangle(0, 0, 639, (float)m_playAreaUpperLeftY - 1, 0, 0, 0);
		CCommonFunctionGraphic::DrawRectangle(0, (float)m_playAreaBottomRightY, 639, 479, 0, 0, 0);
		CCommonFunctionGraphic::DrawRectangle(0, 0, (float)m_playAreaUpperLeftX - 1, 479, 0, 0, 0);
		CCommonFunctionGraphic::DrawRectangle((float)m_playAreaBottomRightX, 0, 639, 479, 0, 0, 0);

		//todo: centralize image
		//      and figure out actual timing of //?
		//      and square bullet pattern... etc
		if (m_curFrame <= 40 * 16)//?
		{

		}
		else if (m_curFrame <= 50 * 16)//?
		{
			m_playAreaBottomRightX -= 4;
		}
		else if (m_curFrame <= 76 * 16)
		{
			m_spriteArray.GetImagePtr(1)->Draw(224, 240);
			m_spriteArray.GetImagePtr(0)->Draw(160, 192);
			/*m_playAreaUpperLeftY = 10 + 40;*/
			/*m_playAreaUpperLeftX = 11;*/
			/*m_playAreaBottomRightY = 0x170 + 40;*/
			m_playAreaBottomRightX = 0;
		}
		else if (m_curFrame <= 92 * 16)
		{
			m_spriteArray.GetImagePtr(2)->Draw(160, 200);
		}
		else if (m_curFrame <= 120 * 16)
		{
			m_spriteArray.GetImagePtr(4)->Draw(160, 0xE0);
			m_spriteArray.GetImagePtr(3)->Draw(160, 200);
		}
		else if (m_curFrame <= (0xAC - 38) * 16)//?
		{
			m_playAreaUpperLeftX+=4;
			m_playAreaBottomRightX += 4;
		}
		else if (m_curFrame <= 0xAC * 16)
		{
			m_playAreaUpperLeftY = 10 + 40;
			m_playAreaUpperLeftX = 639;
			m_playAreaBottomRightY = 0x170 + 40;
			m_playAreaBottomRightX = 639;
			m_spriteArray.GetImagePtr(5)->Draw(0xB0, 0xC8);
		}
		else if (m_curFrame <= 0xBC * 16)
		{
			m_spriteArray.GetImagePtr(6)->Draw(0xB0, 0xc8);
		}
		else if (m_curFrame <= 0xCC * 16)
		{
			m_spriteArray.GetImagePtr(7)->Draw(0xB0, 0xc8);
		}
		else if (m_curFrame <= 0xDC * 16)
		{
			m_spriteArray.GetImagePtr(8)->Draw(0xB0, 0xc8);
		}
		else if (m_curFrame <= 0xEC * 16)
		{
			m_spriteArray.GetImagePtr(9)->Draw(0xB0, 0xc8);
		}
		else if (m_curFrame <= 0xF9 * 16)
		{
			m_spriteArray.GetImagePtr(10)->Draw(0xB0, 0x170);
		}
		//after this, we should draw skill verdict(playresult)
		//it would be great to use CPlayResultScreen::DrawResult
		//But this is possible?
	}

}



















