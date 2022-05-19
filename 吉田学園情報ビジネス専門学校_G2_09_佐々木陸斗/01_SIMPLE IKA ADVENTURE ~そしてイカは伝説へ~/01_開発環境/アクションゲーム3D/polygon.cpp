//============================================================
//
// 3Dポリゴン処理 [polygon.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "polygon.h"
#include "main.h"
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	// 頂点バッファへのポインタ
D3DXVECTOR3 g_posPolygon;							// 位置
D3DXVECTOR3 g_rotPolygon;							// 向き
D3DXMATRIX g_mtxWorldPolygon;						// ワールドマトリックス
//============================================================
// ポリゴンの初期化
//============================================================
void lnitPolygon(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -50.0f);

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

	//頂点バッファアンロック
	g_pVtxBuffPolygon->Unlock();
}


//============================================================
// ポリゴンの終了処理
//============================================================
void UninitPolygon(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//============================================================
// ポリゴンの更新処理
//============================================================
void UpdatePolygon(void)
{

}

//============================================================
// ポリゴンの描画処理
//============================================================
void DrawPolygon(void)
{
	////デバイスを取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//							//ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_mtxWorldPolygon);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	//D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	//D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	////頂点バッファをデバイスのデータストリームに設定
	//pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	////頂点フォーマット設定
	//pDevice->SetFVF(FVF_VERTEX_3D);

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}