//============================================================
//
// 3D制作　ゲットトロフィーの処理[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _GETTROPHY_H_
#define _GETTROPHY_H_
#define MAX_GETTROPHY				(3)		//読み込むサイズ
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	float fWidth;									//幅
	float fHeight;									//高さ
	bool bUse;										//使用しているかどうか
}GETTrophy;


//プロトタイプ宣言
void lnitGetTrophy(void);
void UninitGetTrophy(void);
void UpdateGetTrophy(void);
void DrawGetTrophy(void);
void SetGetTrophy(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight);
void AddGetTrophy(int nValue);
int GetgetTrophy(void);
#endif 

