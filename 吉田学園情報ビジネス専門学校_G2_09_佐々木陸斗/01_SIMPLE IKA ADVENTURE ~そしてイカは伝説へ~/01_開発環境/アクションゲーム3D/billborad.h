//============================================================
//
// 3D制作　billboradの処理[billborad.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _BILLBORAD_H_
#define _BILLBORAD_

#include "main.h"

//============================================================
// 構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//視点					
	D3DXVECTOR3 rot;				//注視点
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//幅
	float fHeight;					//高さ
	bool bUse;						//使用しているかどうか
}Billborad;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitBillborad(void);
void UninitBillborad(void);
void UpdateBillborad(void);
void DrawBillborad(void);
void SetBillborad(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

#endif
