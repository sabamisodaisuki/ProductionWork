//===================================================================
//
//3Dアクション(camera.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//===================================================================
//カメラの構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	float fDistance;			//視点から注視点の距離
	float fDistanceA;			//注視tンから目的の注視点までの距離
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DVIEWPORT9 viewport;
}Camera;

//===================================================================
//マクロ定義
//===================================================================
#define CAMERA_SPEED	(0.5f)

//===================================================================
//プロトタイプ宣言
//===================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nCnt);

//===================================================================
//自作関数宣言
//===================================================================
Camera* GetCamera(void);
void MoveCamera(void);

#endif 