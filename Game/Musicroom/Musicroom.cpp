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
	nt music_count[] = { 14+1,18+1,24+1,28+1,23+1 };
	char musicRoom_up[]= "             ------ ▲ ------       ";
	char musicRoom_down[]= "             ------ ▼ ------       ";
	char musicRoom_middle[]= "             ----------------       ";
	char MusicRoom_TH[][40] = { "   第１弾?東方靈異?  Arrange ver  ",
								"   第２弾?東方封魔?  Special MIX  ",
								"   第３弾?東方夢時空  Special MIX  ",
								"   第４弾?東方幻想郷  Special MIX  ",
								"   第５弾?東方怪?談 MysticSquare  " };
	i
	
	char TH01_Title[][40] =    {"No.1           A Sacred Lot         ",
								"No.2            永遠の巫女          ",
								"No.3    The Positive and Negative   ",
								"No.4   Highly Responsive to Prayers ",
								"No.5            東方怪奇談          ",
								"No.6             天使?説           ",
								"No.7        Oriental Magician       ",
								"No.8           破邪の小太刀         ",
								"No.9               魔鏡             ",
								"No.10       the Legend of KAGE      ",
								"No.11    いざ、?れ逝くその時まで   ",
								"No.12      Civilization of Magic    ",
								"No.13            星幽天使           ",
								"No.14            アイリス           ",
								"            ?イトルに戻る          ",
								""};
	char TH02_Title[][40] =    {"No.1      東方封魔???浄土曼荼羅  ",
								"No.2      ? 博麗??Eastern Wind   ",
								"No.3      ?  She's in a temper!!   ",
								"No.4      ?   End of Daylight?    ",
								"No.5      ?  ? やみのちから??   ",
								"No.6      ?????幻夢界????  ",
								"No.7      ?????を賭して???  ",
								"No.8      ひもろぎ、むらさきにもえ  ",
								"No.9      ?  ? 恋色?ジック ?    ",
								"No.10     ?東方封魔???幽幻乱舞  ",
								"No.11         Complete Darkness     ",
								"No.12        ? エキストララブ      ",
								"No.13        戦車むすめのみるゆめ   ",
								"No.14          ??遠野の森???   ",
								"No.15         昔話わんだ?らんど    ",
								"未使用.1         博麗?社境内       ",
								"未使用.2         ?陽落ちて  ?     ",
								"未使用.3         ?封魔終演  ?     ",
								"              ?イトルに戻る        " };
	char TH03_Title[][40] =   { "No.1       ?夢は時空を越えて       ",
								"No.2      ? ? Selection           ",
								"No.3            東方妖恋談          ",
								"No.4          Reincarnation         ",
								"No.5            Dim. Dream          ",
								"No.6     Tabula rasa??空白少女    ",
								"No.7     ?  Maniacal Princess      ",
								"No.8        夢消失  ?Lost Dream    ",
								"No.9       夢幻遊戯  ?Dream War    ",
								"No.10    魔?決戦！?Fight it out!  ",
								"No.11      ? Sailor of Time        ",
								"No.12       Strawberry Crisis!!     ",
								"No.13        非統一魔?世界?       ",
								"No.14          ?魔?鐘愛           ",
								"No.15          ?久遠の夢           ",
								"No.16          東方の青い空         ",
								"No.17           永遠の満月          ",
								"No.18         Maple Dream...        ",
								"No.19           霊人の休日          ",	
								"No.20            勝利デモ           ",
								"No.21         ゲ??オ?バ?        ",
								"未使用.1          時の風            ",
								"未使用.2     ス???ウドリ??     ",
								"未使用.3       Phantasmagoria       ",
								"              ?イトルに戻る        "};
	char TH04_Title[][40] = {	"No.1    幻想郷  ? Lotus Land Story ",
								"No.2          Witching Dream        ",
								"No.3          Selene's light        ",
								"No.4   装飾戦?? Decoration Battle ",
								"No.5         Break the Sabbath      ",
								"No.6    紅響曲  ? Scarlet Phoneme  ",
								"No.7            Bad Apple!!         ",
								"No.8     霊戦?? Perdition crisis  ",
								"No.9         アリス?エステラ       ",
								"No.10    少女?想曲?? Capriccio   ",
								"No.11   星の器?? Casket of Star   ",
								"No.12           Lotus Love          ",
								"No.13  眠れる恐? ?Sleeping Terror ",
								"No.14           Dream Land          ",
								"No.15    幽夢?? Inanimate Dream   ",
								"No.16      禁じざるをえない遊戯     ",
								"No.17  メイド幻想?? Icemilk Magic ",
								"No.18   かわいい悪魔?? Innocence  ",
								"No.19              Days             ",
								"No.20            Peaceful           ",
								"No.21         Arcadian Dream        ",
								"No.22           幻想の住人          ",
								"未使用.1        Lotus Road          ",
								"未使用.2       Dreamy pilot         ",
								"未使用.3      Incomplete Plot       ",
								"未使用.4        Border Land         ",
								"未使用.5   Magic Shop of Raspberry  ",
								"未使用.6       Crescent Dream       ",
								"              ?イトルに戻る        " };
	char TH05_Title[][40] = {	"No.1     怪?談?? Mystic Square   ",
								"No.2           Dream Express        ",
								"No.3      魔?陣?? Magic Square   ",
								"No.4             夢想時空           ",
								"No.5     霊天?? Spiritual Heaven  ",
								"No.6         Romantic Children      ",
								"No.7       プラス?ック?インド     ",
								"No.8          メイプルワイズ        ",
								"No.9  禁断の魔?  ? Forbidden Magic",
								"No.10  ?紅の少女?? Crimson Dead!!",
								"No.11  裏切りの少女?? Judas Kiss  ",
								"No.12       the Last Judgement      ",
								"No.13  悲しき人??? Doll of Misery",
								"No.14   世界の果て?? World's End  ",
								"No.15   ?話幻想?? Infinite Being ",
								"No.16       不思議の国のアリス      ",
								"No.17     the Grimoire of Alice     ",
								"No.18              ?社             ",
								"No.19            Endless            ",
								"No.20          久遠の楽?           ",
								"No.21         Mystic Dream          ",
								"No.22       Peaceful Romancer       ",
								"No.23         魂の休らむ所          ",
								"              ?イトルに戻る        " };
	char TH01_Filename[][10] =    {"r_00","r_01",    "r_02",   "r_03",  "r_04",   "r_05",  "r_06",   "r_07",   "r_08",   "r_09",   "r_10",   "r_11",   "r_12",   "r_13"};
	char TH02_Filename[][10] =    {"h_op","h_st00",  "h_st00b","h_st01","h_st01b","h_st02","h_st02b","h_st03", "h_st03b","h_st04", "h_st04b","h_st05", "h_st05b","h_end",  "h_staff","h_ng00", "h_ng01", "h_ng02"};
	char TH03_Filename[][10] =    {"y_op","y_select","y_00mm", "y_01mm","y_02mm", "y_03mm","y_04mm", "y_05mm", "y_06mm", "y_dec",  "y_07mm", "y_08mm", "y_demo1","y_demo2","y_demo3","y_demo4","y_demo5","y_ed",  "y_score","y_win",  "y_over","y_ng00","y_ng0!","y_ng02"};
	char TH04_Filename[][10] =    {"g_op","g_st00",  "g_st10", "g_st00b","g_st01","g_st01b","g_st02","g_st02b","g_st03", "g_st03b","g_st04", "g_st04b","g_st05", "g_st05b","g_st06", "g_st06b","g_st06c","g_end1","g_end2", "g_staff","g_name","g_ng00","g_ng01","g_ng02","g_ng03"};
	char TH05_Filename[][10] =    {"op",  "st00",    "st00b",  "st01",   "st01b", "st02",   "st02b", "st03",   "st03b",  "st03c",  "st03d",  "st04",   "st04b",  "st05",   "st05b",  "st06",   "st06b",  "ed00",  "ed01",   "ed02",   "staff", "exed",  "name"};
	
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

	void CMusicRoom::Initialize()
	{
		m_curFrame = 0;
		m_lastKeyState = 0;
		m_curKeyState = 0;
		m_bQuit = false;
		m_curScrFade = 0;

		m_nFilePerPage = 16;
		m_nPage = 5;
		m_listUpperLeftX = 2;
		m_listUpperLeftY = 6;
		SwitchPage(4);
		m_curCursorPos = 0;
		m_curListTop = 0;
		//musicroom comment==_MUSIC0.TXT
		//music.dat
		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, NULL, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
	}

	void CMusicRoom::SwitchPage(int pageIdx)
	{
		m_curPage = pageIdx;
		m_curCursorPos = 0;
		m_curListTop = 0;
		Playmusic();
	}

	void CMusicRoom::Playmusic()
	{
	//	m_nnowPlayingTitle = m_curPage;
		m_nnowPlayingNumber = m_curCursorPos;
	}
	; int __pascal __near music_cmt_load(int track)
