//============================================================
//
// 3D制作　ゴール処理[Goal.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "Goal.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include"fade.h"
#include"HighScore.h"
#include <stdio.h>

//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//減衰係数
#define MAX_MODEL	(128)					//モデルの最大数
#define NUM_MODEL	(2)						//モデル数
//============================================================
//グローバル変数
//============================================================

typedef struct
{
	LPD3DXMESH			 MeshGoal;
	LPD3DXBUFFER		 pBuffMatGoal;
	DWORD				nNumMatGoal;
	D3DXVECTOR3			VtxMinGoal;		//最小値　min[MAX_MODEL_TYPE]
	D3DXVECTOR3			VtxMaxGoal;		//最大値　max[MAX_MODEL_TYPE]

}GoalLinfo;

D3DXMATRIX g_mtxWorldGoal;
Goal g_Goal[MAX_MODEL];
GoalLinfo g_GoalInfo[NUM_MODEL];

//============================================================
//ゴールの初期化処理
//============================================================
void lnitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntGoal;

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/kabe2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GoalInfo[0].pBuffMatGoal,
		NULL,
		&g_GoalInfo[0].nNumMatGoal,
		&g_GoalInfo[0].MeshGoal);

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/GOAL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GoalInfo[1].pBuffMatGoal,
		NULL,
		&g_GoalInfo[1].nNumMatGoal,
		&g_GoalInfo[1].MeshGoal);

	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	for (nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Goal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Goal[nCntGoal].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化

		g_Goal[nCntGoal].bUse = false;
	}

	for (int CntGoal = 0; CntGoal < NUM_MODEL; CntGoal++)
	{
		g_GoalInfo[nCntGoal].VtxMinGoal = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//最小値
		g_GoalInfo[nCntGoal].VtxMaxGoal = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値
	}

	//↓タイプ数分繰り返す
	for (nCntGoal = 0; nCntGoal < NUM_MODEL; nCntGoal++)
	{
		//頂点数の取得
		nNumVtx = g_GoalInfo[nCntGoal].MeshGoal->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_GoalInfo[nCntGoal].MeshGoal->GetFVF());

		//頂点バッファをロック
		g_GoalInfo[nCntGoal].MeshGoal->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最大値を取得
			if (Vtx.x >g_GoalInfo[nCntGoal].VtxMaxGoal.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_GoalInfo[nCntGoal].VtxMaxGoal.x = Vtx.x;
			}

			if (Vtx.y > g_GoalInfo[nCntGoal].VtxMaxGoal.y)
			{
				g_GoalInfo[nCntGoal].VtxMaxGoal.y = Vtx.y;
			}

			if (Vtx.z > g_GoalInfo[nCntGoal].VtxMaxGoal.z)
			{
				g_GoalInfo[nCntGoal].VtxMaxGoal.z = Vtx.z;
			}

			//頂点座標を比較してモデルの最小値を取得

			if (Vtx.x <g_GoalInfo[nCntGoal].VtxMinGoal.x)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.x = Vtx.x;
			}

			if (Vtx.y < g_GoalInfo[nCntGoal].VtxMinGoal.y)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.y = Vtx.y;
			}

			if (Vtx.z <g_GoalInfo[nCntGoal].VtxMinGoal.z)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_GoalInfo[nCntGoal].MeshGoal->UnlockVertexBuffer();
	}
	GoalSet();
}

//============================================================
//　終了処理
//============================================================
void UninitGoal(void)
{
	for (int nCntGoal = 0; nCntGoal < NUM_MODEL; nCntGoal++)
	{
		 //メッシュの破棄
		if (g_GoalInfo[nCntGoal].pBuffMatGoal != NULL)
		{
			g_GoalInfo[nCntGoal].pBuffMatGoal->Release();
			g_GoalInfo[nCntGoal].pBuffMatGoal = NULL;
		}
	}
}

//============================================================
// ゴールのアップデート処理
//============================================================
void UpdateGoal(void)
{

}

//============================================================
// ゴールの描画処理
//============================================================
void DrawGoal(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//マテリアルの保存
	D3DXMATERIAL *pMat;				//マテリアルの保管

	 //現在のマテリアル
	pDevice->GetMaterial(&matDef);

	for (int nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldGoal);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Goal[nCntGoal].rot.x, g_Goal[nCntGoal].rot.y, g_Goal[nCntGoal].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldGoal, &g_mtxWorldGoal, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Goal[nCntGoal].pos.x, g_Goal[nCntGoal].pos.y, g_Goal[nCntGoal].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldGoal, &g_mtxWorldGoal, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGoal);

			GoalLinfo* GoalInfo = &g_GoalInfo[g_Goal[nCntGoal].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)GoalInfo->pBuffMatGoal->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)GoalInfo->nNumMatGoal; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				GoalInfo->MeshGoal->DrawSubset(nCntMat);
			}
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}
//============================================================
// ゴールの当たり判定
//============================================================
bool CollisionGoal(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)				//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか

	// フェード情報の取得
	FADE fade = GetFade();

	for (int nCntGoal = 0; nCntGoal<MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)//使用している場合
		{

			//右の当たり判定
			if (pPos->z - pSize->z <g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z >g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPos->y - pSize->y <g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y &&
				pPos->y + pSize->y >g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y &&

				pPosOld->x >= g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x &&
				pPos->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPos->y - pSize->y < g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y &&
				pPos->y + pSize->y > g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y &&

				pPosOld->x <= g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x &&
				pPos->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x;
				pMove->x = 0.0f;
			}


			//下面の当たり判定
			if (pPos->x - pSize->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x &&
				pPos->x + pSize->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x &&

				pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPosOld->y <= g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y &&
				pPos->y > g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y)
				//ブロックにめり込んだ
			{
				pPos->y = g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y;
				pMove->y = 0.0f;
			}

			//上面の当たり判定
			if (pPos->x - pSize->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x &&
				pPos->x + pSize->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x &&

				pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPosOld->y >= g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y &&
				pPos->y < g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y&& fade == FADE_NONE)
				//ブロックにめり込んだ
			{
				bIsLanding = true;
				SaveHigeScore();//スコア保存
				pPos->y = g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y;
				pMove->y = 0.0f;
				//モード設定(ゲーム画面に移行)
				SetFade(MODE_RESULT);
			}
		}
	}

	return bIsLanding;
}

//============================================================
//ゴールの設定処理
//============================================================
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)	
{
	for (int nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == false)
		{//ブロックが使用されてない場合
			g_Goal[nCntGoal].pos = pos;
			g_Goal[nCntGoal].rot = rot;
			g_Goal[nCntGoal].bUse = true;	//使用している状態にする
			g_Goal[nCntGoal].nType = nType;

			g_Goal[nCntGoal].size.x = (g_GoalInfo[nType].VtxMaxGoal.x - g_GoalInfo[nType].VtxMinGoal.x) / 2.0f;
			g_Goal[nCntGoal].size.y = (g_GoalInfo[nType].VtxMaxGoal.y - g_GoalInfo[nType].VtxMinGoal.y);
			g_Goal[nCntGoal].size.z = (g_GoalInfo[nType].VtxMaxGoal.z - g_GoalInfo[nType].VtxMinGoal.z) / 2.0f;

			break;		//(for文を抜ける)
		}
	}
}

void GoalSet(void)
{
	SetGoal(D3DXVECTOR3(500.0f, 10.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//壁奥

	SetGoal(D3DXVECTOR3(4700.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);//床3
}

