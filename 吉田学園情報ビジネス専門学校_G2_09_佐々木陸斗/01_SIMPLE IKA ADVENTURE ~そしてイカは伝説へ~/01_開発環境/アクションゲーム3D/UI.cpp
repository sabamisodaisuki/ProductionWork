//============================================================
//
// 3D制作　UI[UI.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Ui.h"
#include"Score.h"
#include"sound.h"
#include"fade.h"
#include"HighScore.h"

//============================================================
//マクロ定義
//============================================================
#define MAX_Ui				(128)			//UIの最大数
#define Ui_SIZE_X			(100.0f)		//UIサイズ
#define Ui_SIZE_Y			(100.0f)		//UIサイズ

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureUi = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtexBuffUi = NULL;
Ui g_aUi[MAX_Ui];
int g_CounterUi;
// フェード情報の取得
FADE fade = GetFade();


//============================================================
//UIの初期化処理
//============================================================
void lnitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ScoreUI.png",
		&g_pTextureUi);

	//UIの情報の初期化
	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		g_aUi[nCntUi].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].bUse = false;
	}

	g_CounterUi = 0;

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Ui,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtexBuffUi,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtexBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtexBuffUi->Unlock();

	//UI位置
	SetUi(D3DXVECTOR3(970.0f, 35.0f, 0.0f), (300.0f), (300.0f));
}
//============================================================
//UIの終了処理
//============================================================
void UninitUi(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureUi != NULL)
	{
		g_pTextureUi->Release();
		g_pTextureUi = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtexBuffUi != NULL)
	{
		g_pVtexBuffUi->Release();
		g_pVtexBuffUi = NULL;
	}
}
//============================================================
//UIの更新処理
//============================================================
void UpdateUi(void)
{

}
//============================================================
//UIの描画処理
//============================================================
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtexBuffUi, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureUi);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUi * 4, 2);
		}
	}
}
//============================================================
//UIの設定処理
//============================================================
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntUi;
	VERTEX_2D*pVtx;
	g_pVtexBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == false)
		{//UIが使用されてない場合
			g_aUi[nCntUi].pos = pos;
			g_aUi[nCntUi].fWidth = fWidth;	//幅
			g_aUi[nCntUi].fHeight = fHeight;//高さ

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);

			g_aUi[nCntUi].bUse = true;	//使用している状態にする

			break;		//(for文を抜ける)
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtexBuffUi->Unlock();
}
//============================================================
//グローバル変数
//============================================================
void DeleteUi(int nCntUi)
{

	//サウンドの再生
	PlaySound(SOUND_LABEL_SE_bakuha);

	g_CounterUi++;
	//使用していない状態へ
	g_aUi[nCntUi].bUse = false;

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_CounterUi == 4)//アイテムをすべて取りリザルト画面へ
		{
			SaveHigeScore();
			SetFade(MODE_WIN);
			return;
		}
	}

}
//アイテムの取得
Ui*GetUi(void)
{
	return &g_aUi[0];
}
