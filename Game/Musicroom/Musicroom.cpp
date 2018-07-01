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


namespace th5w {
	char music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];
	int music_count[] = { 14,18,24,28,23 };
	char musicRoom_up[]= "             ------ £ ------       ";
	char musicRoom_down[]= "             ------ ¥ ------       ";
	char musicRoom_middle[]= "             ----------------       ";//dummy
	
	char MusicRoom_TH[5][40] = { "   ‘æ‚P’e?“Œ•ûèËˆÙ?  Arrange ver  ",
								"   ‘æ‚Q’e?“Œ•û••–‚?  Special MIX  ",
								"   ‘æ‚R’e?“Œ•û–²Žž‹ó  Special MIX  ",
								"   ‘æ‚S’e?“Œ•ûŒ¶‘z‹½  Special MIX  ",
								"   ‘æ‚T’e?“Œ•û‰ö?’k MysticSquare  " };
	char MUSIC_TITLES[5][30][40] = {{"No.1           A Sacred Lot         ",
									"No.2            ‰i‰“‚Ì›Þ—          ",
									"No.3    The Positive and Negative   ",
									"No.4   Highly Responsive to Prayers ",
									"No.5            “Œ•û‰öŠï’k          ",
									"No.6             “VŽg?à           ",
									"No.7        Oriental Magician       ",
									"No.8           ”jŽ×‚Ì¬‘¾“         ",
									"No.9               –‚‹¾             ",
									"No.10       the Legend of KAGE      ",
									"No.11    ‚¢‚´A?‚êÀ‚­‚»‚ÌŽž‚Ü‚Å   ",
									"No.12      Civilization of Magic    ",
									"No.13            ¯—H“VŽg           ",
									"No.14            ƒAƒCƒŠƒX           ",
									"            ?ƒCƒgƒ‹‚É–ß‚é          ",
									""} ,
								   {"No.1      “Œ•û••–‚???ò“y™Öä¶—…  ",
									"No.2      ? ”Ž—í??Eastern Wind   ",
									"No.3      ?  She's in a temper!!   ",
									"No.4      ?   End of Daylight?    ",
									"No.5      ?  ? ‚â‚Ý‚Ì‚¿‚©‚ç??   ",
									"No.6      ?????Œ¶–²ŠE????  ",
									"No.7      ?????‚ð“q‚µ‚Ä???  ",
									"No.8      ‚Ð‚à‚ë‚¬A‚Þ‚ç‚³‚«‚É‚à‚¦  ",
									"No.9      ?  ? —öF?ƒWƒbƒN ?    ",
									"No.10     ?“Œ•û••–‚???—HŒ¶—•‘  ",
									"No.11         Complete Darkness     ",
									"No.12        ? ƒGƒLƒXƒgƒ‰ƒ‰ƒu      ",
									"No.13        íŽÔ‚Þ‚·‚ß‚Ì‚Ý‚é‚ä‚ß   ",
									"No.14          ??‰“–ì‚ÌX???   ",
									"No.15         Ì˜b‚í‚ñ‚¾?‚ç‚ñ‚Ç    ",
									"–¢Žg—p.1         ”Ž—í?ŽÐ‹«“à       ",
									"–¢Žg—p.2         ?—z—Ž‚¿‚Ä  ?     ",
									"–¢Žg—p.3         ?••–‚I‰‰  ?     ",
									"              ?ƒCƒgƒ‹‚É–ß‚é        " },
								   {"No.1       ?–²‚ÍŽž‹ó‚ð‰z‚¦‚Ä       ",
									"No.2      ? ? Selection           ",
									"No.3            “Œ•û—d—ö’k          ",
									"No.4          Reincarnation         ",
									"No.5            Dim. Dream          ",
									"No.6     Tabula rasa??‹ó”’­—    ",
									"No.7     ?  Maniacal Princess      ",
									"No.8        –²ÁŽ¸  ?Lost Dream    ",
									"No.9       –²Œ¶—V‹Y  ?Dream War    ",
									"No.10    –‚?ŒˆíI?Fight it out!  ",
									"No.11      ? Sailor of Time        ",
									"No.12       Strawberry Crisis!!     ",
									"No.13        ”ñ“ˆê–‚?¢ŠE?       ",
									"No.14          ?–‚?àˆ¤           ",
									"No.15          ?‹v‰“‚Ì–²           ",
									"No.16          “Œ•û‚ÌÂ‚¢‹ó         ",
									"No.17           ‰i‰“‚Ì–žŒŽ          ",
									"No.18         Maple Dream...        ",
									"No.19           —ìl‚Ì‹x“ú          ",
									"No.20            Ÿ—˜ƒfƒ‚           ",
									"No.21         ƒQ??ƒI?ƒo?        ",
									"–¢Žg—p.1          Žž‚Ì•—            ",
									"–¢Žg—p.2     ƒX???ƒEƒhƒŠ??     ",
									"–¢Žg—p.3       Phantasmagoria       ",
									"              ?ƒCƒgƒ‹‚É–ß‚é        "},
								   {"No.1    Œ¶‘z‹½  ? Lotus Land Story ",
									"No.2          Witching Dream        ",
									"No.3          Selene's light        ",
									"No.4   ‘•üí?? Decoration Battle ",
									"No.5         Break the Sabbath      ",
									"No.6    g‹¿‹È  ? Scarlet Phoneme  ",
									"No.7            Bad Apple!!         ",
									"No.8     —ìí?? Perdition crisis  ",
									"No.9         ƒAƒŠƒX?ƒGƒXƒeƒ‰       ",
									"No.10    ­—?‘z‹È?? Capriccio   ",
									"No.11   ¯‚ÌŠí?? Casket of Star   ",
									"No.12           Lotus Love          ",
									"No.13  –°‚ê‚é‹°? ?Sleeping Terror ",
									"No.14           Dream Land          ",
									"No.15    —H–²?? Inanimate Dream   ",
									"No.16      ‹Ö‚¶‚´‚é‚ð‚¦‚È‚¢—V‹Y     ",
									"No.17  ƒƒCƒhŒ¶‘z?? Icemilk Magic ",
									"No.18   ‚©‚í‚¢‚¢ˆ«–‚?? Innocence  ",
									"No.19              Days             ",
									"No.20            Peaceful           ",
									"No.21         Arcadian Dream        ",
									"No.22           Œ¶‘z‚ÌZl          ",
									"–¢Žg—p.1        Lotus Road          ",
									"–¢Žg—p.2       Dreamy pilot         ",
									"–¢Žg—p.3      Incomplete Plot       ",
									"–¢Žg—p.4        Border Land         ",
									"–¢Žg—p.5   Magic Shop of Raspberry  ",
									"–¢Žg—p.6       Crescent Dream       ",
									"              ?ƒCƒgƒ‹‚É–ß‚é        " },
								   {"No.1     ‰ö?’k?? Mystic Square   ",
									"No.2           Dream Express        ",
									"No.3      –‚?w?? Magic Square   ",
									"No.4             –²‘zŽž‹ó           ",
									"No.5     —ì“V?? Spiritual Heaven  ",
									"No.6         Romantic Children      ",
									"No.7       ƒvƒ‰ƒX?ƒbƒN?ƒCƒ“ƒh     ",
									"No.8          ƒƒCƒvƒ‹ƒƒCƒY        ",
									"No.9  ‹Ö’f‚Ì–‚?  ? Forbidden Magic",
									"No.10  ?g‚Ì­—?? Crimson Dead!!",
									"No.11  — Ø‚è‚Ì­—?? Judas Kiss  ",
									"No.12       the Last Judgement      ",
									"No.13  ”ß‚µ‚«l??? Doll of Misery",
									"No.14   ¢ŠE‚Ì‰Ê‚Ä?? World's End  ",
									"No.15   ?˜bŒ¶‘z?? Infinite Being ",
									"No.16       •sŽv‹c‚Ì‘‚ÌƒAƒŠƒX      ",
									"No.17     the Grimoire of Alice     ",
									"No.18              ?ŽÐ             ",
									"No.19            Endless            ",
									"No.20          ‹v‰“‚ÌŠy?           ",
									"No.21         Mystic Dream          ",
									"No.22       Peaceful Romancer       ",
									"No.23         °‚Ì‹x‚ç‚ÞŠ          ",
									"              ?ƒCƒgƒ‹‚É–ß‚é        " } };
	char MUSIC_FILES[5][30][40] = { {"r_00","r_01",    "r_02",   "r_03",  "r_04",   "r_05",  "r_06",   "r_07",   "r_08",   "r_09",   "r_10",   "r_11",   "r_12",   "r_13"},
								 {"h_op","h_st00",  "h_st00b","h_st01","h_st01b","h_st02","h_st02b","h_st03", "h_st03b","h_st04", "h_st04b","h_st05", "h_st05b","h_end",  "h_staff","h_ng00", "h_ng01", "h_ng02"},
								 {"y_op","y_select","y_00mm", "y_01mm","y_02mm", "y_03mm","y_04mm", "y_05mm", "y_06mm", "y_dec",  "y_07mm", "y_08mm", "y_demo1","y_demo2","y_demo3","y_demo4","y_demo5","y_ed",  "y_score","y_win",  "y_over","y_ng00","y_ng01","y_ng02"},
								 {"g_op","g_st00",  "g_st10", "g_st00b","g_st01","g_st01b","g_st02","g_st02b","g_st03", "g_st03b","g_st04", "g_st04b","g_st05", "g_st05b","g_st06", "g_st06b","g_st06c","g_end1","g_end2", "g_staff","g_name","g_ng00","g_ng01","g_ng02","g_ng03","g_ng04","g_ng05" },
								 {"OP",  "ST00",    "ST00B",  "ST01",   "ST01B", "ST02",   "ST02B", "ST03",   "ST03B",  "ST03C",  "ST03D",  "ST04",   "ST04B",  "ST05",   "ST05B",  "ST06",   "ST06B",  "ED00",  "ED01",   "ED02",   "STAFF", "EXED",  "NAME"} };
	CMusicRoom::CMusicRoom(void)
	{
		m_pBGImage = NULL;
//		m_bEnterNameMode = false;
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
		m_texttrans = 1.0f;
		
		m_nFilePerPage = 16;
		m_nPage = 5;
		m_listUpperLeftX = 2;
		m_listUpperLeftY = 6;
		SwitchPage(4);
		m_curCursorPos = 0;
		m_curListTop = 0;
//		pmdwork = getopenwork();
		CCommonFunctionGraphic::LoadPIFromDat(&m_pBGImage, NULL, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
		
		for (int i = 0; i < MUSIC_POLYGONS; i++) {
				pos[i].x = (float)(rand() % 640);
				pos[i].y = (float)(rand() % 480);
				move_speed[i].x = (float)(8 - (rand() & 15));
				if(move_speed[i].x == 0) { 
					move_speed[i].x = 26.0f / (CGame::s_pCurGame->m_fps);
				} 
				move_speed[i].y = (float)((rand() & 3) + 32);
				angle[i] = (float)rand(); 
				rot_speed[i] = (float)(4 - (rand() & 7)); 
				if(rot_speed[i] == 0.0f) { 
					rot_speed[i] = 4.0f; 
				}
			}
	}
	
	void CMusicRoom::music_cmt_load()
	{
		char musicTxtFile[] = "_MUSIC0.TXT";
		musicTxtFile[6] += m_curPage;

		int fileIdx = CGame::s_pCurGame->m_musicDat.GetChildFileIndex(musicTxtFile);
		CGame::s_pCurGame->m_musicDat.Childfseek(fileIdx, m_curCursorPos * 400, SEEK_SET);
		CGame::s_pCurGame->m_musicDat.Childfread(music_cmt,1,MUSIC_CMT_LEN, fileIdx);
		for (int i = 0; i < MUSIC_CMT_LINE_COUNT; i++) {
			music_cmt[i][MUSIC_CMT_LINE_LEN - 2] = 0;
			if (music_cmt[i][0] == ';')//todo:I think I didn't see this at here,
				music_cmt[i][0] = 0;   //where ';' is removed at?
		}
	}
	COORD a = { 1,2 };
	
	void CMusicRoom::polygon_build(COORDF *pts, float x, float y, float rad, int npoint, float angle)
	{
		int i;
		//printf("rad:%6.2f npoint:%d.angle:%6.2f\n", rad, npoint, angle);
		//y /= 16.0f;
		for (i = 0; i < npoint; i++) {
			float point_angle = (float)i*2*PI  / (float)npoint + angle;
			pts[i].x = (rad * cosf(point_angle) ) + x;
			pts[i].y = (rad * sinf(point_angle) ) + y;
			//printf("pts[%d].x:%6.2f pts[%d].y:6.2f\n", i, pts[i].x, i,pts[i].y);
		}
		pts[i].x = pts[0].x;
		pts[i].y = pts[0].y;
	}
	
	
	void CMusicRoom::polygons_update_and_render(void)
	{
		int i;
		float fpshack = 26.0f / (CGame::s_pCurGame->m_fps);
		for (i = 0; i < MUSIC_POLYGONS; i++) {
			polygon_build(points, pos[i].x, pos[i].y,(float)((i & 3) << 4) + 64, (i / 4) + 3, angle[i]);
			pos[i].x += move_speed[i].x * fpshack;
			pos[i].y += move_speed[i].y*0.4f * fpshack;
			angle[i] += rot_speed[i]*0.05f * fpshack;
			if (pos[i].x <= 0.0f || pos[i].x > 640.0f) {
				move_speed[i].x *= -1.0f;
			}
			if (pos[i].y > 680.0f) {
				pos[i].x = (float)(rand() % 640);
				pos[i].y = -200.0f;
				move_speed[i].x = (float)(8 - (rand() & 15));
				if(move_speed[i].x == 0.0f) { 
					move_speed[i].x = 1.0f;
				} 
				move_speed[i].y = (float)((rand() & 3) + 32);
				angle[i] = (float)rand(); 
				rot_speed[i] = (float)(1 - (rand() & 5)); 
				if(rot_speed[i] == 0.0f) { 
					rot_speed[i] = 1.0f;
				}
			}
		//	CCommonFunctionGraphic::DrawRectangle(pos[i].x- (float)((i & 3) << 4)/2.0f - 32.0f
		//, pos[i].y - (float)((i & 3) << 4) / 2.0f - 32.0f, pos[i].x + (float)((i & 3) << 4) / 2.0f + 32.0f, pos[i].y + (float)((i & 3) << 4) / 2.0f + 32.0f, 0.19921875f, 1.0f, 0.3984375f);
			//grcg_polygon_c(points, (i / 4) + 3);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, CGame::s_pCurGame->m_windowWidth,
				0, CGame::s_pCurGame->m_windowHeight);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glDisable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0, 0, 0, 1);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_POLYGON);
			for (int j = 0; j < (i / 4) + 3; j++) {
				glVertex2f(points[j].x, CGame::s_pCurGame->m_windowHeight - 1 - points[j].y);
			}
			glEnd();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

		}
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
		m_texttrans = 0.0f;
		m_nnowPlayingNumber = m_curCursorPos;
		CCommonFunctionMusicSE::Pause();
		CCommonFunctionMusicSE::UnloadData();
		music_cmt_load();
		if(m_curPage==1|| m_curPage==2)
		CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_musicDat, MUSIC_FILES[m_curPage][m_nnowPlayingNumber],false);
		else
		CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_musicDat, MUSIC_FILES[m_curPage][m_nnowPlayingNumber]);
		CCommonFunctionMusicSE::Play();

		
	}

	int CMusicRoom::Step()
	{
		m_curFrame++;
		if (m_texttrans<1.0f)
		{
			m_texttrans += 0.1f;
			if (m_texttrans>1.0f)
				m_texttrans = 1.0f;
			return 0;
		}

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
			m_curCursorPos = (m_curCursorPos + music_count[m_curPage]) % (music_count[m_curPage]+1);
			if (m_curListTop > m_curCursorPos   )
				m_curListTop--;
			if ((m_curCursorPos == music_count[m_curPage])&&(m_curPage!=0))
				m_curListTop = music_count[m_curPage]+1- m_nFilePerPage;

		}
		if (CCommonFunctionInput::DownPressed(m_curKeyState, m_lastKeyState))
		{
			m_curCursorPos = (m_curCursorPos + 1) % (music_count[m_curPage]+1);
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
		if (CCommonFunctionInput::ZPressed(m_curKeyState, m_lastKeyState)||CCommonFunctionInput::EnterPressed(m_curKeyState, m_lastKeyState))
		{
			if (music_count[m_curPage] == m_curCursorPos )
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
		polygons_update_and_render();
		char strBuf[100];
		float text_color[] = { 1.0f,0.796875f,1.0f };
		float white_color[] = { 1.0f,1.0f,1.0f };
		float list_color[] = { 0.7265625f,0.7265625f,1.0f };
		CPC98Font::DrawString(MusicRoom_TH[m_curPage], 100, 8, 32, white_color[0], white_color[1], white_color[2]);
		CPC98Font::DrawString(MusicRoom_TH[m_curPage], 100, 8 - 1, 32, white_color[0], white_color[1], white_color[2]);

		CPC98Font::DrawString(music_cmt[0], 100, 320, 32, text_color[0], text_color[1], text_color[2], m_texttrans);
		CPC98Font::DrawString(music_cmt[0], 100, 320 - 1, 32, text_color[0], text_color[1], text_color[2], m_texttrans);
		
		for (int i = 1; i < 10; i++)
		{
			CPC98Font::DrawString(music_cmt[i], 100, 320, 208 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
			CPC98Font::DrawString(music_cmt[i], 100, 320 - 1, 208 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
		}
		CPC98Font::DrawString(musicRoom_up, 100, m_listUpperLeftX * 8, m_listUpperLeftY * 16 -16, list_color[0], list_color[1], list_color[2]);
		
		CPC98Font::DrawString(musicRoom_down, 100, m_listUpperLeftX * 8, (m_listUpperLeftY + m_nFilePerPage) * 16, list_color[0], list_color[1], list_color[2]);

		for (int i = 0; i < m_nFilePerPage; i++)
		{
			int x = m_listUpperLeftX * 8;
			int y = (m_listUpperLeftY + i) * 16;
			

			float color[] = { 0.5f,1.0f,0.5f };
			float sc[] = { 0.2f,0.2f,0.2f };
			float salpha = 0.5f;
			sprintf(strBuf, "%s", MUSIC_TITLES[m_curPage][i + m_curListTop]);
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


			}

		/*
		for (int i = 0; i < NumOfAllPart; i++) {
			sprintf(strBuf, "Note for channel %d is %x", i, notes[i]);
			CPC98Font::DrawString(strBuf, 100, 0, i*16, white_color[0], white_color[1], white_color[2]);

		}*/
		}
	



	}






















