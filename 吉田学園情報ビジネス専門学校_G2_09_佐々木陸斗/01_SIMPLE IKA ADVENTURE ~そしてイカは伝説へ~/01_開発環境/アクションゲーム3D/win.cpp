//============================================================
//
// 3D制作　CLEAR画面[win.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"RESULT.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"win.h"
#include"Score.h"

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureWin = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWin = NULL;	//頂点バッファへのぽんった
int g_nWinScore;

//============================================================
//CLEAR画面の初期化
//============================================================
void lnitWin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	g_nWinScore = GetScore();
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	//デバイスの取得
	pDevice = GetDevice();

	//スコア初期化
	lnitScore();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ika08.png",
		&g_pTextureWin);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWin,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffWin->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffWin->Unlock();
	//スコア位置
	SetScore(g_nWinScore, D3DXVECTOR3(600.0f, 315.0f, 0.0f), (50.0f), (30.0f));
}

//============================================================
//CLEAR画面の終了
//============================================================
void UninitWin(void)
{
	//サウンドの停止
	StopSound();

	//スコア終了
	UninitScore();

	//テクスチャの破棄
	if (g_pTextureWin != NULL)
	{
		g_pTextureWin->Release();
		g_pTextureWin = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWin != NULL)
	{
		g_pVtxBuffWin->Release();
		g_pVtxBuffWin = NULL;
	}
}

//============================================================
//CLEAR画面の更新
//============================================================
void UpdateWin(void)
{
	//スコアの更新
	UpdateScore();

	// フェード情報の取得
	FADE fade = GetFade();

	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//モード設定
		SetFade(MODE_TITLE);
	}

	//シフトキーが押されたかどうか
	if (GetKeyboardTrigger(DIK_SPACE) == true && fade == FADE_NONE)
	{
		//モード設定
		SetFade(MODE_GAME);
	}

}

//============================================================
//CLEAR画面の描画処理
//============================================================
void DrawWin(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWin, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureWin);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//スコアの描画
	DrawScore();

	
}
