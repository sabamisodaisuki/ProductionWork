//============================================================
//
// 3D制作　UIの処理[Ui.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _Ui_H_
#define _Ui_H_

#include "main.h"

//マクロ定義
#define MAX_Ui			(128)		//敵の最大数
#define NUM_Ui			(10)		//敵の種類
#define Ui_SIZE			(300.0f)	//敵のサイズ

//敵の状態
typedef enum
{
	UiSTA_NORMAL = 0,
	UiSTA_DAMAGE,
	UiSTA_MAX
}UiSTATE;


//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 move;								//移動量
	int nType;										//種類
	UiSTATE state;									//状態
	float fWidth;									//幅
	float fHeight;									//高
	int nCounterState;								//状態管理カウンター
	int nLife;										//体力
	int nScore;										//鳥のスコア
	bool bUse;										//使用しているかどうか
}Ui;


//プロトタイプ宣言
void lnitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight);


#endif 


