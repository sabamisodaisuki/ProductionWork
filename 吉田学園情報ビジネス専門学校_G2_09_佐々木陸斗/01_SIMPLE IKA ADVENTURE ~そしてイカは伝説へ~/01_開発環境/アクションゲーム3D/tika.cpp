//============================================================
//
// 3D制作　地下モデル処理[Tika.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "tika.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>

//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//減衰係数
#define MAX_TIKA	(128)					//モデルの最大数
#define NUM_TIKA	(2)						//モデル数
//============================================================
//グローバル変数
//============================================================
typedef struct
{
	LPD3DXMESH			 MeshTika;
	LPD3DXBUFFER		 pBuffMatTika;
	DWORD				nNumMatTika;
	D3DXVECTOR3			VtxMinTika;		//最小値
	D3DXVECTOR3			VtxMaxTika;		//最大値

}TikaLinfo;

////↓Tikainfo構造体の配列を宣言する
D3DXMATRIX g_mtxWorldTika;
Tika g_Tika[MAX_TIKA];
TikaLinfo g_TikaInfo[NUM_TIKA];

//============================================================
//　地下モデルの初期化処理
//============================================================
void lnitTika(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTika;

	memset(&g_TikaInfo, 0, sizeof(g_TikaInfo));
	memset(&g_Tika, 0, sizeof(g_Tika));

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/tikakabe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_TikaInfo[0].pBuffMatTika,
		NULL,
		&g_TikaInfo[0].nNumMatTika,
		&g_TikaInfo[0].MeshTika);
	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/tikayuka.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_TikaInfo[1].pBuffMatTika,
		NULL,
		&g_TikaInfo[1].nNumMatTika,
		&g_TikaInfo[1].MeshTika);

	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	for (nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		g_Tika[nCntTika].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Tika[nCntTika].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Tika[nCntTika].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化

		g_Tika[nCntTika].bUse = false;
	}

	//↓タイプ数分繰り返す
	for (nCntTika = 0; nCntTika < NUM_TIKA; nCntTika++)
	{
		g_TikaInfo[nCntTika].VtxMinTika = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//最小値
		g_TikaInfo[nCntTika].VtxMaxTika = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値

																						//頂点数の取得
		nNumVtx = g_TikaInfo[nCntTika].MeshTika->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_TikaInfo[nCntTika].MeshTika->GetFVF());

		//頂点バッファをロック
		g_TikaInfo[nCntTika].MeshTika->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最大値を取得
			if (Vtx.x >g_TikaInfo[nCntTika].VtxMaxTika.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_TikaInfo[nCntTika].VtxMaxTika.x = Vtx.x;
			}

			if (Vtx.y > g_TikaInfo[nCntTika].VtxMaxTika.y)
			{
				g_TikaInfo[nCntTika].VtxMaxTika.y = Vtx.y;
			}

			if (Vtx.z > g_TikaInfo[nCntTika].VtxMaxTika.z)
			{
				g_TikaInfo[nCntTika].VtxMaxTika.z = Vtx.z;
			}

			//頂点座標を比較してモデルの最小値を取得

			if (Vtx.x <g_TikaInfo[nCntTika].VtxMinTika.x)
			{
				g_TikaInfo[nCntTika].VtxMinTika.x = Vtx.x;
			}

			if (Vtx.y < g_TikaInfo[nCntTika].VtxMinTika.y)
			{
				g_TikaInfo[nCntTika].VtxMinTika.y = Vtx.y;
			}

			if (Vtx.z <g_TikaInfo[nCntTika].VtxMinTika.z)
			{
				g_TikaInfo[nCntTika].VtxMinTika.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_TikaInfo[nCntTika].MeshTika->UnlockVertexBuffer();
	}

	//	TikaSet();

	FILE*pFile = fopen("data/tika.txt", "r");

	//情報を外部ファイルから読み込む
	if (pFile != NULL)
	{
		float posX;
		float posY;
		float posZ;
		float rotX;
		float rotY;
		float rotZ;
		int type;
		char comment[1024];

		while (true)
		{
			int ret = fscanf(pFile, "%f %f %f %f %f %f %d %s", &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &type, comment);
			if (ret == EOF)
			{
				break;
			}
			SetTika(D3DXVECTOR3(posX, posY, posZ), D3DXVECTOR3(rotX, rotY, rotZ), type);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("***ファイルが開けませんでした***\n\n");
	}
}

