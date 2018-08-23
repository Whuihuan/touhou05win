#include ".\MusicRoom.h"
#include "../Game.h"
#include "..\..\include\PMDWin\PMDWinImort.h"
#include "../../gameLib/PMDPlayer/PMDPlayer.h"
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
QQ* pmddriver[24];
#define DELAY_CAL 200
int pmdonkaibuf[24][DELAY_CAL+1];
char OnkaiName[][3]={"c ", "c+", "d ", "d+", "e ", "f ", "f+", "g ", "g+", "a ", "a+", "b "};

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
								 {"g_op","g_st00",  "g_st10", "g_st00b","g_st01","g_st01b","g_st02","g_st02b","g_st03", "g_st03b", "g_st03C","g_st04", "g_st04b","g_st05", "g_st05b","g_st06", "g_st06b","g_st06c","g_end1","g_end2", "g_staff","g_name","g_ng00","g_ng01","g_ng02","g_ng03","g_ng04","g_ng05" },
								 {"OP",  "ST00",    "ST00B",  "ST01",   "ST01B", "ST02",   "ST02B", "ST03",   "ST03B",  "ST03C",  "ST03D",  "ST04",   "ST04B",  "ST05",   "ST05B",  "ST06",   "ST06B",  "ED00",  "ED01",   "ED02",   "STAFF", "EXED",  "NAME"} };
	
	char music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];

	
	CMusicRoom::CMusicRoom(void)
	{
		m_pBGImage = NULL;
		m_pBGImage2 = NULL;
	}

	CMusicRoom::~CMusicRoom(void)
	{
		if (m_pBGImage)
			m_pBGImage->Destroy();
		m_pBGImage = NULL;
		if (m_pBGImage2)
			m_pBGImage2->Destroy();
		m_pBGImage2 = NULL;
	}

	void CMusicRoom::Initialize()
	{
		for(int i=0;i<24;i++)
			pmddriver[i]= getpartwork(i);

		m_curFrame = 0;
		m_lastKeyState = 0;
		m_curKeyState = 0;
		m_bQuit = false;
		m_curScrFade = 0;
		m_texttrans = 1.0f;
		CGame::s_pCurGame->SetVSYNC(true);
		CGame::s_pCurGame->m_fpsLimit = 26*2;

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
		m_palette[0]=51;
		m_palette[1]=0;
		m_palette[2]=102;
		LoadPIFromDat(&m_pBGImage, m_palette,NULL, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
		m_palette[0]=m_palette[3];
		m_palette[1]=m_palette[4];
		m_palette[2]=m_palette[5];
		m_palette[30]=m_palette[33];
		m_palette[31]=m_palette[34];
		m_palette[32]=m_palette[35];
		m_palette[36]=m_palette[39];
		m_palette[37]=m_palette[40];
		m_palette[38]=m_palette[41];
		m_palette[42]=m_palette[45];
		m_palette[43]=m_palette[46];
		m_palette[44]=m_palette[47];
		LoadPIFromDat(&m_pBGImage2, NULL, m_palette, &CGame::s_pCurGame->m_th5Dat1, "MUSIC.PI");
			
		for (int i = 0; i < MUSIC_POLYGONS; i++) {
			pos[i].x = (float)(rand() % 640);
			pos[i].y = (float)(rand() % 480);
			move_speed[i].x = (float)(4 - rand()%8)/2.0f;
			if (move_speed[i].x < 0.01f) {
				move_speed[i].x = 1.0f/2.0f;
			}
			move_speed[i].y = (float)(rand()%4+32)/2.0f;
			angle[i] = (float)rand();
			rot_speed[i] = (float)(4 - (rand()%15))*PI/128.0f/2.0f;
			if (rot_speed[i] < 0.01f) {
				rot_speed[i] = 4.0f*PI/128.0f/2.0f;
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
		GLuint texID=m_pBGImage2->GetTexID();
		for (i = 0; i < MUSIC_POLYGONS; i++) {
			PolygonBuild(points, pos[i].x, pos[i].y, (float)((i & 3) << 4) + 64, (i / 6) + 3, angle[i]);
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,texID);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, CGame::s_pCurGame->m_windowWidth,
					   0, CGame::s_pCurGame->m_windowHeight);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glColor4f(1,1,1,1);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			
			glDisable(GL_DEPTH_TEST);

			glBegin(GL_POLYGON);
			
			
			for (int j = 0; j < (i / 4) + 3; j++) {
				glTexCoord2d(points[j].x/1024.0f, (CGame::s_pCurGame->m_windowHeight - 1 - points[j].y)/512.0f);
				glVertex3f(points[j].x, CGame::s_pCurGame->m_windowHeight - 1 - points[j].y,0);
			}
			glEnd();
			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

		}
	}
	void CMusicRoom::PolygonsUpdate(void)
	{
		int i;
		for (i = 0; i < MUSIC_POLYGONS; i++) 
		{
			pos[i].x += move_speed[i].x;
			pos[i].y += move_speed[i].y;
			angle[i] += rot_speed[i];
			if (pos[i].x <= 0.0f || pos[i].x > 640.0f) 
				move_speed[i].x *= -1.0f;
			if (pos[i].y > 580.0f) 
			{
				pos[i].x = (float)(rand() % 640);
				pos[i].y = -100.0f;
				move_speed[i].x = (float)(4 - rand()%8)/2.0f;
				if (move_speed[i].x < 0.001f) 
					move_speed[i].x = 1.0f/2.0f;
				move_speed[i].y = (float)(rand()%4+32)/2.0f;
				angle[i] = (float)rand();
				rot_speed[i] = (float)(4 - (rand()%16))*PI/128.0f/2.0f;
				if (rot_speed[i] < 0.001f) 
					rot_speed[i] = 4.0f*PI/128.0f/2.0f;
			
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
	bool CMusicRoom::LoadPIFromDat(C2DImage** pRet, unsigned char *outPalette, unsigned char *inPalette,
		Cth5DatFile *pDatFile, char *piFileName)//hack for musicroombackground
	{
		int piIdx = pDatFile->GetChildFileIndex(piFileName);
		th5w::CPIFile piFile(pDatFile->GetChildFileContentPointer(piIdx),
			pDatFile->GetChildFileLength(piIdx));
		C2DImage *p2DImage = C2DImage::Create2DImage(piFile.GetWidth(), piFile.GetHeight()+80);
		unsigned char *pWrite=p2DImage->GetDataPointer();
		piFile.ExtractImageAndPalette(p2DImage->GetDataPointer()+80*piFile.GetWidth()*4, outPalette, inPalette);
		piFile.ExtractImageAndPalette(p2DImage->GetDataPointer(), outPalette, inPalette);
		for (int i=11;i<=21;i++)
		{
			for (int j=112;j<=128;j++)
			{
			pWrite[(640*(480-j)+i)*4]=m_palette[0];
			pWrite[(640*(480-j)+i)*4+1]=m_palette[1];
			pWrite[(640*(480-j)+i)*4+2]=m_palette[2];
			pWrite[(640*(480-j)+i)*4+3]=255;
			}
		}
		for (int i=293;i<=303;i++)
		{
			for (int j=112;j<=128;j++)
			{
			pWrite[(640*(480-j)+i)*4]=m_palette[0];
			pWrite[(640*(480-j)+i)*4+1]=m_palette[1];
			pWrite[(640*(480-j)+i)*4+2]=m_palette[2];
			pWrite[(640*(480-j)+i)*4+3]=255;
			}
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
		/*printf("PCMPOS:%4d frame:%04d ",getpos2(),m_curFrame);
		for(int i=0; i<14; i++)
		{		
			pmdonkaibuf[i][m_curFrame%DELAY_CAL]=pmddriver[i]->onkai;
			if(pmdonkaibuf[i][(m_curFrame+1)%DELAY_CAL]!=0xFF)
				printf("%1d%2s ",pmdonkaibuf[i][(m_curFrame+1)%DELAY_CAL]/0x10+1,OnkaiName[pmdonkaibuf[i][(m_curFrame+1)%DELAY_CAL]%0x10]);
			else
				printf("    ");
		}*/
		//printf("\n");
		
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
		m_pBGImage->Draw(0, 0);
		PolygonsRender();
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
			CPC98Font::DrawString(music_cmt[i], 100, 320, 208+16 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
			CPC98Font::DrawString(music_cmt[i], 100, 320 - 1, 208+16 + i * 16, text_color[0], text_color[1], text_color[2], m_texttrans);
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
		{
		for(int part=0;part<8;part++)
			for(int i=0;i<8;i++)
			{
				float x=384+i*28;
				float y=64+16+part*18;
			
				CCommonFunctionGraphic::DrawRectangle(x+(4*0), y, x + 2+(4*0), y + 14, 1, 1, 1);	//C
				CCommonFunctionGraphic::DrawRectangle(x+(4*1), y, x + 2+(4*1), y + 14, 1, 1, 1);	//D
				CCommonFunctionGraphic::DrawRectangle(x+(4*2), y, x + 2+(4*2), y + 14, 1, 1, 1);	//E
				CCommonFunctionGraphic::DrawRectangle(x+(4*3), y, x + 2+(4*3), y + 14, 1, 1, 1);	//F
				CCommonFunctionGraphic::DrawRectangle(x+(4*4), y, x + 2+(4*4), y + 14, 1, 1, 1);	//G
				CCommonFunctionGraphic::DrawRectangle(x+(4*5), y, x + 2+(4*5), y + 14, 1, 1, 1);	//A
				CCommonFunctionGraphic::DrawRectangle(x+(4*6), y, x + 2+(4*6), y + 14, 1, 1, 1);	//B
				
				CCommonFunctionGraphic::DrawRectangle(x+2+4*0, y, x + 2+2+4*0, y + 8 , 0, 0, 0);//C+
				CCommonFunctionGraphic::DrawRectangle(x+2+4*1, y, x + 2+2+4*1, y + 8 , 0, 0, 0);//D+
				CCommonFunctionGraphic::DrawRectangle(x+2+4*3, y, x + 2+2+4*3, y + 8 , 0, 0, 0);//F+
				CCommonFunctionGraphic::DrawRectangle(x+2+4*4, y, x + 2+2+4*4, y + 8 , 0, 0, 0);//G+
				CCommonFunctionGraphic::DrawRectangle(x+2+4*5, y, x + 2+2+4*5, y + 8 , 0, 0, 0);//A+
				
				/*for(int j=0;j<12;j++);
					if(pmdonkaibuf[part][(m_curFrame+1)%DELAY_CAL]/0x10==i)
					{	
						if(OnkaiName[pmdonkaibuf[part][(m_curFrame+1)%DELAY_CAL]%0x10==j])
						{
							
						}
					}*/
			}
		}
	}
}




