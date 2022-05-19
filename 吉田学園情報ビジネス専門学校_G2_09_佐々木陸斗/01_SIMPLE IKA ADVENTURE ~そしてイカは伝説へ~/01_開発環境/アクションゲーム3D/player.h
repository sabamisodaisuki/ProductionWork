//===================================
//
// 3D制作　プレイヤー[player.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
//===================================
//モデルの構造体の定義
//===================================
typedef struct
{
	D3DXVECTOR3 pos;				//位置					
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rot;				//角度
	D3DXVECTOR3 posOld;				//前回の位置
	D3DXVECTOR3 VtxMin;				//最小値
	D3DXVECTOR3 VtxMax;				//最大値
	D3DXVECTOR3 size;				//サイズ
	int nCounterState;				//状態管理カウンター
	int nLife;						//体力
	int nCounterAnim;				//カウンター
	int nPatternAnim;				//パターン番号
	int nDirectionMove;				//向き
	float fWidth;					//幅
	float fHeight;					//高さ
	bool bDisp;						//表示するかしないか
	bool bIsJumping;				//ジャンプ
	bool blsLanding;
	bool bUse;

}Player;
//===================================
// プロトタイプ宣言
//===================================
void lnitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void DeathPlayer(D3DXVECTOR3 pos);
Player*GetPlayer(void);
#endif

