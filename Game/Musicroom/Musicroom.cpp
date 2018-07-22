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
#ifdef _TRIAL
	int music_count[] = { 14,18,24,28,18 };
#else
	int music_count[] = { 14,18,24,28,23 };
#endif
#include ".\MusicRoom_Text.cpp"

	char MUSIC_FILES[5][30][40] = { {"r_00","r_01",    "r_02",   "r_03",  "r_04",   "r_05",  "r_06",   "r_07",   "r_08",   "r_09",   "r_10",   "r_11",   "r_12",   "r_13"},
								 {"h_op","h_st00",  "h_st00b","h_st01","h_st01b","h_st02","h_st02b","h_st03", "h_st03b","h_st04", "h_st04b","h_st05", "h_st05b","h_end",  "h_staff","h_ng00", "h_ng01", "h_ng02"},
								 {"y_op","y_select","y_00mm", "y_01mm","y_02mm", "y_03mm","y_04mm", "y_05mm", "y_06mm", "y_dec",  "y_07mm", "y_08mm", "y_demo1","y_demo2","y_demo3","y_demo4","y_demo5","y_ed",  "y_score","y_win",  "y_over","y_ng00","y_ng01","y_ng02"},
								 {"g_op","g_st00",  "g_st10", "g_st00b","g_st01","g_st01b","g_st02","g_st02b","g_st03", "g_st03b","g_st04", "g_st04b","g_st05", "g_st05b","g_st06", "g_st06b","g_st06c","g_end1","g_end2", "g_staff","g_name","g_ng00","g_ng01","g_ng02","g_ng03","g_ng04","g_ng05" },
								 {"OP",  "ST00",    "ST00B",  "ST01",   "ST01B", "ST02",   "ST02B", "ST03",   "ST03B",  "ST03C",  "ST03D",  "ST04",   "ST04B",  "ST05",   "ST05B",  "ST06",   "ST06B",  "ED00",  "ED01",   "ED02",   "STAFF", "EXED",  "NAME"} };
	
	char music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];

	
	CMusicRoom::CMusicRoom(void)
	{
		m_pBGImage = NULL;
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
		CGame::s_pCurGame->m_fpsLimit = 58;

		m_nFilePerPage = 16;
		m_nPage = 5;
		m_listUpperLeftX = 2;
		m_listUpperLeftY = 6;
		m_curPage = 4;
		m_curCursorPos = 0;
		m_curListTop = 0;
		m_curCursorPos = 0;
		m_curListTop = 0;
		MusicCommentLoad();
		LoadPIFromDat(&m_pBGImage, m_palette, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
		//	for (int i = 0; i <= 16; i++)
			//	printf("%d %d %d\n", m_palette[3 * i], m_palette[3 * i + 1], m_palette[3 * i + 2]);

		for (int i = 0; i < MUSIC_POLYGONS; i++) {
			pos[i].x = (float)(rand() % 640);
			pos[i].y = (float)(rand() % 480);
			move_speed[i].x = (float)(8 - (rand() & 15));
			if (move_speed[i].x == 0) {
				move_speed[i].x = 26.0f / (CGame::s_pCurGame->m_fps);
			}
			move_speed[i].y = (float)((rand() & 3) + 32);
			angle[i] = (float)rand();
			rot_speed[i] = (float)(4 - (rand() & 7));
			if (rot_speed[i] == 0.0f) {
				rot_speed[i] = 4.0f;
			}
		}
	}

	void CMusicRoom::MusicCommentLoad()
	{
		char musicTxtFile[] = "_MUSIC0.TXT";
		musicTxtFile[6] += m_curPage;

		int fileIdx = CGame::s_pCurGame->m_musicDat.GetChildFileIndex(musicTxtFile);
		CGame::s_pCurGame->m_musicDat.Childfseek(fileIdx, m_curCursorPos * 400, SEEK_SET);
		CGame::s_pCurGame->m_musicDat.Childfread(music_cmt, 1, MUSIC_CMT_LEN, fileIdx);
		for (int i = 0; i < MUSIC_CMT_LINE_COUNT; i++) {
			music_cmt[i][MUSIC_CMT_LINE_LEN - 2] = 0;
			if (music_cmt[i][0] == ';')//todo:I think I didn't see this at here,
				music_cmt[i][0] = 0;   //where ';' is removed at?
		}
	}
	
	void CMusicRoom::PolygonBuild(COORDF *pts, float x, float y, float rad, int npoint, float angle)
	{
		int i;
		for (i = 0; i < npoint; i++) {
			float point_angle = (float)i * 2 * PI / (float)npoint + angle;
			pts[i].x = (rad * cosf(point_angle)) + x;
			pts[i].y = (rad * sinf(point_angle)) + y;
		}
		pts[i].x = pts[0].x;
		pts[i].y = pts[0].y;
	}

	void CMusicRoom::PolygonsRender(void)
	{
		int i;
		for (i = 0; i < MUSIC_POLYGONS; i++) {
			PolygonBuild(points, pos[i].x, pos[i].y, (float)((i & 3) << 4) + 64, (i / 4) + 3, angle[i]);
			
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
	void CMusicRoom::PolygonsUpdate(void)
	{
		int i;
		float fpshack = 26.0f / (CGame::s_pCurGame->m_fps);
		for (i = 0; i < MUSIC_POLYGONS; i++) {
			pos[i].x += move_speed[i].x * fpshack;
			pos[i].y += move_speed[i].y*0.4f * fpshack;
			angle[i] += rot_speed[i] * 0.05f * fpshack;
			if (pos[i].x <= 0.0f || pos[i].x > 640.0f) {
				move_speed[i].x *= -1.0f;
			}
			if (pos[i].y > 580.0f) {
				pos[i].x = (float)(rand() % 640);
				pos[i].y = -100.0f;
				move_speed[i].x = (float)(8 - (rand() & 15));
				if (move_speed[i].x == 0.0f) {
					move_speed[i].x = 1.0f;
				}
				move_speed[i].y = (float)((rand() & 3) + 32);
				angle[i] = (float)rand();
				rot_speed[i] = (float)(1 - (rand() & 5));
				if (rot_speed[i] == 0.0f) {
					rot_speed[i] = 1.0f;
				}
			}
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
		MusicCommentLoad();
		if (m_curPage == 1 || m_curPage == 2)
			CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_musicDat, MUSIC_FILES[m_curPage][m_nnowPlayingNumber], false);
		else
			CCommonFunctionMusicSE::LoadMusicFromDat(&CGame::s_pCurGame->m_musicDat, MUSIC_FILES[m_curPage][m_nnowPlayingNumber]);
		CCommonFunctionMusicSE::Play();


	}
	bool CMusicRoom::LoadPIFromDat(C2DImage** pRet, unsigned char *outPalette,
		Cth5DatFile *pDatFile, char *piFileName)//hack to use transparent
	{
		int piIdx = pDatFile->GetChildFileIndex(piFileName);
		th5w::CPIFile piFile(pDatFile->GetChildFileContentPointer(piIdx),
			pDatFile->GetChildFileLength(piIdx));
		C2DImage *p2DImage = C2DImage::Create2DImage(piFile.GetWidth(), piFile.GetHeight());
		if (piFile.ExtractImageAndPalette(p2DImage->GetDataPointer(), outPalette, NULL, 0) == false)
		{
			p2DImage->Destroy();
			return false;
		}
		if (p2DImage->UploadToTexture() == false)
		{
			p2DImage->Destroy();
			return false;
		}
		*pRet = p2DImage;
		return true;
	}

	int CMusicRoom::Step()
	{
		PolygonsUpdate();
		m_curFrame++;
		if (m_texttrans < 1.0f)
		{
			m_texttrans += 0.1f;
			if (m_texttrans > 1.0f)
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
			m_curCursorPos = (m_curCursorPos + music_count[m_curPage]) % (music_count[m_curPage] + 1);
#ifdef _TRIAL
			if (m_curPage == 4 && m_curCursorPos > 6 && m_curCursorPos != music_count[m_curPage])
				m_curCursorPos=6;
			else if (m_curPage != 4 && m_curCursorPos > 0 && m_curCursorPos != music_count[m_curPage])
			{
				m_curCursorPos = 0;
				m_curListTop = 0;
			}

#endif
			if (m_curListTop > m_curCursorPos)
				m_curListTop--;
			if ((m_curCursorPos == music_count[m_curPage]) && (m_curPage != 0))
				m_curListTop = music_count[m_curPage] + 1 - m_nFilePerPage;

		}
		if (CCommonFunctionInput::DownPressed(m_curKeyState, m_lastKeyState))
		{
			m_curCursorPos = (m_curCursorPos + 1) % (music_count[m_curPage] + 1);
#ifdef _TRIAL
			if (m_curPage == 4 && m_curCursorPos > 6 && m_curCursorPos != music_count[m_curPage])
			{
				m_curCursorPos = music_count[m_curPage];
				m_curListTop = music_count[m_curPage] - m_nFilePerPage;
			}
			else if(m_curPage!=4 && m_curCursorPos > 0 && m_curCursorPos != music_count[m_curPage])
			{
				m_curCursorPos = music_count[m_curPage];
				m_curListTop = music_count[m_curPage]- m_nFilePerPage;
			}
#endif
			if (m_curCursorPos == 0)
				m_curListTop = 0;
			if (m_curCursorPos > m_curListTop + m_nFilePerPage - 1)
				m_curListTop++;
		}
		if (CCommonFunctionInput::ESCPressed(m_curKeyState, m_lastKeyState)
			|| CCommonFunctionInput::XPressed(m_curKeyState, m_lastKeyState))
		{
			m_bQuit = true;
			m_quitCode = MUSICROOM_END_BACK;
		}
		if (CCommonFunctionInput::ZPressed(m_curKeyState, m_lastKeyState) || CCommonFunctionInput::EnterPressed(m_curKeyState, m_lastKeyState))
		{
			if (music_count[m_curPage] == m_curCursorPos)
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
		CCommonFunctionGraphic::DrawRectangle(0, 0, 640, 480, 0.19921875f, 0.0f, 0.3984375f);
		PolygonsRender();
		//m_pBGImage->Draw(0,0);
		m_pBGImage->Draw(0, 80);
		//CCommonFunctionGraphic::DrawRectangle(8, 108, 40,140, 0.19921875f, 0.0f, 0.3984375f);
		//CCommonFunctionGraphic::DrawRectangle(284, 108, 316, 140, 0.19921875f, 0.0f, 0.3984375f);
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
			// CPC98Font::DrawString(music_cmt[i], 100, 320, 208 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
			//CPC98Font::DrawString(music_cmt[i], 100, 320 - 1, 208 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
			CPC98Font::DrawString(music_cmt[i], 100, 320, 144 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
			CPC98Font::DrawString(music_cmt[i], 100, 320 - 1, 144 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
		}
		CPC98Font::DrawString(musicRoom_up, 100, m_listUpperLeftX * 8, m_listUpperLeftY * 16 - 16, list_color[0], list_color[1], list_color[2]);

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
				CCommonFunctionGraphic::DrawRectangle(x, y, x + 288, y + 16, 1, 1, 1, 1, false);
			}
			if (i + m_curListTop == m_nnowPlayingNumber)
			{
				CPC98Font::DrawString(strBuf, 100, x, y, white_color[0], white_color[1], white_color[2]);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, white_color[0], white_color[1], white_color[2]);
			}
#ifdef _TRIAL
			else if (m_curPage == 4 && i + m_curListTop > 6 && i + m_curListTop != music_count[m_curPage])
			{
				CPC98Font::DrawString(strBuf, 100, x, y, white_color[0], white_color[1], white_color[2],0.5f);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, white_color[0], white_color[1], white_color[2], 0.5f);

			}
			else if (m_curPage != 4 && i + m_curListTop > 0 && i + m_curListTop != music_count[m_curPage])
			{
				CPC98Font::DrawString(strBuf, 100, x, y, white_color[0], white_color[1], white_color[2], 0.5f);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, white_color[0], white_color[1], white_color[2], 0.5f);

			}

#endif
			else
			{
				CPC98Font::DrawString(strBuf, 100, x, y, list_color[0], list_color[1], list_color[2]);
				CPC98Font::DrawString(strBuf, 100, x - 1, y, list_color[0], list_color[1], list_color[2]);
			}


		}
	}
}






















