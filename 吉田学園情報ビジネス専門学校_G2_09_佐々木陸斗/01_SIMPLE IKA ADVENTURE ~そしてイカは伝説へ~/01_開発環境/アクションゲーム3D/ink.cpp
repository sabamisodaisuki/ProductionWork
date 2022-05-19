//============================================================
//
// 3Dインクの処理 [Ink.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "ink.h"
#include "main.h"

//============================================================
//マクロ定義
//============================================================
#define MAX_Ink		(256)	//インクの最大数
#define Ink_SIZE		(60)	//インクのサイズ

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureInk = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInk = NULL;	// 頂点バッファへのポインタ
Ink g_aInk[MAX_Ink];						//インク

//============================================================
// インクの初期化
//============================================================
void lnitInk(void)
{
	int nCntInk;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ink.png",					//effect000.jpg
		&g_pTextureInk);

	//インクの情報の初期化
	for (nCntInk = 0; nCntInk< MAX_Ink; nCntInk++)
	{
		g_aInk[nCntInk].pos = D3DXVECTOR3(200.0f, -100.0f, 0.0f);
		g_aInk[nCntInk].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].bUse = false;
	}
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Ink,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffInk,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffInk->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-25.0f, 0.0f, 25.0f);
		pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 25.0f);
		pVtx[2].pos = D3DXVECTOR3(-25.0f, 0.0f, -25.0f);
		pVtx[3].pos = D3DXVECTOR3(25.0f, 0.0f, -25.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの描画
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffInk->Unlock();
}

//============================================================
// インクの終了処理
//============================================================
void UninitInk(void)
{
	//テクスチャの破棄
	if (g_pTextureInk != NULL)
	{
		g_pTextureInk->Release();
		g_pTextureInk = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffInk != NULL)
	{
		g_pVtxBuffInk->Release();
		g_pVtxBuffInk = NULL;
	}
}

//============================================================
// インクの更新処理
//============================================================
void UpdateInk(void)
{

}

//============================================================
// インクの設定
//============================================================
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntInk;

	for (nCntInk = 0; nCntInk<MAX_Ink; nCntInk++)
	{
		//bUseがfalseの場合、pos,rotを代入しbUseをtrueにする
		if (g_aInk[nCntInk].bUse == false)
		{
			g_aInk[nCntInk].pos = pos;
			g_aInk[nCntInk].rot = rot;
			g_aInk[nCntInk].bUse = true;
			break;
		}
	}
	return nCntInk;//インクの番号(indexを返す）
}
//============================================================
// インクの位置の更新処理
//============================================================
void SetPositionInk(int nldxInk, D3DXVECTOR3 pos)
{
	//引数で指定された番号のインクのposを設定
	g_aInk[nldxInk].pos = pos;
}
//============================================================
// インクの描画処理
//============================================================
void DrawInk(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		if (g_aInk[nCntInk].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aInk[nCntInk].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aInk[nCntInk].rot.y, g_aInk[nCntInk].rot.x, g_aInk[nCntInk].rot.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxRot);

			//位置を反映.
			D3DXMatrixTranslation(&mtxTrans, g_aInk[nCntInk].pos.x, g_aInk[nCntInk].pos.y, g_aInk[nCntInk].pos.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aInk[nCntInk].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffInk, 0, sizeof(VERTEX_3D));

			//頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureInk);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntInk * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}