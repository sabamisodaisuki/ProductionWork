//===================================
//
// 3D制作　道[Miti.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _MITI_H_
#define _MITI_H_

#include "main.h"
//===================================
//モデルの構造体の定義
//===================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置					
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 scale;						//
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;						//前回の位置
	D3DXVECTOR3 size;
	int nNumVtx;							//頂点数
	DWORD sizeFVF;							//頂点フォーマットのサイズ
	BYTE*pVtxBuff;							//頂点バッファのポインタ
	int nCounterState;						//状態管理カウンター
	int nLife;								//体力
	int nCounterAnim;						//カウンター
	int nPatternAnim;						//パターン番号
	int nDirectionMove;						//向き
	float fWidth;							//幅
	float fHeight;							//高さ
	bool bDisp;								//表示するかしないか
	bool bIsJumping;						//ジャンプ中
	bool bUse;
	int nType;								//タイプ
}MITI;
//===================================
// プロトタイプ宣言
//===================================
void lnitMiti(void);
void UninitMiti(void);
void UpdateMiti(void);
void DrawMiti(void);
void SetMiti(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);
void MitiSet(void);


#endif

