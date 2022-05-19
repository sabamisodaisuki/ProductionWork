//============================================================
//
// 3D制作　ゲットスコアの処理[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _GETSCORE_H_
#define _GETSCORE_H_
#define MAX_GETScore				(3)		//読み込むサイズ
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	float fWidth;									//幅
	float fHeight;									//高さ
	bool bUse;										//使用しているかどうか
}GETScore;


//プロトタイプ宣言
void lnitGetScore(void);
void UninitGetScore(void);
void UpdateGetScore(void);
void DrawGetScore(void);
void SetGetScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddGetScore(int nValue);
int GetgetScore(void);
#endif 
