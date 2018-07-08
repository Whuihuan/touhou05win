#include ".\staffroll.h"
#include "../../gameLib/CommonFunction/CommonFunctionGraphic.h"
#include "../Game.h"
#include "../../gameLib/Graphic/PC98Font.h"
#include "../../gameLib/Graphic/Th5ExtFont.h"
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

	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf00.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf01.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf02.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf03.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf04.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf05.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf06.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf07.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf08.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf09.CDG", m_palette);
	CCommonFunctionGraphic::LoadCD2CDGAllSpriteFromDat(&m_spriteArray, &CGame::s_pCurGame->m_th5Dat1, "stf10.CDG", m_palette);
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"stf01.BFT",0);
	CCommonFunctionGraphic::LoadBFTAllPatternFromDat(&m_patternArray,NULL,&CGame::s_pCurGame->m_th5Dat1,"stf00.BFT",0);
	
	
}

int CStaffRoll::Step()
{
	m_curScrFade=m_curFrame+64;
	{
		if (m_curScrFade>100)
			m_curScrFade=100;
	}
	//if (m_curFrame==64)
		//return 1;
	return 0;
}

void CStaffRoll::Draw()
{
	glClearColor(m_palette[3]/255.0f,m_palette[4]/255.0f,m_palette[5]/255.0f,1);
	glClear(GL_COLOR_BUFFER_BIT);


	if (m_curScrFade == 0)
		return;
	char strbuf[1000];
	sprintf(strbuf, "%d", m_curFrame);
	CPC98Font::DrawString(strbuf, 100, 320, 32, 1, 1, 1,1);

	CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);

	m_curFrame++;
	//CCommonFunctionGraphic::DrawRectangle(0,0,639,(float)m_playAreaUpperLeftY-1,0,0,0);
	//CCommonFunctionGraphic::DrawRectangle(0,(float)m_playAreaUpperLeftY+368,639,479,0,0,0);
	//CCommonFunctionGraphic::DrawRectangle(0,0,(float)m_playAreaUpperLeftX-1,479,0,0,0);
	//CCommonFunctionGraphic::DrawRectangle((float)m_playAreaUpperLeftX+384,0,639,479,0,0,0);
}

}



















