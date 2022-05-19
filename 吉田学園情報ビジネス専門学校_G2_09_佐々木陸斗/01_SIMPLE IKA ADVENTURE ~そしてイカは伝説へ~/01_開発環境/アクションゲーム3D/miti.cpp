//============================================================
//
// 3D制作　道処理[Miti.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "miti.h"
#include "MODEL.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>

//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//減衰係数
#define MAX_Miti	(128)					//道の最大数
#define NUM_Miti	(2)						//道数
//============================================================
//グローバル変数
//============================================================

typedef struct
{
	LPD3DXMESH			 MeshMiti;
	LPD3DXBUFFER		 pBuffMatMiti;
	DWORD				nNumMatMiti;
	D3DXVECTOR3			VtxMinMiti;		//最小値　min[MAX_Miti_TYPE]
	D3DXVECTOR3			VtxMaxMiti;		//最大値　max[MAX_Miti_TYPE]

}MitiLinfo;

//↓Mitiinfo構造体の配列を宣言する
D3DXMATRIX g_mtxWorldMiti;
MITI g_Miti[MAX_Miti];
MitiLinfo g_MitiInfo[NUM_Miti];

//============================================================
//　道の初期化処理
//============================================================
void lnitMiti(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntMiti;

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/douro.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MitiInfo[0].pBuffMatMiti,
		NULL,
		&g_MitiInfo[0].nNumMatMiti,
		&g_MitiInfo[0].MeshMiti);//block001.x,ie.x

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/boat.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MitiInfo[1].pBuffMatMiti,
		NULL,
		&g_MitiInfo[1].nNumMatMiti,
		&g_MitiInfo[1].MeshMiti);

	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	for (nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		g_Miti[nCntMiti].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Miti[nCntMiti].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Miti[nCntMiti].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化

		g_Miti[nCntMiti].bUse = false;
	}

	for (int CntMiti = 0; CntMiti < NUM_Miti; CntMiti++)
	{
		g_MitiInfo[CntMiti].VtxMinMiti = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);		//最小値
		g_MitiInfo[CntMiti].VtxMaxMiti = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値
	}

	//↓タイプ数分繰り返す
	for (nCntMiti = 0; nCntMiti < NUM_Miti; nCntMiti++)
	{
		//頂点数の取得
		nNumVtx = g_MitiInfo[nCntMiti].MeshMiti->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_MitiInfo[nCntMiti].MeshMiti->GetFVF());

		//頂点バッファをロック
		g_MitiInfo[nCntMiti].MeshMiti->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較して道の最大値を取得
			if (Vtx.x >g_MitiInfo[nCntMiti].VtxMaxMiti.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_MitiInfo[nCntMiti].VtxMaxMiti.x = Vtx.x;
			}

			if (Vtx.y > g_MitiInfo[nCntMiti].VtxMaxMiti.y)
			{
				g_MitiInfo[nCntMiti].VtxMaxMiti.y = Vtx.y;
			}

			if (Vtx.z > g_MitiInfo[nCntMiti].VtxMaxMiti.z)
			{
				g_MitiInfo[nCntMiti].VtxMaxMiti.z = Vtx.z;
			}

			//頂点座標を比較して道の最小値を取得

			if (Vtx.x <g_MitiInfo[nCntMiti].VtxMinMiti.x)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.x = Vtx.x;
			}

			if (Vtx.y < g_MitiInfo[nCntMiti].VtxMinMiti.y)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.y = Vtx.y;
			}

			if (Vtx.z <g_MitiInfo[nCntMiti].VtxMinMiti.z)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_MitiInfo[nCntMiti].MeshMiti->UnlockVertexBuffer();
	}
	MitiSet();
}

//============================================================
//　終了処理
//============================================================
void UninitMiti(void)
{
	
	for (int nCntMiti = 0; nCntMiti < NUM_Miti; nCntMiti++)
	{ //テクスチャの破棄
	  //メッシュの破棄
		if (g_MitiInfo[nCntMiti].pBuffMatMiti != NULL)
		{
			g_MitiInfo[nCntMiti].pBuffMatMiti->Release();
			g_MitiInfo[nCntMiti].pBuffMatMiti = NULL;
		}
	}
}

//============================================================
// 道のアップデート処理
//============================================================
void UpdateMiti(void)
{

}

//============================================================
// 道の描画処理
//============================================================
void DrawMiti(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用
	D3DMATERIAL9 matDef;//マテリアルの保存
	D3DXMATERIAL *pMat;//マテリアルの保管

					   //現在のマテリアル
	pDevice->GetMaterial(&matDef);

	for (int nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		if (g_Miti[nCntMiti].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldMiti);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Miti[nCntMiti].rot.x, g_Miti[nCntMiti].rot.y, g_Miti[nCntMiti].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldMiti, &g_mtxWorldMiti, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Miti[nCntMiti].pos.x, g_Miti[nCntMiti].pos.y, g_Miti[nCntMiti].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldMiti, &g_mtxWorldMiti, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMiti);

			MitiLinfo* MitiInfo = &g_MitiInfo[g_Miti[nCntMiti].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)MitiInfo->pBuffMatMiti->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)MitiInfo->nNumMatMiti; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//道パーツの描画
				MitiInfo->MeshMiti->DrawSubset(nCntMat);
			}
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}

//============================================================
//道の設定処理
//============================================================
void SetMiti(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)	//type追加
{
	for (int nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		if (g_Miti[nCntMiti].bUse == false)
		{//ブロックが使用されてない場合
			g_Miti[nCntMiti].pos = pos;
			g_Miti[nCntMiti].rot = rot;
			g_Miti[nCntMiti].bUse = true;	//使用している状態にする
			g_Miti[nCntMiti].nType = nType;

			g_Miti[nCntMiti].size.x = (g_MitiInfo[nType].VtxMaxMiti.x - g_MitiInfo[nType].VtxMinMiti.x) / 2.0f;
			g_Miti[nCntMiti].size.y = (g_MitiInfo[nType].VtxMaxMiti.y - g_MitiInfo[nType].VtxMinMiti.y);
			g_Miti[nCntMiti].size.z = (g_MitiInfo[nType].VtxMaxMiti.z - g_MitiInfo[nType].VtxMinMiti.z) / 2.0f;

			break;		//(for文を抜ける)
		}
	}
}

//============================================================
//道の配置
//============================================================
void MitiSet(void)
{
	SetMiti(D3DXVECTOR3(2320.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
	SetMiti(D3DXVECTOR3(2320.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥

	SetMiti(D3DXVECTOR3(2450.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
	SetMiti(D3DXVECTOR3(2450.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥

	SetMiti(D3DXVECTOR3(2600.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
	SetMiti(D3DXVECTOR3(2740.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
	SetMiti(D3DXVECTOR3(2600.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
	SetMiti(D3DXVECTOR3(2740.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥

	SetMiti(D3DXVECTOR3(4500.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);//ボート), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥
}
