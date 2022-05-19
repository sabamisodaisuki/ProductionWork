//============================================================
//
// 3D制作スコアの処理[score.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#define MAX_Score				(4)		//読み込むサイズ
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	float fWidth;									//幅
	float fHeight;									//高さ
	bool bUse;										//使用しているかどうか
}Score;


//プロトタイプ宣言
void lnitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore,D3DXVECTOR3 pos,float fWidth, float fHeight);
void AddScore(int nValue);
int GetScore(void);
#endif 