//============================================================
//　終了処理
//============================================================
void UninitTika(void)
{
	for (int nCntTika = 0; nCntTika < NUM_TIKA; nCntTika++)
	{ //テクスチャの破棄
	  //メッシュの破棄
		if (g_TikaInfo[nCntTika].pBuffMatTika != NULL)
		{
			g_TikaInfo[nCntTika].pBuffMatTika->Release();
			g_TikaInfo[nCntTika].pBuffMatTika = NULL;
		}
	}
}

//============================================================
// 地下モデルのアップデート処理
//============================================================
void UpdateTika(void)
{

}

//============================================================
// 地下モデルの描画処理
//============================================================
void DrawTika(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//マテリアルの保存
	D3DXMATERIAL *pMat;				//マテリアルの保管

	 //現在のマテリアル
	pDevice->GetMaterial(&matDef);

	for (int nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldTika);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Tika[nCntTika].rot.x, g_Tika[nCntTika].rot.y, g_Tika[nCntTika].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldTika, &g_mtxWorldTika, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Tika[nCntTika].pos.x, g_Tika[nCntTika].pos.y, g_Tika[nCntTika].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldTika, &g_mtxWorldTika, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTika);

			TikaLinfo* TikaInfo = &g_TikaInfo[g_Tika[nCntTika].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)TikaInfo->pBuffMatTika->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)TikaInfo->nNumMatTika; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				TikaInfo->MeshTika->DrawSubset(nCntMat);
			}
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}
//============================================================
// 地下モデルの当たり判定
//============================================================
bool CollisionTika(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)				//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか

	for (int nCntTika = 0; nCntTika<MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == true)//使用している場合
		{

			//右の当たり判定
			if (pPos->z - pSize->z <g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z >g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPos->y - pSize->y <g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y &&
				pPos->y + pSize->y >g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y &&

				pPosOld->x >= g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x &&
				pPos->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPos->y - pSize->y < g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y &&
				pPos->y + pSize->y > g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y &&

				pPosOld->x <= g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x &&
				pPos->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//下面の当たり判定
			if (pPos->x - pSize->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x &&
				pPos->x + pSize->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x &&

				pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPosOld->y <= g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y &&
				pPos->y > g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y)
				//ブロックにめり込んだ
			{
				pPos->y = g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y;
				pMove->y = 0.0f;
			}

			//上面の当たり判定
			if (pPos->x - pSize->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x &&
				pPos->x + pSize->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x &&

				pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPosOld->y >= g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y &&
				pPos->y < g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y)
				//ブロックにめり込んだ
			{
				bIsLanding = true;
				pPos->y = g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}
	}

	return bIsLanding;
}
//============================================================
// 地下モデルの設定処理
//============================================================
void SetTika(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == false)
		{//ブロックが使用されてない場合
			g_Tika[nCntTika].pos = pos;
			g_Tika[nCntTika].rot = rot;
			g_Tika[nCntTika].bUse = true;	//使用している状態にする
			g_Tika[nCntTika].nType = nType;

			g_Tika[nCntTika].size.x = (g_TikaInfo[nType].VtxMaxTika.x - g_TikaInfo[nType].VtxMinTika.x) / 2.0f;
			g_Tika[nCntTika].size.y = (g_TikaInfo[nType].VtxMaxTika.y - g_TikaInfo[nType].VtxMinTika.y);
			g_Tika[nCntTika].size.z = (g_TikaInfo[nType].VtxMaxTika.z - g_TikaInfo[nType].VtxMinTika.z) / 2.0f;

			break;		//(for文を抜ける)
		}
	}
}
//============================================================
// モデルの配置
//============================================================
void TikaSet(void)
{

}
Tika*GetTika(void)
{
	return &g_Tika[0];
}

