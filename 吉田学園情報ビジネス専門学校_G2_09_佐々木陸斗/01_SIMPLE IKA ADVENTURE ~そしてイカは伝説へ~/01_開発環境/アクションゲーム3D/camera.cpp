//============================================================
//
// 3D制作　カメラの処理[camera.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "camera.h "
#include "main.h"
#include "input.h"
#include "player.h"

//============================================================
//グローバル変数
//============================================================
Camera g_camera;

//============================================================
// カメラの初期化
//============================================================
void lnitCamera(void)
{
	//プレイヤーの情報を取得
	Player*pPlayer = GetPlayer();

	//視点・注視点・↑方向を設定
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -245.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x)*(g_camera.posR.x - g_camera.posV.x)+(g_camera.posR.z-g_camera.posV.z)*(g_camera.posR.z-g_camera.posV.z));
	g_camera.fDistance1 = 20.0f;

}

//============================================================
// カメラの終了処理
//============================================================
void UninitCamera(void)
{

}

//============================================================
// カメラのアップデート処理
//============================================================
void UpdateCamera(void)
{
	//プレイヤーの情報を取得
	Player*pPlayer = GetPlayer();

	//カメラの正規化

	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}
	else if (g_camera.rot.y< -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}

//============================================================
// カメラの追従
//============================================================
	g_camera.posRDest.x = pPlayer->pos.x;// -sinf(pPlayer->rot.y) * g_camera.fDistance1;
	g_camera.posRDest.y = pPlayer->pos.y;
	g_camera.posRDest.z = pPlayer->pos.z;// -cosf(pPlayer->rot.y) * g_camera.fDistance1;

	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x)*0.1f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z)*0.1f;

	g_camera.posVDest.x = g_camera.posRDest.x; //+cosf(pPlayer->rot.y)*g_camera.fDistance;
	g_camera.posVDest.y = g_camera.posRDest.y + 250.0f;
	g_camera.posVDest.z = g_camera.posRDest.z - 350.0f;// +sinf(pPlayer->rot.y)*g_camera.fDistance;

	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
}

//============================================================
// カメラのセット処理
//============================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxviex);

	//ビューマトリックスの制作
	D3DXMatrixLookAtLH(&g_camera.mtxviex,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxviex);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの制作
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}
//============================================================
// カメラ情報
//============================================================
Camera*GetCamera(void)
{
	return&g_camera;
}