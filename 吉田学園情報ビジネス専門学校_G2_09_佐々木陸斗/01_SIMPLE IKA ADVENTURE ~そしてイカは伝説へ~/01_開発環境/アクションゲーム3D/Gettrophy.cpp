//============================================================
//
// 3D制作　トロフィー獲得数の処理[Gettrophy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Gettrophy.h"

//============================================================
//マクロ定義
//============================================================
#define TEXTURE_U				(10)	//テクスチャ等分

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGettrophy = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGettrophy = NULL;		//頂点バッファへのポインタ	
D3DXVECTOR3 g_posGetTrophy;								//スコアの位置
int g_nGetTrophy;										//スコアの値

//============================================================
//トロフィーゲットの初期化
//============================================================
void lnitGetTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTrophy;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureGettrophy);

	g_posGetTrophy = D3DXVECTOR3(1020.0f, 70.0f, 0.0f);//位置を初期化する
	g_nGetTrophy= 0; //値を初期化する

					 //頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GETTROPHY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGettrophy,
		NULL);

	VERTEX_2D*pVtx;;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f*nCntTrophy, g_posGetTrophy.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f + 20.0f*nCntTrophy, g_posGetTrophy.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f*nCntTrophy, g_posGetTrophy.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f + 20.0f*nCntTrophy, g_posGetTrophy.y + 30.0f, 0.0f);

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
	g_pVtxBuffGettrophy->Unlock();
}

//============================================================
//トロフィーゲットの終了処理
//============================================================
void UninitGetTrophy(void)
{
	//テクスチャの破棄
	if (g_pTextureGettrophy != NULL)
	{
		g_pTextureGettrophy->Release();
		g_pTextureGettrophy = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGettrophy != NULL)
	{
		g_pVtxBuffGettrophy->Release();
		g_pVtxBuffGettrophy = NULL;
	}

}
//============================================================
//トロフィーゲットの更新処理
//============================================================
void UpdateGetTrophy(void)
{

}

//============================================================
//トロフィーゲットの描画処理
//============================================================
void DrawGetTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTrophy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGettrophy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGettrophy);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTrophy * 4, 2);
	}
}

//============================================================
//トロフィーゲットの設定処理
//============================================================
void SetGetTrophy(int nTrophy, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_GETTROPHY];	//各桁の数字を格納
	int nCntTrophy;

	g_posGetTrophy = pos;
	g_nGetTrophy = nTrophy;

	VERTEX_2D*pVtx;
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nGetTrophy % 1000 / 100;
	aPosTexU[1] = g_nGetTrophy % 100 / 10;
	aPosTexU[2] = g_nGetTrophy % 10 / 1;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth*nCntTrophy, g_posGetTrophy.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth + fWidth*nCntTrophy, g_posGetTrophy.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth*nCntTrophy, g_posGetTrophy.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth + fWidth*nCntTrophy, g_posGetTrophy.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntTrophy] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffGettrophy->Unlock();
}
//============================================================
//トロフィーゲットの加算処理
//============================================================
void AddGetTrophy(int nValue)
{
	int aPosTexU[MAX_GETTROPHY];	//各桁の数字を格納
	int nCntTrophy;

	g_nGetTrophy += nValue;

	aPosTexU[0] = g_nGetTrophy % 1000 / 100;
	aPosTexU[1] = g_nGetTrophy % 100 / 10;
	aPosTexU[2] = g_nGetTrophy % 10 / 1;

	VERTEX_2D*pVtx;;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}

	//頂点バッファアンロック
	g_pVtxBuffGettrophy->Unlock();
}

int GetgetTrophy(void)
{
	return g_nGetTrophy;
}