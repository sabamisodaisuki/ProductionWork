//===================================
//
// 3D制作	地下配置[Tika.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _Tika_H_
#define _Tika_H_

#include "main.h"
//===================================
//Tikaの構造体の定義
//===================================
typedef struct
{
	D3DXVECTOR3 pos;				//位置					
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 scale;				//
	D3DXVECTOR3 rot;				//
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;				//前回の位置
	D3DXVECTOR3 size;
	int nNumVtx;					//頂点数
	DWORD sizeFVF;					//頂点フォーマットのサイズ
	BYTE*pVtxBuff;					//頂点バッファのポインタ
	int nCounterState;				//状態管理カウンター
	int nLife;						//体力
	int nCounterAnim;				//カウンター
	int nPatternAnim;				//パターン番号
	int nDirectionMove;				//向き
	float fWidth;					//幅
	float fHeight;					//高さ
	bool bDisp;						//表示するかしないか
	bool bIsJumping;				//ジャンプ中
	bool bUse;
	int nType;						//タイプ
}Tika;
//===================================
// プロトタイプ宣言
//===================================
void lnitTika(void);
void UninitTika(void);
void UpdateTika(void);
void DrawTika(void);							
void SetTika(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);//ブロックの設定処理
void TikaSet(void);
bool CollisionTika(D3DXVECTOR3*pPos,//現在の位置
	D3DXVECTOR3*pPosOld,			//前回の高さ
	D3DXVECTOR3*pMove,				//移動量
	D3DXVECTOR3*pSize);				//サイズ
Tika*GetTika(void);

#endif


