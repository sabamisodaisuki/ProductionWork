//============================================================
//
// 3D制作　リザルト処理[result.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"result.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"Score.h"
#include"HighScore.h"
#include"trophy.h"
#include"Gettrophy.h"
#include"getscore.h"

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureRESULT = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRESULT = NULL;	//頂点バッファへのぽんった
int g_nRESULTScore;
int g_Counter;
int g_GetTrophy;

//============================================================
//リザルトの初期化処理
//============================================================
void lnitRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nRESULTScore = GetScore();
	g_GetTrophy = GetgetTrophy();

	//スコア
	lnitScore();

	//トロフィー数
	lnitGetTrophy();

	lnitTrophy();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result.jpg",
		&g_pTextureRESULT);


	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRESULT,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRESULT->Unlock();

	//スコア位置
 	SetScore(g_nRESULTScore, D3DXVECTOR3(550.0f, 355.0f, 0.0f), (50.0f), (30.0f));

	//トロフィー数
	SetGetTrophy(g_GetTrophy, D3DXVECTOR3(950.0f,470.0f, 0.0f), (50.0f), (30.0f));
}

//============================================================
//リザルトの終了処理
//============================================================
void UninitRESULT(void)
{
	//サウンドの停止
	StopSound();

	//スコア
	UninitScore();

	//トロフィー数
	UninitGetTrophy();

	UninitTrophy();

	//テクスチャの破棄
	if (g_pTextureRESULT != NULL)
	{
		g_pTextureRESULT->Release();
		g_pTextureRESULT = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRESULT != NULL)
	{
		g_pVtxBuffRESULT->Release();
		g_pVtxBuffRESULT = NULL;
	}
}

//============================================================
//リザルトの更新処理
//============================================================
void UpdateRESULT(void)
{
	g_Counter++;
	//スコア
	UpdateScore();
	
	UpdateGetTrophy();

	UpdateTrophy();

	if (g_Counter == 10)
	{
		SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 0);
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_fanfare);
		AddScore(100);
		AddGetTrophy(1);
		AddGetScore(13);
	}
	
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
//リザルト画面の描画処理
//============================================================
void DrawRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRESULT, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRESULT);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//スコア呼び出し
	DrawScore();

	//獲得トロフィー表示
	DrawGetTrophy();

	//出るトロフィー表示
	DrawTrophy();
}

		

