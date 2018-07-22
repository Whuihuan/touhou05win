#pragma once
#include "../scheme.h"
#include "../../gameLib/Graphic/2DImageArray.h"

#define PLAYRESULTSCREEN_END 1
#define PLAYRESULTSCREEN_SKIPPED 2


#define RESULT_NOMAL 0
#define RESULT_CLEAR 1
#define RESULT_CLEAR_CONTINUE 2
#define RESULT_CLEAR_EXTRA 3

namespace th5w{

class CPlayResultScreen : public CScheme
{
protected:
	bool m_bLoadMode;
	int m_curFrame;
	unsigned short m_lastKeyState,m_curKeyState;

protected:
	int m_listUpperLeftX;
	int m_listUpperLeftY;

	C2DImage *m_pBGImage;


	int m_curScrFade;
	bool m_bQuit;
	int m_quitCode;

	void DrawNumber(int numX,int numY,int number,int nDigit,bool leadingZero,bool rightAlign,float colorR,float colorG,float colorB, int dotpos=0);
	int  CalcPercent(int value, int MaxValue, bool unk116EA=false);
	int m_ResultType;

public:
	void Initialize(bool bSwitchMusic, int ResultType);
	void InitializeValue(int ResultType);
	void DrawResult(int x, int y,int type);
	int  Step();
	void Draw();

	int m_Difficulty;
	int m_Score;
	int m_nMiss;
	int m_nBomb;
	int m_nGameAchivement;
	int m_nExorcism;
	int m_nItemCollect;
	int m_nItemHighCollect;
	int m_nfocus;
	int m_nSlowDown;
	int m_ability;
	
	int m_nUnk15182;
	int m_nUnk1517E;
	char m_comment_text[2][30];
	
public:
	CPlayResultScreen(void);
	~CPlayResultScreen(void);
};

}
