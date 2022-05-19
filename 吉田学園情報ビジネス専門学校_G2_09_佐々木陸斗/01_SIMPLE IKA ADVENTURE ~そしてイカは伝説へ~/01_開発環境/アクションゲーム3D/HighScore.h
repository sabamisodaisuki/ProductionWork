//============================================================
//
// 3D制作　ハイスコアの処理[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_
#define MAX_HigeScore				(5)		//読み込むサイズ



#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 move;				//移動量
	float fWidth;					//幅
	float fHeight;					//高さ
	bool bUse;						//使用しているかどうか
}HigeScore;


//プロトタイプ宣言
void lnitHigeScore(void);
void UninitHigeScore(void);
void UpdateHigeScore(void);
void DrawHigeScore(void);
void SetHigeScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddHigeScore(int nValue);
void LoadHigeScore(void);
void SaveHigeScore(void);
int GetHigeScore(void);
#endif 