//===================================================================
//
//3Dアクション(wall.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _WALL_H_
#define _WALL_H_

//===================================================================
//マクロ定数
//===================================================================
#define MAX_WALL	(4)	//影の最大数

//===================================================================
//影の構造体設定
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//方向
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使用しているか
}Wall;

//===================================================================
//プロトタイプ宣言
//===================================================================
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Wall* GetWall(void);

#endif 