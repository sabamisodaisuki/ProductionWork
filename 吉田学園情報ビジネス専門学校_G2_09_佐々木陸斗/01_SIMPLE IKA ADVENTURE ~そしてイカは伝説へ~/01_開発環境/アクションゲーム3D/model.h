//===================================
//
// 3D制作　モデル[model.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _MODEL_H_
#define _MODEL_H_

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
	D3DXVECTOR3 size;						//サイズ
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
	bool bUse;								//使用するかどうか
	int nType;								//タイプ
}Model;
//===================================
// プロトタイプ宣言
//===================================
void lnitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
bool CollisionModel(D3DXVECTOR3*pPos,//現在の位置
	D3DXVECTOR3*pPosOld,			//前回の高さ
	D3DXVECTOR3*pMove,				//移動量
	D3DXVECTOR3*pSize);				//サイズ
									//ブロックの設定処理
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);
void ModelSet(void);
float GetYMaxModel(void);
Model*GetModel(void);

#endif
