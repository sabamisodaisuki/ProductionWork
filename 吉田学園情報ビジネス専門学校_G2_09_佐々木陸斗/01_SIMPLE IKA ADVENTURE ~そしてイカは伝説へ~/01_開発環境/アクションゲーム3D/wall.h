
//============================================================
//
// 3D制作　壁の処理[wall.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//============================================================
// 影の構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//視点					
	D3DXVECTOR3 rot;				//注視点
	D3DXVECTOR3 col;				//色
	D3DXMATRIX mtxWorld;			//
	float fWidth;					//幅
	float fHeight;					//高さ
	bool bUse;						//使用しているかどうか
}Wall;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth,float fHeight, float fcol);
void ZZWall(void);
Wall*GetWall(void);
#endif