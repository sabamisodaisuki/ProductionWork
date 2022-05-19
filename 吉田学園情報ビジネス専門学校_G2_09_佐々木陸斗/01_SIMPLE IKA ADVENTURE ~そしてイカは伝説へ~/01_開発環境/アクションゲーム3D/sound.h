//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Sasaki Rikuto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGMTITLE2,		//タイトルBGM
	SOUND_LABEL_BGMTITLE,		//タイトルBGM
	SOUND_LABEL_BGMMAOU,		//タイトルBGM2
	SOUND_LABEL_BGMGame,		//ゲームBGM
	SOUND_LABEL_BGMGameBGM,		//ゲームBGM
	SOUND_LABEL_SE_ketei,		//決定音
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_bakuha,	// 爆発音
	SOUND_LABEL_SE_aruki,	// 歩き
	SOUND_LABEL_SE_jump,	// 歩き
	SOUND_LABEL_SE_fanfare,
	SOUND_LABEL_MAX,
	SOUND_LABEL_si
} SOUND_LABEL;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
