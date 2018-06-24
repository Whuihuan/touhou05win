#pragma once
#include "../Graphic/include/glew.h"
#include <gl/gl.h>

typedef enum {
	GB_DIGITS = 160,
	gb_0_ = GB_DIGITS,
	gb_1_,
	gb_2_,
	gb_3_,
	gb_4_,
	gb_5_,
	gb_6_,
	gb_7_,
	gb_8_,
	gb_9_,

	GB_LETTERS = 105,
	gb_A_ = GB_LETTERS + 'A',
	gb_B_,
	gb_C_,
	gb_D_,
	gb_E_,
	gb_F_,
	gb_G_,
	gb_H_,
	gb_I_,
	gb_J_,
	gb_K_,
	gb_L_,
	gb_M_ = GB_LETTERS + 'M',
	gb_N_ = GB_LETTERS + 'N',
	gb_O_ = GB_LETTERS + 'O',
	gb_P_,
	gb_Q_,
	gb_R_,
	gb_S_,
	gb_T_,
	gb_U_,
	gb_V_,
	gb_W_,
	gb_X_,
	gb_Y_,
	gb_Z_,
	gb_BULLET,
	gb_PERIOD,
	gb_EXCLAMATION, // !
	gb_QUESTION, // ?
	gb_ELLIPSIS,// ¡¦
	gb_HEART, // ??
	gb_SKULL, // ??
	gb_GHOST, // ??
	gb_SIDDHAM_HAM, // Siddha? seed syllable H?M? (I don't even)
	gb_SP = 207,
} gaiji_bold_t;

typedef enum {
	gs_YINYANG = 2, // ?
	gs_BOMB, // ?? ?? ??? ??? Or simply ???
	gs_BULLET = 218, // ?
	gs_PERIOD, // .
	gs_EXCLAMATION, // !
	gs_QUESTION, // ?
	gs_ELLIPSIS, // ¡¦
	gs_COPYRIGHT, // ?
	gs_HEART, // ??
	gs_SKULL, // ??
	gs_GHOST, // ??
	gs_SIDDHAM_HAM, // Siddha? seed syllable H?M? (I don't even)
	gs_SPACE, // ?
	gs_ARROW_LEFT, // ¡ç
	gs_ARROW_RIGHT, // ¡æ
	gs_END, // "End"

			// Unused 32x16 rank sprites
			gs_EA, gs_SY, // "Ea", "sy"
			gs_NOR, gs_MAL, // "Nor, "mal"
			gs_HA, gs_RD, // "Ha, "rd"
			gs_LUN, gs_ATIC, // "Lun", "atic"

			gs_ALL, // "All"
} gaiji_symbols_t;
// ----------------

namespace th5w{

class CTh5ExtFont
{
protected:
	static bool s_bFontLoaded;
	static GLuint s_fontTex;
public:
	static bool LoadZUNCOM(const char *fileName);
	static void DrawExtChar(unsigned char extChar,int drawX,int drawY,float colorR,float colorG,float colorB,
							float fadeInScale=1.0,bool coordIsUpperLeft=true);
	static void DrawExtString(const unsigned char *extStr,int nChar,int drawX,int drawY,
							  float colorR,float colorG,float colorB,
							  float fadeInScale=1.0,bool coordIsUpperLeft=true,bool bReverse=false);

public:
	CTh5ExtFont(void);
	~CTh5ExtFont(void);
};

}