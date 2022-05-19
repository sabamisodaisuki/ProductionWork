//============================================================
//
// 3D制作　スコアゲットの処理[getscore.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Score.h"

//============================================================
//マクロ定義
//============================================================
#define TEXTURE_U				(10)	//テクスチャ等分

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGetScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGetScore = NULL;		//頂点バッファへのポインタ	
D3DXVECTOR3 g_posGetScore;								//スコアの位置
int g_nGetScore;										//スコアの値

//============================================================
//ゲットスコアの初期化
//============================================================
void lnitGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureGetScore);

	g_posGetScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する
	g_nGetScore = 0; //値を初期化する

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Score,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGetScore,
		NULL);

	VERTEX_2D*pVtx;;		//頂点情報へポインタ

							//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f*nCntScore, g_posGetScore.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f + 20.0f*nCntScore, g_posGetScore.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f*nCntScore, g_posGetScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f + 20.0f*nCntScore, g_posGetScore.y + 30.0f, 0.0f);

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
	g_pVtxBuffGetScore->Unlock();
}

//============================================================
//ゲットスコアの終了処理
//============================================================
void UninitGetScore(void)
{
	//テクスチャの破棄
	if (g_pTextureGetScore != NULL)
	{
		g_pTextureGetScore->Release();
		g_pTextureGetScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGetScore != NULL)
	{
		g_pVtxBuffGetScore->Release();
		g_pVtxBuffGetScore = NULL;
	}

}

//============================================================
//ゲットスコアの更新処理
//============================================================
void UpdateGetScore(void)
{

}

//============================================================
//ゲットスコアの描画処理
//============================================================
void DrawGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGetScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGetScore);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//============================================================
//ゲットスコアの設定処理
//============================================================
void SetGetScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_Score];	//各桁の数字を格納
	int nCntScore;

	g_posGetScore = pos;
	g_nGetScore = nScore;

	VERTEX_2D*pVtx;
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nGetScore % 1000 / 100;
	aPosTexU[1] = g_nGetScore % 100 / 10;
	aPosTexU[2] = g_nGetScore % 10 / 1;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posGetScore.x + fWidth*nCntScore, g_posGetScore.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetScore.x + fWidth + fWidth*nCntScore, g_posGetScore.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetScore.x + fWidth*nCntScore, g_posGetScore.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetScore.x + fWidth + fWidth*nCntScore, g_posGetScore.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntScore] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffGetScore->Unlock();
}
//============================================================
//ゲットスコアの加算処理
//============================================================
void AddGetScore(int nValue)
{
	int aPosTexU[MAX_Score];	//各桁の数字を格納
	int nCntScore;

	g_nGetScore += nValue;

	aPosTexU[0] = g_nGetScore % 1000 / 100;
	aPosTexU[1] = g_nGetScore % 100 / 10;
	aPosTexU[2] = g_nGetScore % 10 / 1;

	VERTEX_2D*pVtx;;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}

	//頂点バッファアンロック
	g_pVtxBuffGetScore->Unlock();
}

int GetgetScore(void)
{
	return g_nGetScore;
}