//============================================================
//
// 3D制作　スタッフ紹介[staff.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Staff.h"
#include"game.h"
#include"sound.h"
#include"fade.h"


//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureStaff = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStaff = NULL;	//頂点バッファへのぽんった

//============================================================
//スタッフの初期化処理
//============================================================
void lnitStaff(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/staff.jpg",//TITOL.png"
		&g_pTextureStaff);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStaff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffStaff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの描画
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロック
	g_pVtxBuffStaff->Unlock();
}

//============================================================
//スタッフの終了処理
//============================================================
void UninitStaff(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureStaff != NULL)
	{
		g_pTextureStaff->Release();
		g_pTextureStaff = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStaff != NULL)
	{
		g_pVtxBuffStaff->Release();
		g_pVtxBuffStaff = NULL;
	}
}

//============================================================
//スタッフの更新処理
//============================================================
void UpdateStaff(void)
{
	// フェード情報の取得
	FADE fade = GetFade();

	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_TITLE);
	}
	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_K) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_GAME);
	}
}

//============================================================
//スタッフの描画処理
//============================================================
void DrawStaff(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStaff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureStaff);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

