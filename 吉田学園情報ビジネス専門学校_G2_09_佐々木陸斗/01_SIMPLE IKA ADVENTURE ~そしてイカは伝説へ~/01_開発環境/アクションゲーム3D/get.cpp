//============================================================
//
// 3D制作　トロフィーゲット方法の処理[get.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"get.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"getscore.h"

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGet = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGet = NULL;	//頂点バッファへのぽんった
int g_nGetgetScore;

//============================================================
//ゲットの初期化
//============================================================
void lnitGet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nGetgetScore = GetgetScore();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGMTITLE2);

	//ゲットスコアの初期化
	lnitGetScore();

	//デバイスの取得
	pDevice = GetDevice();


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy.jpg",//TITOL.png"
		&g_pTextureGet);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGet,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGet->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffGet->Unlock();

	//スコア位置
	SetGetScore(g_nGetgetScore, D3DXVECTOR3(1050.0f, 90.0f, 0.0f), (40.0f), (30.0f));
}

//============================================================
//ゲットの終了処理
//============================================================
void UninitGet(void)
{
	//サウンドの停止
	StopSound();

	//ゲットスコアの終了
	UninitGetScore();

	//テクスチャの破棄
	if (g_pTextureGet != NULL)
	{
		g_pTextureGet->Release();
		g_pTextureGet = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGet != NULL)
	{
		g_pVtxBuffGet->Release();
		g_pVtxBuffGet = NULL;
	}
}

//============================================================
//ゲットの更新処理
//============================================================
void UpdateGet(void)
{
	//ゲットスコアの更新処理
	UpdateGetScore();

	// フェード情報の取得
	FADE fade = GetFade();

	//決定キー(RETURNキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_TITLE);
	}
	//決定キー(Kキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_K) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_ketei);

		//モード設定
		SetFade(MODE_GAME);
	}
}

//============================================================
//ゲットの描画処理
//============================================================
void DrawGet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGet);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ゲットスコア呼び出し
	DrawGetScore();
}

