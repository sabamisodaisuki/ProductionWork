//============================================================
//
// 3D制作　エフェクトの処理[effect.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
//============================================================
//マクロ定義
//============================================================
#define MAX_EFFECT			(4096)		//エフェクトの最大数
//============================================================
// エフェクトの構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//視点					
	D3DXVECTOR3 rot;				//注視点
	D3DXCOLOR col;					//色
	D3DXVECTOR3 size;				//サイズ
	D3DXVECTOR3 move;				//移動
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//幅
	float fHeight;					//高さ
	int nLife;						//寿命
	bool bUse;						//使用しているかどうか
}Effect;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int life);
void ZZEffect(void);
#endif