#pragma once
#include "../scheme.h"
#include <windows.h>
//#include "../../gameLib/Graphic/2DImage.h"
#include "../../gameLib/Graphic/2DImageArray.h"

namespace th5w{

class CStaffRoll : public CScheme
{
protected:
	int m_curScrFade;
	int m_curFrame;
	C2DImageArray m_spriteArray;
	C2DImageArray m_patternArray;
	unsigned char m_palette[48];
	int m_playAreaUpperLeftY;
	int m_playAreaUpperLeftX;
	int m_playAreaBottomRightY;
	int m_playAreaBottomRightX;

public:
	void Initialize();
	int Step();
	void Draw();
	bool m_bQuit;
	int m_quitCode;


public:
	CStaffRoll(void);
	~CStaffRoll(void);
};

}
