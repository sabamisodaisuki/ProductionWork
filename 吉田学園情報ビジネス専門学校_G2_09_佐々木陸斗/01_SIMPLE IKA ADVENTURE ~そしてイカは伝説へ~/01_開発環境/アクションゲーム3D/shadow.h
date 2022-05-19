//============================================================
//
// 3D制作　影の処理[shadow.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//============================================================
// 影の構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//視点					
	D3DXVECTOR3 rot;				//注視点
	D3DXMATRIX mtxWorld;			//
	bool bUse;						//
}Shadow;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
#endif
