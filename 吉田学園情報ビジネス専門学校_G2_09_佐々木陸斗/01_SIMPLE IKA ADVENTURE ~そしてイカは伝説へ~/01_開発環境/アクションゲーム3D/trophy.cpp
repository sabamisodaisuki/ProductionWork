//============================================================
//
// 3D制作　トロフィー[trophy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"trophy.h"
#include"Score.h"
#include"sound.h"
#include"result.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_apTextureTROPHY[NUM_TROPHY] = { NULL };	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTROPHY = NULL;				//頂点バッファポインタ
TROPHY g_aTROPHY[MAX_TROPHY];									//敵の情報
int g_nTROPHYCouter;											//敵のカウント

//鳥の取得
TROPHY*GetTROPHY(void)
{
	return &g_aTROPHY[0];
}

//============================================================
//トロフィーの初期化処理
//============================================================
void lnitTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTROPHY;

	//カウンターの初期化
	nCntTROPHY = 0;

	//デバイスの取得
	pDevice = GetDevice();


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy11.png",
		&g_apTextureTROPHY[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy1.png",
		&g_apTextureTROPHY[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy2.png",
		&g_apTextureTROPHY[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy3.png",
		&g_apTextureTROPHY[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy4.png",
		&g_apTextureTROPHY[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy6.png",
		&g_apTextureTROPHY[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy.png",
		&g_apTextureTROPHY[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy5.png",
		&g_apTextureTROPHY[7]);

	//鳥の初期化
	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		g_aTROPHY[nCntTROPHY].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTROPHY[nCntTROPHY].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTROPHY[nCntTROPHY].nType = 0;
		g_aTROPHY[nCntTROPHY].bUse = false;
	}

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TROPHY * NUM_TROPHY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTROPHY,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
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
	g_pVtxBuffTROPHY->Unlock();
	lnitGetScore();
}

//============================================================
//トロフィーの処理処理
//============================================================
void UninitTrophy(void)
{
	int nCntTROPHY;
	UninitGetScore();

	for (nCntTROPHY = 0; nCntTROPHY < NUM_TROPHY; nCntTROPHY++)
	{ //テクスチャの破棄
		if (g_apTextureTROPHY[nCntTROPHY] != NULL)
		{
			g_apTextureTROPHY[nCntTROPHY]->Release();
			g_apTextureTROPHY[nCntTROPHY] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTROPHY != NULL)
	{
		g_pVtxBuffTROPHY->Release();
		g_pVtxBuffTROPHY = NULL;
	}

}
//============================================================
//トロフィーの更新処理
//============================================================
void UpdateTrophy(void)
{
	UpdateGetScore();
	int nCntTROPHY;
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	g_nTROPHYCouter++;			//敵の間隔

	if (g_nTROPHYCouter == 60)
	{
		SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 6);
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_fanfare);
		AddScore(100);
		AddGetTrophy(1);
		AddGetScore(13);
	}

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == true)
		{//鳥が出現される

		 //鳥の位置の更新

			g_aTROPHY[nCntTROPHY].pos += g_aTROPHY[nCntTROPHY].move;

			//頂点座標の更新(鳥の大きさ）
			pVtx[0].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y - TROPHY_SIZE / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y - TROPHY_SIZE / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y + TROPHY_SIZE / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y + TROPHY_SIZE / 2, 0.0f);

			if (g_aTROPHY[nCntTROPHY].pos.x <= 6)

			{//画面外に鳥が出た時
				g_aTROPHY[nCntTROPHY].bUse = false;
			}
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffTROPHY->Unlock();
}

//============================================================
//トロフィー描画処理
//============================================================
void DrawTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTROPHY;
	DrawGetScore();
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTROPHY, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == true)
		{//敵が使用されている

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTROPHY[g_aTROPHY[nCntTROPHY].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTROPHY * 4, 2);
		}
	}
}

//============================================================
//トロフィーの設定処理
//============================================================
void SetTrophy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntTROPHY;

	VERTEX_2D*pVtx;

	//頂点バッファロックし、頂点情報へポインタ取得
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == false)
		{//敵が使用されてない場合

		 //敵の情報の設定
			g_aTROPHY[nCntTROPHY].pos = pos;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - 6.0f, g_aTROPHY[nCntTROPHY].pos.y - 6.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + 6.0f, g_aTROPHY[nCntTROPHY].pos.y - 6.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - 6.0f, g_aTROPHY[nCntTROPHY].pos.y + 6.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + 6.0f, g_aTROPHY[nCntTROPHY].pos.y + 6.0f, 0.0f);


			//頂点カラーの描画
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aTROPHY[nCntTROPHY].move = move;
			g_aTROPHY[nCntTROPHY].nLife = 10;
			g_aTROPHY[nCntTROPHY].bUse = true;	//使用している状態にする
			g_aTROPHY[nCntTROPHY].nType = nType;
			
			break;
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtxBuffTROPHY->Unlock();
}
//トロフィーの処理
void HitTrophy(int nCntTROPHY, int nDamage)
{
	g_aTROPHY[nCntTROPHY].nLife -= nDamage;

	if (g_aTROPHY[nCntTROPHY].nLife <= 0)
	{

		g_aTROPHY[nCntTROPHY].bUse = false;
	}
	else
	{
		g_aTROPHY[nCntTROPHY].state = TROPHYSTA_DAMAGE;
		g_aTROPHY[nCntTROPHY].nCounterState = 15;

		VERTEX_2D*pVtx;

		//頂点バッファをロックし、頂点情報へポインタ取得
		g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntTROPHY;//ポインタを４つ分進める

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//頂点バッファアンロック
		g_pVtxBuffTROPHY->Unlock();
	}
}