/*
	void CMusicRoom::music_cmt_load()
	{
	char fileName[]="_MUSIC0.TXT";
		fileName[6]='0'+m_curPage;
		int fileIdx=CGame::s_pCurGame->m_musicDat.GetChildFileIndex(fileName);
		if (fileIdx!=-1)
		{
			int eax=m_nnowPlayingNumber*MUSIC_CMT_LEN;
			CGame::s_pCurGame->m_musicDat.Childfseek(fileIdx,eax,SEEK_SET);
			CGame::s_pCurGame->m_modDat.Childfread(_music_cmt,size, MUSIC_CMT_LEN,fileIdx);
		}
	strlen(rateText[i])
	xor	si, si
	jmp	short @@check

@@terminate_line:
	mov	bx, si
	imul	bx, MUSIC_CMT_LINE_LEN
	mov	(_music_cmt + MUSIC_CMT_LINE_LEN - 2)[bx], 0
	inc	si

@@check:
	cmp	si, MUSIC_CMT_LINE_COUNT
	jl	short @@terminate_line
	pop	si
	ret
	}
music_cmt_load	endp*/
	
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
		/*	m_curScrFade += 6;
			if (m_curScrFade > 100)*/
				m_curScrFade = 100;
			return 0;
		}

		m_lastKeyState = m_curKeyState;
		m_curKeyState = CCommonFunctionInput::GetAllKeyState();


		if (CCommonFunctionInput::LeftPressed(m_curKeyState, m_lastKeyState))
		{
			SwitchPage((m_curPage + m_nPage - 1) % m_nPage);
		}
		if (CCommonFunctionInput::RightPressed(m_curKeyState, m_lastKeyState))
		{
			SwitchPage((m_curPage + 1) % m_nPage);
		}
		if (CCommonFunctionInput::UpPressed(m_curKeyState, m_lastKeyState))
		{
			m_curCursorPos = (m_curCursorPos + music_count[m_curPage]-1) % (music_count[m_curPage]);
			if (m_curCursorPos < m_curListTop )
				m_curListTop--;
			if ((m_curCursorPos == music_count[m_curPage]-1)&&(m_curPage!=0))
				m_curListTop = music_count[m_curPage]- m_nFilePerPage;

		}
		if (CCommonFunctionInput::DownPressed(m_curKeyState, m_lastKeyState))
		{
			m_curCursorPos = (m_curCursorPos + 1) % (music_count[m_curPage]);
			if (m_curCursorPos == 0)
				m_curListTop = 0;
			if (m_curCursorPos > m_curListTop + m_nFilePerPage -1)
				m_curListTop++;
		}
		if (CCommonFunctionInput::ESCPressed(m_curKeyState, m_lastKeyState)
			|| CCommonFunctionInput::XPressed(m_curKeyState, m_lastKeyState))
		{
			m_bQuit = true;
			m_quitCode = MUSICROOM_END_BACK;
		}
		if (CCommonFunctionInput::ZPressed(m_curKeyState, m_lastKeyState))
		{
			if (music_count[m_curPage] - 1 == m_curCursorPos )
			{
				m_bQuit = true;
				m_quitCode = MUSICROOM_END_BACK;
			}
			else
			{
				Playmusic();
			}
		}
		return 0;
	}

	void CMusicRoom::Draw()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		if (m_curScrFade == 0)
			return;

		m_pBGImage->Draw(0,0);
		m_pBGImage->Draw(0, 80);
		CCommonFunctionGraphic::DrawRectangle(8, 108, 40,140, 0.19921875f, 0.0f, 0.3984375f);
		CCommonFunctionGraphic::DrawRectangle(284, 108, 316, 140, 0.19921875f, 0.0f, 0.3984375f);

		char strBuf[100];
		float text_color[] = { 1.0f,0.796875f,1.0f };
		float white_color[] = { 1.0f,1.0f,1.0f };
		float list_color[] = { 0.7265625f,0.7265625f,1.0f };
		CPC98Font::DrawString(MusicRoom_TH[m_curPage], 100, 8, 32, white_color[0], white_color[1], white_color[2]);
		CPC98Font::DrawString(MusicRoom_TH[m_curPage], 100, 8 - 1, 32, white_color[0], white_color[1], white_color[2]);
		switch (m_curPage)
		{
		case 0:
			sprintf(strBuf, "%s", TH01_Title[m_nnowPlayingNumber]);
			break;
		case 1:
			sprintf(strBuf, "%s", TH02_Title[m_nnowPlayingNumber]);
			break;
		case 2:
			sprintf(strBuf, "%s", TH03_Title[m_nnowPlayingNumber]);
			break;
		case 3:
			sprintf(strBuf, "%s", TH04_Title[m_nnowPlayingNumber]);
			break;
		case 4:
			sprintf(strBuf, "%s", TH05_Title[m_nnowPlayingNumber]);
			break;
		}
		CPC98Font::DrawString(strBuf, 100, 320, 32, text_color[0], text_color[1], text_color[2]);
		CPC98Font::DrawString(strBuf, 100, 320 - 1, 32, text_color[0], text_color[1], text_color[2]);

		
		for (int i = 0; i < m_nFilePerPage; i++)
		{
			int x = m_listUpperLeftX * 8;
			int y = (m_listUpperLeftY + i) * 16;
			

			float color[] = { 0.5f,1.0f,0.5f };
			float sc[] = { 0.2f,0.2f,0.2f };
			float salpha = 0.5f;
			int soffx = 2, soffy = 2;
			switch (m_curPage)
			{
			case 0:
				sprintf(strBuf, "%s", TH01_Title[i + m_curListTop]);
				break;
			case 1:
				sprintf(strBuf, "%s", TH02_Title[i + m_curListTop]);
				break;
			case 2:
				sprintf(strBuf, "%s", TH03_Title[i + m_curListTop]);
				break;
			case 3:
				sprintf(strBuf, "%s", TH04_Title[i + m_curListTop]);
				break;
			case 4:
				sprintf(strBuf, "%s", TH05_Title[i + m_curListTop]);
				break;
			}
			if (i + m_curListTop == m_curCursorPos)
			{
				CPC98Font::DrawString(strBuf, 100, x, y, white_color[0], white_color[1], white_color[2]);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, white_color[0], white_color[1], white_color[2]);
			}
			else
			{
				CPC98Font::DrawString(strBuf, 100, x, y, list_color[0], list_color[1], list_color[2]);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, list_color[0], list_color[1], list_color[2]);
			}

			x += 6 * 8;

			}
		}

	}






















