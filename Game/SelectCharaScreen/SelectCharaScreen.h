#pragma once
#include "../scheme.h"
#include "../../gameLib/Graphic/2DImageArray.h"

#define SELECTCHARASCREEN_END_SELECTED_CHARA 1
#define SELECTCHARASCREEN_END_BACK 2

namespace th5w{

class CSelectCharaScreen : public CScheme
{
protected:
	bool m_bCharaSelectable[4];
	int m_charaDisplayImg[4];
	bool m_bCharaClearFlag[4];

	unsigned char m_palette[48];

protected:
	int m_curScrFade;
	int m_cursorPos;
	int m_cursorstage;
protected:
	C2DImageArray m_spriteArray;
	C2DImage *m_pBGImage;
	C2DImage *m_pExtendBgImg;
	
protected:
	bool m_bQuit;
	int m_quitCode;

	unsigned short m_lastKeyState;

public:
	void Initialize();
	virtual int Step();
	void Draw();
	int m_curMenu;			//1 for char select, 1 for stage select

protected:
	void ParseKeyEvent();

public:
	CSelectCharaScreen(void);
	virtual ~CSelectCharaScreen(void);
};

}