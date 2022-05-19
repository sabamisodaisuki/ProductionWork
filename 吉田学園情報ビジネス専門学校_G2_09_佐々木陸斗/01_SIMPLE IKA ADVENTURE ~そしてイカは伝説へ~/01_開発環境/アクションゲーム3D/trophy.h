//============================================================
//
// 3D制作　トロフィーの処理[trophy.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _TROPHY_H_
#define _TROPHY_H_

#include "main.h"

//マクロ定義
#define MAX_TROPHY			(128)		//敵の最大数
#define NUM_TROPHY			(10)		//敵の種類
#define TROPHY_SIZE			(300.0f)	//敵のサイズ

//敵の状態
typedef enum
{
	TROPHYSTA_NORMAL = 0,
	TROPHYSTA_DAMAGE,
	TROPHYSTA_MAX
}TROPHYSTATE;


//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	int nType;										//種類
	TROPHYSTATE state;								//状態
	int nCounterState;								//状態管理カウンター
	int nLife;										//体力
	int nScore;										//鳥のスコア
	bool bUse;										//使用しているかどうか
}TROPHY;


//プロトタイプ宣言
void lnitTrophy(void);
void UninitTrophy(void);
void UpdateTrophy(void);
void DrawTrophy(void);
void SetTrophy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void HitTrophy(int nCntTROPHY, int nDamage);

TROPHY*GetTrophy(void);




#endif 

