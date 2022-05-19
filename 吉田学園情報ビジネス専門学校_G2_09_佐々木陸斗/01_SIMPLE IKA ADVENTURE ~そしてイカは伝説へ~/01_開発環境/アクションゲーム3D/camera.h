//============================================================
//
// 3D制作　カメラ処理[camera.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//============================================================
// カメラの構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 posV;				//視点					
	D3DXVECTOR3 posR;				//注視点
	D3DXVECTOR3 vecU;				//↑方向ベクトル
	D3DXVECTOR3 posVDest;			//目的の視点		
	D3DXVECTOR3 posRDest;			//目的の注視点
	D3DXVECTOR3 rot;				//向き
	D3DXVECTOR3 move;				//移動量
	D3DXMATRIX mtxProjection;		//プロジェクション
	D3DXMATRIX mtxviex;				//ビューマトリックス
	float fDistance;				//視点から注視点までの距離B
	float fDistance1;				//視点から注視点までの距離A


}Camera;

//============================================================
// プロトタイプ宣言
//============================================================
Camera*GetCamera(void);
void lnitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

#endif
