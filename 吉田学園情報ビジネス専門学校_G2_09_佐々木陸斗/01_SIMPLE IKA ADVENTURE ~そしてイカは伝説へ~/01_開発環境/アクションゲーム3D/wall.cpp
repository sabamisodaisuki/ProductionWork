//============================================================
//
// 3D壁の処理 [wall.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "wall.h"
#include "main.h"

//============================================================
//マクロ定義
//============================================================
#define MAX_WALL		(256)	//壁の最大数
#define WALL_SIZE_X		(60)	//壁のサイズ
#define WALL_SIZE_Y 	(60)	//壁のサイズ
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// 頂点バッファへのポインタ
Wall g_aWall[MAX_WALL];							//影

 //壁の取得
Wall*GetWall(void)
{
	return &g_aWall[0];
}
//============================================================
// 壁の初期化
//============================================================
void lnitWall(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntWall;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/9.png",			
		&g_pTextureWall);

	//影の情報の初期化
	for (nCntWall = 0; nCntWall< MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
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
	g_pVtxBuffWall->Unlock();

	
	ZZWall();
}


//============================================================
// 壁の終了処理
//============================================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//============================================================
// 影の更新処理
//============================================================
void UpdateWall(void)
{

}

//============================================================
// 壁の設定
//============================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fcol)
{
	int nCntWall;
	VERTEX_3D*pVtx;
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{//壁が使用されてない場合
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].fWidth = fWidth;//幅
			g_aWall[nCntWall].fHeight = fHeight;//高さ
			g_aWall[nCntWall].rot = rot;		//向き
			

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth / 2.0f,	g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aWall[nCntWall].fWidth / 2.0f, g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth / 2.0f, -g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aWall[nCntWall].fWidth / 2.0f,	-g_aWall[nCntWall].fHeight / 2.0f, 0.0f);

			//頂点カラーの初期化
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);

			g_aWall[nCntWall].bUse = true;	//使用している状態にする

			break;		//(for文を抜ける)
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtxBuffWall->Unlock();
}

//============================================================
// 影の描画処理
//============================================================
void DrawWall(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映.
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
	
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//============================================================
// 壁のまとめ処理
//============================================================
void ZZWall(void)
{
	//壁位置
	SetWall(D3DXVECTOR3(60.0f, 50.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (240.0f), (100.0f), (1.0f));

	//壁位置
	SetWall(D3DXVECTOR3(60.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), (240.0f), (100.0f), (1.0f));

	//壁位置
	SetWall(D3DXVECTOR3(-60.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.5f, 0.0f), (240.0f), (100.0f), (1.0f));

	//壁位置
	SetWall(D3DXVECTOR3(180.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), (240.0f), (100.0f), (1.0f));


	//壁位置
	SetWall(D3DXVECTOR3(60.0f, 50.0f, 60.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), (240.0f), (100.0f), (0.2f));//上

	//壁位置
	SetWall(D3DXVECTOR3(60.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (240.0f), (100.0f), (0.2f));//下

	 //壁位置
	SetWall(D3DXVECTOR3(-60.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), (240.0f), (100.0f), (0.2f));//左

	//壁位置
	SetWall(D3DXVECTOR3(180.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.5f, 0.0f), (240.0f), (100.0f), (0.2f));//右
}