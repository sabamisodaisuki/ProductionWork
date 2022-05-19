//============================================================
//
// 3D制作　タイム処理[time.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"time.h"
#include"fade.h"
#include"HighScore.h"
//============================================================
//マクロ定義
//============================================================
#define TEXTURE_U				(10)	//テクスチャ当分

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファへのポインタ	
D3DXVECTOR3 g_posTime;								//スコアの位置
int g_nTime;										//スコアの値
int g_nTimetime;

//============================================================
//タイムの初期化処理
//============================================================
void lnitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime);

	g_posTime = D3DXVECTOR3(620.0f, 10.0f, 0.0f);//位置を初期化する
	g_nTime = 0;								//値を初期化する
	g_nTimetime = 0;
	
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

						//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{

		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_posTime.x + 30.0f*nCntTime, g_posTime.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 30.0f + 30.0f*nCntTime, g_posTime.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x + 30.0f*nCntTime, g_posTime.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 30.0f + 30.0f*nCntTime, g_posTime.y + 30.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffTime->Unlock();
	
	//ゲーム時間設定
	SetTime(300);
}

//============================================================
//タイムの終了処理
//============================================================
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

}

//============================================================
//タイムの更新処理
//============================================================
void UpdateTime(void)
{// フェード情報の取得
	FADE fade = GetFade();

	g_nTimetime++;
	if (g_nTimetime%60==0)
	{
		AddTime(-1);
	}
	if (g_nTime <= 0 && fade == FADE_NONE)
	{
		SaveHigeScore();

		SetFade(MODE_TIMEOVER);
		return;
	}

}

//============================================================
//タイムの描画処理
//============================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//============================================================
//タイムの設定処理
//============================================================
void SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];	//各桁の数字を格納

	int nCntTime;

	g_nTime = nTime;

	aPosTexU[0] = g_nTime % 1000 / 100;
	aPosTexU[1] = g_nTime % 100 / 10;
	aPosTexU[2] = g_nTime % 10 / 1;


	VERTEX_2D*pVtx;		//頂点情報へポインタ

						//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffTime->Unlock();

}
//============================================================
//タイムの加算処理
//============================================================
void AddTime(int nValue)
{
	int aPosTexU[MAX_TIME];	//各桁の数字を格納

	int nCntTime;

	g_nTime += nValue;

	aPosTexU[0] = g_nTime % 1000 / 100;
	aPosTexU[1] = g_nTime % 100 / 10;
	aPosTexU[2] = g_nTime % 10 / 1;


	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffTime->Unlock();

}