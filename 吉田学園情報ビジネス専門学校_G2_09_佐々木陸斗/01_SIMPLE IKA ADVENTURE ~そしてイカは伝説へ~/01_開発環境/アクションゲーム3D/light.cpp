//============================================================
//
// 3D制作　ライト処理[light.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "light.h"
#include "main.h"

//============================================================
// グローバル変数
//============================================================
D3DLIGHT9 g_light [10];	//ライト情報

//============================================================
// ライトの初期化処理
//============================================================
void lnitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ベクトル
	D3DXVECTOR3 verDir[10];

	//ライトクリア
	ZeroMemory(&g_light[0],sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[1], sizeof(D3DLIGHT9));

	//ライトの種類
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡張光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//ライトの方向を設定
	verDir[0] = D3DXVECTOR3(0.2f, -1.0f, -0.4f);
	verDir[1] = D3DXVECTOR3(-0.2f,-1.0f,  0.4f);

	//正規化する
	D3DXVec3Normalize(&verDir[0], &verDir[0]);
	g_light[0].Direction = verDir[0];

	//正規化する
	D3DXVec3Normalize(&verDir[1], &verDir[1]);
	g_light[1].Direction = verDir[1];

	//ライトを設定する
	pDevice->SetLight(0, &g_light[0]);

	//ライトを設定する
	pDevice->SetLight(1, &g_light[1]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	//ライトを有効にする
	pDevice->LightEnable(1, TRUE);
}

//============================================================
// ライトの終了処理
//============================================================
void UninitLight(void)
{

}

//============================================================
// ライトのアップデート処理
//============================================================
void UpdateLight(void)
{

}