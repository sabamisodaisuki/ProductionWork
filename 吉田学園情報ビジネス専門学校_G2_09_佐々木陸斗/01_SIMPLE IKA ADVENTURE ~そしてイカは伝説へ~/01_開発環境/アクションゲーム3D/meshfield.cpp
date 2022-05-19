//============================================================
//
// 3Dメッシュ処理 [Meshfield.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "Meshfield.h"
#include "main.h"
#include "input.h"
#define MESHFIELD_X_BLOCK	(55)		//x方向のブロック
#define MESHFIELD_Z_BLOCK	(55)		//Z方向のブロック	
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))
#define MESHFIELD_INDEX_NUM	((MESHFIELD_X_BLOCK+1)*2*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)
#define MESHFIELD_PRIMITVE_NUM	(MESHFIELD_X_BLOCK*MESHFIELD_Z_BLOCK*2+(MESHFIELD_Z_BLOCK-1)*4)
#define MESHFIELD_FWIDTH	(60.0f)		//幅
#define MESHFIELD_FHEIGHT	(60.0f)		//奥行
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		//メッシュのテクスチャ
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshfield = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshfield;							// 位置
D3DXVECTOR3 g_rotMeshfield;							// 向き
D3DXMATRIX g_mtxWorldMeshfield;						// ワールドマトリックス
MESHFIELD g_Meshfield;
//メッシュの取得
MESHFIELD*GetMeshfield(void)
{
	return &g_Meshfield;
}
//============================================================
// メッシュの初期化
//============================================================
void lnitMeshfield(void)
{
	int nCntZ;
	int nCntX;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/1.png",
		&g_pTextureMeshfield);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK+1; nCntZ++)
	{
		for ( nCntX = 0; nCntX < MESHFIELD_X_BLOCK+1; nCntX++)
		{
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3((MESHFIELD_FWIDTH*nCntX- MESHFIELD_FHEIGHT), 0.0f, (-MESHFIELD_FHEIGHT* nCntZ+MESHFIELD_FWIDTH));

			pVtx[0].tex = D3DXVECTOR2((1.0f/MESHFIELD_X_BLOCK)*nCntX,(1.0f / MESHFIELD_Z_BLOCK)* nCntZ );

			//各頂点の法線の設定
		
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			//頂点カラーの描画
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f,1.0f);

			pVtx++;
		}
	}
	//頂点バッファアンロック
	g_pVtxBuffMeshfield->Unlock();
	//インデックスバッファをポインタ
	WORD*pldx;

	//インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshfield,
		NULL);

	//インデックスバッファをロックし、頂点情報へポインタ取得
	g_pldxBuffMeshfield->Lock(0, 0, (void**)&pldx, 0);

	for (nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK; nCntZ++)
	{
		for (nCntX = 0; nCntX <= MESHFIELD_X_BLOCK ; nCntX++)
		{
			//インデックスの設定

			//X列下段
			pldx[0] = (WORD)nCntX + (MESHFIELD_X_BLOCK + 1) * (nCntZ + 1);
			pldx[1] = (WORD)nCntX + (MESHFIELD_X_BLOCK + 1) * nCntZ;
			pldx += 2;

		}
		if (nCntZ<MESHFIELD_Z_BLOCK-1)
		{
			//X列の上段
			pldx[0] = pldx[-1];
			pldx[1] = (WORD)((MESHFIELD_X_BLOCK+1)*(nCntZ+2));
			pldx+=2;
		}
	}
		//インデックスをアンロック
		g_pldxBuffMeshfield->Unlock();
	
}

//============================================================
// メッシュの終了処理
//============================================================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//インデックスバッファを開放
	if (g_pldxBuffMeshfield != NULL)
	{
		g_pldxBuffMeshfield->Release();
		g_pldxBuffMeshfield = NULL;
	}

}

//============================================================
// メッシュの更新処理
//============================================================
void UpdateMeshfield(void)
{
	
}

//============================================================
// メッシュの描画処理
//============================================================
void DrawMeshfield(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pldxBuffMeshfield);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//メッシュの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの関係
		0,												//描画する最初の頂点
		0,												//インデックスの最小値
		MESHFIELD_VERTEX_NUM,							//頂点数
		0,												//インデックスの最初の数
		MESHFIELD_PRIMITVE_NUM);						//プリミティブ数
}