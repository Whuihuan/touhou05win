#include ".\staffroll.h"
#include "../../gameLib/CommonFunction/CommonFunctionInput.h"
#include "../../gameLib/CommonFunction/CommonFunctionGraphic.h"
#include "../../gameLib/CommonFunction/CommonFunctionMusicSE.h"
#include "../Game.h"
#include "../../gameLib/Graphic/PC98Font.h"
#include "../../gameLib/Graphic/Th5ExtFont.h"
#include <time.h>
namespace th5w{

CStaffRoll::CStaffRoll(void)
{
}

CStaffRoll::~CStaffRoll(void)
{
}

void CStaffRoll::Initialize()
{
	m_curScrFade=100;
	m_curFrame=0;
	m_bQuit = false;

	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf00.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf01.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf02.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf03.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf04.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf05.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf06.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf07.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf08.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf09.CDG", 0);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf10.CDG", 0);
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"stf01.BFT",0);
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"stf00.BFT",0);
	
	CGame::s_pCurGame->m_fpsLimit=26;
	
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
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);


	if (m_curScrFade == 0)
		return;
	char strbuf[1000];
	sprintf(strbuf, "%d", m_curFrame);
	CPC98Font::DrawString(strbuf, 100, 320, 32, 1, 1, 1,1);

	CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);
	int m_playAreaUpperLeftY=10;
	int m_playAreaUpperLeftX=11;
	CCommonFunctionGraphic::DrawRectangle(0,0,639,(float)m_playAreaUpperLeftY-1,0,0,0);
	CCommonFunctionGraphic::DrawRectangle(0,(float)m_playAreaUpperLeftY+368,639,479,0,0,0);
	CCommonFunctionGraphic::DrawRectangle(0,0,(float)m_playAreaUpperLeftX-1,479,0,0,0);
	CCommonFunctionGraphic::DrawRectangle((float)m_playAreaUpperLeftX+384,0,639,479,0,0,0);
	
	if(m_curFrame<=76){
		m_spriteArray.GetImagePtr(1)->Draw(528, 240);
		m_spriteArray.GetImagePtr(0)->Draw(464, 192);
	}
	else if(m_curFrame<=92){
		m_spriteArray.GetImagePtr(2)->Draw(464, 200);
	}
	else if(m_curFrame<=120){
		m_spriteArray.GetImagePtr(4)->Draw(464, 0xE0);
		m_spriteArray.GetImagePtr(3)->Draw(464, 200);
	}
	else if(m_curFrame<=0xAC){
		m_spriteArray.GetImagePtr(5)->Draw(0xB0, 0xC8);
	}
	else if(m_curFrame<=0xBC)
	{
		m_spriteArray.GetImagePtr(6)->Draw(0xB0, 0xc8);
	}
	else if(m_curFrame<=0xCC)
	{
		m_spriteArray.GetImagePtr(7)->Draw(0xB0, 0xc8);
	}
	else if(m_curFrame<=0xDC)
	{
		m_spriteArray.GetImagePtr(8)->Draw(0xB0, 0xc8);
	}
	else if(m_curFrame<=0xEC)
	{
		m_spriteArray.GetImagePtr(9)->Draw(0xB0, 0xc8);
	}
	else if(m_curFrame<=0xF9)
	{
		m_spriteArray.GetImagePtr(10)->Draw(0xB0, 0x170);
	}
}

}



















