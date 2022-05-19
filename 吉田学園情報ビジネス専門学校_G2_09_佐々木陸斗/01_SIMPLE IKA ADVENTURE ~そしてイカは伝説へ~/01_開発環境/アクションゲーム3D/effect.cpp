//============================================================
//
// エフェクトの処理 [effect.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "effect.h"
#include "main.h"
#include "MODEL.h"
#include"billborad.h"

//============================================================
//マクロ定義
//============================================================
#define EFFECT_SIZE_X		(60)	//エフェクトのサイズX
#define EFFECT_SIZE_Y 		(60)	//エフェクトのサイズY
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		// 頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];							//エフェクト

//============================================================
// エフェクトの初期化
//============================================================
void lnitEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntPlayer;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/0.jpg",
		&g_pTextureEffect);

	//エフェクトの情報の初期化
	for (nCntPlayer = 0; nCntPlayer<MAX_EFFECT; nCntPlayer++)
	{
		g_aEffect[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntPlayer].nLife = 0;
		g_aEffect[nCntPlayer].bUse = false;
	}
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer <MAX_EFFECT; nCntPlayer++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffEffect->Unlock();

}

//============================================================
// エフェクトの終了処理
//============================================================
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//============================================================
// エフェクトの更新処理
//============================================================
void UpdateEffect(void)
{
	int nCntPlayer;

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer < MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == true)
		{
			//寿命のカウントダウン
			g_aEffect[nCntPlayer].nLife--;

			//a値を下げる
			g_aEffect[nCntPlayer].col.a -= 0.04f;

			//ライフが0の時
			if (g_aEffect[nCntPlayer].nLife <= 0)
			{
				g_aEffect[nCntPlayer].bUse = false;
			}

		}
		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffEffect->Unlock();
}

//============================================================
// エフェクトの描画処理
//============================================================
void DrawEffect(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;

	////加算合成
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//zプレディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntPlayer].mtxWorld);

			//ライトの無効
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラ逆例を設定
			g_aEffect[nCntPlayer].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntPlayer].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntPlayer].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntPlayer].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntPlayer].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntPlayer].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntPlayer].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntPlayer].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntPlayer].mtxWorld._33 = mtxView._33;

			
			//位置を反映.
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntPlayer].pos.x, g_aEffect[nCntPlayer].pos.y, g_aEffect[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntPlayer].mtxWorld, &g_aEffect[nCntPlayer].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntPlayer].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayer * 4, 2);

			//テクスチャの無効
			pDevice->SetTexture(0, NULL);

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		}
	}
	//aプレディングを元に戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//zプレディングを元に戻す設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
//============================================================
// エフェクトの設定
//============================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int life)
{
	int nCntPlayer;
	VERTEX_3D*pVtx;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer <MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == false)
		{//エフェクトが使用されてない場合
			g_aEffect[nCntPlayer].pos = pos;			//位置
			g_aEffect[nCntPlayer].size = size;			//幅
			g_aEffect[nCntPlayer].col = col;			//カラー
			g_aEffect[nCntPlayer].rot = rot;			//向き
			g_aEffect[nCntPlayer].nLife = life;			//ライフ
			g_aEffect[nCntPlayer].bUse = true;			//使用している状態にする

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, size.z);

			//頂点カラーの初期化
			pVtx[0].col = g_aEffect[nCntPlayer].col;
			pVtx[1].col = g_aEffect[nCntPlayer].col;
			pVtx[2].col = g_aEffect[nCntPlayer].col;
			pVtx[3].col = g_aEffect[nCntPlayer].col;

			break;		//(for文を抜ける)
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtxBuffEffect->Unlock();
}

//============================================================
// エフェクトのまとめ処理
//============================================================
void ZZEffect(void)
{
	
}