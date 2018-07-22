#include ".\playresultscreen.h"
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

namespace th5w {
#include ".\PlayResultScreen_Text.cpp"
	CPlayResultScreen::CPlayResultScreen(void)
	{
		m_pBGImage = NULL;

	}

	CPlayResultScreen::~CPlayResultScreen(void)
	{
		if (m_pBGImage)
			m_pBGImage->Destroy();
		m_pBGImage = NULL;
	}
	void CPlayResultScreen::InitializeValue(int ResultType)
	{
		m_ResultType = ResultType;
		m_Difficulty = CGame::GVar().m_playDifficulty;
		m_Score = CGame::GVar().m_curScore;
		m_nMiss = 0;
		m_nBomb = 0;

		if (CGame::GVar().m_playStage == 6)
		{
			if (m_ResultType == RESULT_CLEAR_EXTRA)
				CGame::GVar().m_nBX2C = 12800;
			m_nGameAchivement = CalcPercent(CGame::GVar().m_nBX2C, 12800) / 100;
		}
		else
		{
			if ((m_ResultType == RESULT_CLEAR) || (m_ResultType == RESULT_CLEAR_CONTINUE))
				CGame::GVar().m_nBX2C = 46000;
			m_nGameAchivement = CalcPercent(CGame::GVar().m_nBX2C, 46000) / 100;
		}

		m_nExorcism = CalcPercent(CGame::GVar().m_nBX38, CGame::GVar().m_nBX36) / 100;
		m_nItemCollect = CalcPercent(CGame::GVar().m_nBX30, CGame::GVar().m_nBX2E) / 100;
		m_nItemHighCollect = CalcPercent(CGame::GVar().m_nBX34, CGame::GVar().m_nBX32) / 100;
		//need to find m_nFocus
		m_nSlowDown = CalcPercent(CGame::GVar().m_nBX3C / 10, CGame::GVar().m_nBX40 / 10, true) / 100;
		m_nUnk15182 = 0;
		m_ability = 0;
		m_ability = m_ability / 12 + m_nUnk15182;

		/****************************************/
		/*left over of th04                     */
		/*th04  th05                            */
		/*24	4B                              */
		/*23	4A                              */
		/*these values never changed in th05    */
		/****************************************/
		/*
		if(CGame::GVar().m_nBX4B>=10)
			m_ability=m_ability+500000;
		else
		m_ability=m_ability+CGame::GVar().m_nBX4A*5000+CGame::GVar().m_nBX4B*5000;
		*/

		int totalScore = 0;
		switch (m_Difficulty)
		{
		case 0:
			m_ability -= 50000;
			totalScore = 800000;
			break;
		case 1:
			totalScore = 1000000;
			break;
		case 2:
			m_ability = (m_ability * 5) / 4;
			m_ability += 150000;
			totalScore = 1200000;
			break;
		case 3:
			m_ability = (m_ability * 3) / 2;
			m_ability += 300000;
			totalScore = 1400000;
			break;
		case 4:
			m_ability = (m_ability * 3) / 2;
			m_ability += 250000;
			totalScore = 2000000;
			break;

		}

		int temp = CGame::GVar().m_nInitLife;//it looks like life on continue, not life
		switch (temp)
		{
		case 1:
			m_ability += 50000;
			totalScore += 100000;
			break;
		case 2:
			m_ability += 25000;
			totalScore += 50000;
			break;
		case 3:
			break;
		case 4:
			totalScore -= 25000;
			break;
		case 5:
			totalScore -= 50000;
			break;
		case 6:
			totalScore -= 75000;
			break;
		}

		if (CGame::GVar().m_nInitBomb == 0) {
			m_ability += 50000;
			totalScore += 100000;
		}
		else if (CGame::GVar().m_nInitBomb == 1) {
			m_ability += 30000;
			totalScore += 50000;
		}
		else if (CGame::GVar().m_nInitBomb == 2) {
			m_ability += 20000;
			totalScore += 25000;
		}
		/*
		if(CGame::GVar().m_nBX16==0){
			m_ability-=200000
			totalScore-=100000
		}*/

		if (m_nMiss >= 10)
			m_ability -= 300000;
		else
			m_ability -= m_nMiss * 30000;

		if (m_nBomb >= 15)
			m_ability -= 225000;
		else
			m_ability -= m_nBomb * 15000;


		if (m_ResultType == 0)
			m_ability = m_ability * 7 / 8;

		if (m_ability < 0)
			m_ability = 0;
		else if (m_ability > totalScore)
			m_ability = totalScore;

		//	if(([bx+40h]>>1)>[bx+3Ch])
			//jbe	loc_D120
	//		if(m_ability>=1500000)
		//	{
			//	printf(x=110h,"？？？？？？点")
			//	printf(x=128h,"処理落ちによる判定不可")
				//;goto loc_D0E1;
			//}

			//mov	byte_15187, 0
			//mov	byte_151A5, 0

		int rank, comment_num;

		if (m_ability == 0)
			rank = 25;
		else if (m_ability < 1050000)
			rank = 24 - m_ability / 50000;
		else if (m_ability < 1200000)
			rank = 3;
		else if (m_ability < 1350000)
			rank = 2;
		else
			rank = 1;

		if (m_ResultType == RESULT_CLEAR || m_ResultType == RESULT_CLEAR_EXTRA)// no continue
		{
			if (m_Difficulty == 0)
				comment_num = 4;			//Try Normal mode
			//else if([bx+27h]<=7)//what is this???
			 //	comment_num=1;			//目標：  もっと稼ごう      
			else if (m_nMiss >= 6)
				comment_num = 7;			//Try no miss play
			//else if([bx+0Ch]>=15)//total used bomb?
			//	comment_num=8;			//Save Bomb
			else
				comment_num = 0;			//All clear  
		}
		else if (RESULT_CLEAR == RESULT_CLEAR_CONTINUE)//; continue used
		{
			comment_num = 2;			//Try one coin play
		}
		else
		{
			if (m_nBomb <= m_nMiss * 2)
				comment_num = 5;		//Use MissBomb
			else
			{
				if (CGame::GVar().m_playStage >= 4 || CGame::GVar().m_nBX32 <= 350)//stage and high get score?
					comment_num = 6;//目標：  得点アイテムを取ろう
				else
					comment_num = 3;//目標：  クリアをしよう     		
			}
		}
		char udeTxtFile[] = "_UDE.TXT";
		int fileIdx = CGame::s_pCurGame->m_th5Dat1.GetChildFileIndex(udeTxtFile);
		CGame::s_pCurGame->m_th5Dat1.Childfseek(fileIdx, rank * 30, SEEK_SET);
		CGame::s_pCurGame->m_th5Dat1.Childfread(m_comment_text[0], 1, 30, fileIdx);
		CGame::s_pCurGame->m_th5Dat1.Childfseek(fileIdx, comment_num * 30 + 780, SEEK_SET);
		CGame::s_pCurGame->m_th5Dat1.Childfread(m_comment_text[1], 1, 30, fileIdx);
		for (int i = 0; i < 2; i++)
			m_comment_text[i][30 - 2] = 0;



	}
	void CPlayResultScreen::Initialize(bool bSwitchMusic, int ResultType)
	{
		m_ResultType = ResultType;

		m_curFrame = 0;
		m_lastKeyState = 0;
		m_curKeyState = 0;
		m_bQuit = false;
		m_curScrFade = 0;
		InitializeValue(ResultType);

		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, NULL, &CGame::s_pCurGame->m_th5Dat1, "UDE.PI");
		if (bSwitchMusic)
		{
			CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_th5Dat1, "NAME");
			th5w::CCommonFunctionMusicSE::Play();
		}
	}
	int CPlayResultScreen::CalcPercent(int value, int MaxValue, bool unk116EA)
	{
		int percent;
		if (MaxValue == 0)
			percent = 0;
		else
			percent = 1000000;
		if (value != MaxValue)
		{
			if (MaxValue == 0)
			{
				percent = 0;
			}
			else
			{
				percent = percent / MaxValue;
			}
			percent = percent * value;
		}
		if (unk116EA == false)
			m_nUnk1517E += percent;
		else
			m_nUnk1517E -= percent;

		//if(byte_1517C!=0)
		m_nUnk15182 = percent / 4;

		return percent;

	}
	void CPlayResultScreen::DrawNumber(int numX, int numY, int number, int nDigit, bool leadingZero, bool rightAlign, float colorR, float colorG, float colorB, int dotpos)
	{
		unsigned char digit[20];
		for (int i = 0; i < nDigit; i++)
		{
			digit[i] = number % 10;
			number /= 10;
		}
		digit[nDigit - 1] += number * 10;		//this is to simulate "score overflow to hex value" of PC98 ver
		int startDigit = nDigit - 1;
		if (leadingZero == false)
		{
			startDigit = 0;
			for (int i = 0; i < nDigit; i++)
				if ((digit[i] != 0) || (dotpos >= i))
					startDigit = i;
		}
		if (rightAlign)
			numX += 16 * (nDigit - 1 - startDigit);
		for (int i = startDigit; i >= 0; i--)
		{
			CTh5ExtFont::DrawExtChar(digit[i] + 0xa0, numX, numY, colorR, colorG, colorB);
			numX += 16;

			if ((dotpos > 0) && (dotpos == i)) {
				CPC98Font::DrawString(".", 100, numX - 1, numY, colorR, colorG, colorB);
				CPC98Font::DrawString(".", 100, numX, numY, colorR, colorG, colorB);
				numX += 16;

			}
		}
	}

	int CPlayResultScreen::Step()
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
			m_curScrFade += 3;
			if (m_curScrFade > 100)
				m_curScrFade = 100;
			return 0;
		}

		m_lastKeyState = m_curKeyState;
		m_curKeyState = CCommonFunctionInput::GetAllKeyState();
		if (CCommonFunctionInput::ZPressed(m_curKeyState, m_lastKeyState))
		{
			m_bQuit = true;
			m_quitCode = PLAYRESULTSCREEN_END;
		}

		return 0;
	}

	void CPlayResultScreen::DrawResult(int x, int y, int type)
	{
		float color[3];
		float colorcmt[3];
		if (type == 0)
		{
			color[0] = 168.0f / 255.0f;
			color[1] = 100.0f / 255.0f;
			color[2] = 100.0f / 255.0f;
			colorcmt[0] = 236.0f / 255.0f;
			colorcmt[1] = 116.0f / 255.0f;
			colorcmt[2] = 116.0f / 255.0f;

		}
		else
		{
			color[0] = 1;
			color[1] = 1;
			color[2] = 1;
			colorcmt[0] = 1;
			colorcmt[1] = 1;
			colorcmt[2] = 1;

		}
		for (int i = 0; i < 13; i++)
		{
			CPC98Font::DrawString(resultListText[i], 100, x - 1, y + i * 24, color[0], color[1], color[2]);
			CPC98Font::DrawString(resultListText[i], 100, x, y + i * 24, color[0], color[1], color[2]);
		}
		unsigned char difficultyName[][10] = { {  2    , 2    , 2    , gb_E_, gb_A_, gb_S_, gb_Y_, 0 },
												{ 2    , gb_N_, gb_O_, gb_R_, gb_M_, gb_A_, gb_L_, 0 },
												{ 2    , 2    , 2    , gb_H_, gb_A_, gb_R_, gb_D_, 0 },
												{ gb_L_, gb_U_, gb_N_, gb_A_, gb_T_, gb_I_, gb_C_, 0 },
												{ 2    , 2    , gb_E_, gb_X_, gb_T_, gb_R_, gb_A_, 0 } };

		CTh5ExtFont::DrawExtString(difficultyName[m_Difficulty], 100, x + 160, y + 24, color[0], color[1], color[2]);//difficulty
		DrawNumber(x + 96 + 16, y + 24 * 2, m_Score * 10, 10, false, true, color[0], color[1], color[2]);				//score
		//DrawNumber(x+96+16,y+24*3,m_nMiss,10,false,true, color[0], color[1], color[2]);						//Miss
		//DrawNumber(x+96+16,y+24*4, m_nBomb,10,false,true, color[0], color[1], color[2]);						//Bomb
		DrawNumber(x + 96, y + 24 * 5, m_nGameAchivement, 10, false, true, color[0], color[1], color[2], 2);
		DrawNumber(x + 96, y + 24 * 6, m_nExorcism, 10, false, true, color[0], color[1], color[2], 2);
		DrawNumber(x + 96, y + 24 * 7, m_nItemCollect, 10, false, true, color[0], color[1], color[2], 2);
		DrawNumber(x + 96, y + 24 * 8, m_nItemHighCollect, 10, false, true, color[0], color[1], color[2], 2);//percent
		// DrawNumber(x+96,y+24*9,m_nfocus,10,false,true, color[0], color[1], color[2],2);//percent
		// DrawNumber(x+96,y+24*10,m_nSlowDown,10,false,true, color[0], color[1], color[2],2);//percent

		CPC98Font::DrawString(denText, 100, x + 270 - 1, y + 24 * 2, color[0], color[1], color[2]);
		CPC98Font::DrawString(denText, 100, x + 270, y + 24 * 2, color[0], color[1], color[2]);

		CPC98Font::DrawString(timesText, 100, x + 270 - 1, y + 24 * 3, color[0], color[1], color[2]);
		CPC98Font::DrawString(timesText, 100, x + 270, y + 24 * 3, color[0], color[1], color[2]);

		CPC98Font::DrawString(timesText, 100, x + 270 - 1, y + 24 * 4, color[0], color[1], color[2]);
		CPC98Font::DrawString(timesText, 100, x + 270, y + 24 * 4, color[0], color[1], color[2]);


		for (int i = 5; i <= 10; i++)
		{
			CPC98Font::DrawString(percentText, 100, x + 270 - 1, y + 24 * i, color[0], color[1], color[2]);
			CPC98Font::DrawString(percentText, 100, x + 270, y + 24 * i, color[0], color[1], color[2]);
		}
		if (m_ability >= 1500000)
		{
			CPC98Font::DrawString(errorText[0], 100, x + 270 - 1, y + 24 * 12, color[0], color[1], color[2]);
			CPC98Font::DrawString(errorText[0], 100, x + 270, y + 24 * 12, color[0], color[1], color[2]);

			CPC98Font::DrawString(errorText[1], 100, x + 48 - 1, y + 24 * 13, colorcmt[0], colorcmt[1], colorcmt[2]);
			CPC98Font::DrawString(errorText[1], 100, x + 48, y + 24 * 13, colorcmt[0], colorcmt[1], colorcmt[2]);

		}
		else
		{
			DrawNumber(x + 96, y + 24 * 12, m_ability / 100, 10, false, true, color[0], color[1], color[2], 2);
			CPC98Font::DrawString(denText, 100, x + 270 - 1, y + 24 * 12, color[0], color[1], color[2]);
			CPC98Font::DrawString(denText, 100, x + 270, y + 24 * 12, color[0], color[1], color[2]);

			CPC98Font::DrawString(m_comment_text[0], 100, x + 48 - 1, y + 24 * 13, colorcmt[0], colorcmt[1], colorcmt[2]);
			CPC98Font::DrawString(m_comment_text[0], 100, x + 48, y + 24 * 13, colorcmt[0], colorcmt[1], colorcmt[2]);

			CPC98Font::DrawString(m_comment_text[1], 100, x + 48 - 1, y + 24 * 14 -8, colorcmt[0], colorcmt[1], colorcmt[2]);
			CPC98Font::DrawString(m_comment_text[1], 100, x + 48, y + 24 * 14 - 8, colorcmt[0], colorcmt[1], colorcmt[2]);
		}
	}

	void CPlayResultScreen::Draw()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (m_curScrFade == 0)
		return;
	
		m_pBGImage->Draw(0, 80);
		CCommonFunctionGraphic::DrawRectangle(0, 0, 639, 79, 1, 1, 1);



		if (m_curScrFade == 0)
			return;
		char strbuf[1000];
		if (m_curFrame >= 50)
			DrawResult(304, 40 + 32, 0);
		CCommonFunctionGraphic::ScreenFade((float)m_curScrFade);

	}


}


