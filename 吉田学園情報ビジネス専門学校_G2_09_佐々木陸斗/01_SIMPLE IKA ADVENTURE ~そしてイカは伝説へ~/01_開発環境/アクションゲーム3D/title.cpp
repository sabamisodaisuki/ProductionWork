//============================================================
//
// 3D制作　タイトル処理[title.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"title.h"
#include"game.h"
#include"sound.h"
#include"fade.h"

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//頂点バッファへのぽんった


//============================================================
//タイトルの初期化処理
//============================================================
void lnitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGMTITLE2);

	//デバイスの取得
	pDevice = GetDevice();
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE1.jpg",
		&g_pTextureTitle);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();
}

//============================================================
//タイトル終了処理
//============================================================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//============================================================
//タイトル更新処理
//============================================================
void UpdateTitle(void)
{
	// フェード情報の取得
	FADE fade = GetFade();

	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//モード設定
		SetFade(MODE_KIKEN);
	}
	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_K) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_GAME);
	}

	//LSHIFTキー(LSHIFTキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_LSHIFT) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_STAFF);
	}

	//RSHIFTキー(LSHIFTキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_RSHIFT) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_STAFF);
	}
	//SPACEキー(SPACEキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_SPACE) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_GET);
	}
}

//============================================================
//タイトルの描画処理
//============================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 , 2);
}

