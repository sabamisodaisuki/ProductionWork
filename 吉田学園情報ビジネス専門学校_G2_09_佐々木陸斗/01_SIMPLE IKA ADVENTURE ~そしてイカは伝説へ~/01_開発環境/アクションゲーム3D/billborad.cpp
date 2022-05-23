//============================================================
//
//  ビルボード[billborad.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "billborad.h"
#include "main.h"

//============================================================
//マクロ定義
//============================================================
#define MAX_Billborad		(256)		//ビルボードの最大数
#define Billborad_SIZE_X	(60)	//ビルボードのサイズ
#define Billborad_SIZE_Y 	(60)		//ビルボードのサイズ
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureBillborad = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillborad = NULL;		// 頂点バッファへのポインタ
Billborad g_aEffect[MAX_Billborad];						//エフェクト数

//============================================================
// ビルボードの初期化
//============================================================
void lnitBillborad(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBillborad;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETUMEI.jpg",
		&g_pTextureBillborad);

	//ビルボードの情報の初期化
	for (nCntBillborad = 0; nCntBillborad< MAX_Billborad; nCntBillborad++)
	{
		g_aEffect[nCntBillborad].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntBillborad].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntBillborad].bUse = false;
	}
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Billborad,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillborad,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
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
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの描画
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffBillborad->Unlock();

	//ビルボード位置
	SetBillborad(D3DXVECTOR3(30.0f, 400.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (100.0f), (100.0f));
}

//============================================================
// ビルボードの終了処理
//============================================================
void UninitBillborad(void)
{
	//テクスチャの破棄
	if (g_pTextureBillborad != NULL)
	{
		g_pTextureBillborad->Release();
		g_pTextureBillborad = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBillborad != NULL)
	{
		g_pVtxBuffBillborad->Release();
		g_pVtxBuffBillborad = NULL;
	}
}

//============================================================
// ビルボードの更新処理
//============================================================
void UpdateBillborad(void)
{
	//使用無し
}

//============================================================
// ビルボードの設定
//============================================================
void SetBillborad(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	int nCntBillborad;

	VERTEX_3D*pVtx;

	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
	{
		if (g_aEffect[nCntBillborad].bUse == false)
		{//ビルボードが使用されてない場合
			g_aEffect[nCntBillborad].pos = pos;				//位置
			g_aEffect[nCntBillborad].fWidth = fWidth;		//幅
			g_aEffect[nCntBillborad].fHeight = fHeight;		//高さ
			g_aEffect[nCntBillborad].rot = rot;				//向き

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntBillborad].fWidth / 2.0f, g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntBillborad].fWidth / 2.0f, g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntBillborad].fWidth / 2.0f, -g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntBillborad].fWidth / 2.0f, -g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);

			g_aEffect[nCntBillborad].bUse = true;	//使用している状態にする

			break;		//(for文を抜ける)
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtxBuffBillborad->Unlock();
}

//============================================================
// ビルボードの描画処理
//============================================================
void DrawBillborad(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);//ビューマトリックスの取得

	for (int nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
	{
		if (g_aEffect[nCntBillborad].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntBillborad].mtxWorld);
			pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//カメラ逆例を設定
			g_aEffect[nCntBillborad].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntBillborad].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntBillborad].mtxWorld._13 = mtxView._31;
			/*g_aEffect[nCntBillborad].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntBillborad].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntBillborad].mtxWorld._23 = mtxView._32;*/
			g_aEffect[nCntBillborad].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntBillborad].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntBillborad].mtxWorld._33 = mtxView._33;

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntBillborad].rot.y, g_aEffect[nCntBillborad].rot.x, g_aEffect[nCntBillborad].rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntBillborad].mtxWorld, &g_aEffect[nCntBillborad].mtxWorld, &mtxRot);

			//位置を反映.
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntBillborad].pos.x, g_aEffect[nCntBillborad].pos.y, g_aEffect[nCntBillborad].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntBillborad].mtxWorld, &g_aEffect[nCntBillborad].mtxWorld, &mtxTrans);

			//ライトの無効
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntBillborad].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillborad, 0, sizeof(VERTEX_3D));

			//頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillborad);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillborad * 4, 2);

			//元に戻す
			pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ライトの有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}