//============================================================
//
// 3D制作　モデル処理[model.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>
//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//減衰係数
#define MAX_MODEL	(128)					//モデルの最大数
#define NUM_MODEL	(23)					//モデル数
//============================================================
//グローバル変数
//============================================================

//↓modelinfo構造体
typedef struct
{
	LPD3DXMESH			 MeshModel;
	LPD3DXBUFFER		 pBuffMatModel;
	DWORD				nNumMatModel;
	D3DXVECTOR3			VtxMinModel;		//最小値　min[MAX_MODEL_TYPE]
	D3DXVECTOR3			VtxMaxModel;		//最大値　max[MAX_MODEL_TYPE]

}ModelLinfo;

//↓modelinfo構造体の配列を宣言する
D3DXMATRIX g_mtxWorldModel;
Model g_Model[MAX_MODEL];
ModelLinfo g_ModelInfo[NUM_MODEL];

//============================================================
//　モデルの初期化処理
//============================================================
void lnitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntModel;

	memset(&g_ModelInfo, 0, sizeof(g_ModelInfo));
	memset(&g_Model, 0, sizeof(g_Model));
	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/kabe4.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[0].pBuffMatModel,
		NULL,
		&g_ModelInfo[0].nNumMatModel,
		&g_ModelInfo[0].MeshModel);//block001.x,ie.x

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/kabe3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[1].pBuffMatModel,
		NULL,
		&g_ModelInfo[1].nNumMatModel,
		&g_ModelInfo[1].MeshModel);

	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/ie.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[2].pBuffMatModel,
		NULL,
		&g_ModelInfo[2].nNumMatModel,
		&g_ModelInfo[2].MeshModel);
								
	D3DXLoadMeshFromX("data/MODEL/yuka.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[3].pBuffMatModel,
		NULL,
		&g_ModelInfo[3].nNumMatModel,
		&g_ModelInfo[3].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/yuka2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[4].pBuffMatModel,
		NULL,
		&g_ModelInfo[4].nNumMatModel,
		&g_ModelInfo[4].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/yuka3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[5].pBuffMatModel,
		NULL,
		&g_ModelInfo[5].nNumMatModel,
		&g_ModelInfo[5].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kago2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[6].pBuffMatModel,
		NULL,
		&g_ModelInfo[6].nNumMatModel,
		&g_ModelInfo[6].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[7].pBuffMatModel,
		NULL,
		&g_ModelInfo[7].nNumMatModel,
		&g_ModelInfo[7].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/Object.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[8].pBuffMatModel,
		NULL,
		&g_ModelInfo[8].nNumMatModel,
		&g_ModelInfo[8].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue4.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[9].pBuffMatModel,
		NULL,
		&g_ModelInfo[9].nNumMatModel,
		&g_ModelInfo[9].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/ikakago.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[10].pBuffMatModel,
		NULL,
		&g_ModelInfo[10].nNumMatModel,
		&g_ModelInfo[10].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue5.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[11].pBuffMatModel,
		NULL,
		&g_ModelInfo[11].nNumMatModel,
		&g_ModelInfo[11].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[12].pBuffMatModel,
		NULL,
		&g_ModelInfo[12].nNumMatModel,
		&g_ModelInfo[12].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/hako.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[13].pBuffMatModel,
		NULL,
		&g_ModelInfo[13].nNumMatModel,
		&g_ModelInfo[13].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/hako1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[14].pBuffMatModel,
		NULL,
		&g_ModelInfo[14].nNumMatModel,
		&g_ModelInfo[14].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[15].pBuffMatModel,
		NULL,
		&g_ModelInfo[15].nNumMatModel,
		&g_ModelInfo[15].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kanban.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[16].pBuffMatModel,
		NULL,
		&g_ModelInfo[16].nNumMatModel,
		&g_ModelInfo[16].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[17].pBuffMatModel,
		NULL,
		&g_ModelInfo[17].nNumMatModel,
		&g_ModelInfo[17].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[18].pBuffMatModel,
		NULL,
		&g_ModelInfo[18].nNumMatModel,
		&g_ModelInfo[18].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[19].pBuffMatModel,
		NULL,
		&g_ModelInfo[19].nNumMatModel,
		&g_ModelInfo[19].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/miti.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[20].pBuffMatModel,
		NULL,
		&g_ModelInfo[20].nNumMatModel,
		&g_ModelInfo[20].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kadan.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[21].pBuffMatModel,
		NULL,
		&g_ModelInfo[21].nNumMatModel,
		&g_ModelInfo[21].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tonneru.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[22].pBuffMatModel,
		NULL,
		&g_ModelInfo[22].nNumMatModel,
		&g_ModelInfo[22].MeshModel);

	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_Model[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Model[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化
	
		g_Model[nCntModel].bUse = false;
	}

	//↓タイプ数分繰り返す
	for (nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
	{
		g_ModelInfo[nCntModel].VtxMinModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);		//最小値
		g_ModelInfo[nCntModel].VtxMaxModel= D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値

		//頂点数の取得
		nNumVtx = g_ModelInfo[nCntModel].MeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_ModelInfo[nCntModel].MeshModel->GetFVF());

		//頂点バッファをロック
		g_ModelInfo[nCntModel].MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最大値を取得
			if (Vtx.x >g_ModelInfo[nCntModel].VtxMaxModel.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_ModelInfo[nCntModel].VtxMaxModel.x = Vtx.x;
			}

			if (Vtx.y > g_ModelInfo[nCntModel].VtxMaxModel.y)
			{
				g_ModelInfo[nCntModel].VtxMaxModel.y = Vtx.y;
			}

			if (Vtx.z > g_ModelInfo[nCntModel].VtxMaxModel.z)
			{
				g_ModelInfo[nCntModel].VtxMaxModel.z = Vtx.z;
			}

			//頂点座標を比較してモデルの最小値を取得

			if (Vtx.x <g_ModelInfo[nCntModel].VtxMinModel.x)
			{
				g_ModelInfo[nCntModel].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_ModelInfo[nCntModel].VtxMinModel.y)
			{
				g_ModelInfo[nCntModel].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z <g_ModelInfo[nCntModel].VtxMinModel.z)
			{
				g_ModelInfo[nCntModel].VtxMinModel.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_ModelInfo[nCntModel].MeshModel->UnlockVertexBuffer();
	}

//	ModelSet();
	
	FILE*pFile = fopen("data/Simple.txt", "r");

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
			SetModel(D3DXVECTOR3(posX, posY, posZ), D3DXVECTOR3(rotX, rotY, rotZ), type);
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
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
	{ //テクスチャの破棄
	//メッシュの破棄
		if (g_ModelInfo[nCntModel].pBuffMatModel != NULL)
		{
			g_ModelInfo[nCntModel].pBuffMatModel->Release();
			g_ModelInfo[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//============================================================
// モデルのアップデート処理
//============================================================
void UpdateModel(void)
{

}

//============================================================
// モデルの描画処理
//============================================================
void DrawModel(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用
	D3DMATERIAL9 matDef;		//マテリアルの保存
	D3DXMATERIAL *pMat;			//マテリアルの保管

	//現在のマテリアル
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldModel);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].pos.x, g_Model[nCntModel].pos.y, g_Model[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

			ModelLinfo* modelInfo = &g_ModelInfo[g_Model[nCntModel].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)modelInfo->pBuffMatModel->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)modelInfo->nNumMatModel; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				modelInfo->MeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}
//============================================================
// モデルの当たり判定
//============================================================
bool CollisionModel(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)				//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか

	for(int nCntModel=0;nCntModel<MAX_MODEL;nCntModel++)
	{ 
		if (g_Model[nCntModel].bUse == true)//使用している場合
		{
			
			//右の当たり判定
			if (pPos->z - pSize->z <g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z >g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPos->y - pSize->y <g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y &&
				pPos->y + pSize->y >g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y &&

				pPosOld->x >= g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x &&
				pPos->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPos->y - pSize->y < g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y &&
				pPos->y + pSize->y > g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y &&

				pPosOld->x <= g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x &&
				pPos->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//下面の当たり判定
			if (pPos->x - pSize->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x &&
				pPos->x + pSize->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x &&

				pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPosOld->y <= g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y &&
				pPos->y > g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y)
				//ブロックにめり込んだ
			{
				pPos->y = g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y;
				pMove->y = 0.0f;
			}
		
			//上面の当たり判定
			if (pPos->x - pSize->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x &&
				pPos->x + pSize->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x &&

				pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPosOld->y >= g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y &&
				pPos->y < g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y)
				//ブロックにめり込んだ
			{
				bIsLanding = true;
				pPos->y = g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}		
	}

	return bIsLanding;
}
//============================================================
// モデルの設定処理
//============================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)	//type追加
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == false)
		{//ブロックが使用されてない場合
			g_Model[nCntModel].pos = pos;
			g_Model[nCntModel].rot = rot;
			g_Model[nCntModel].bUse = true;	//使用している状態にする
			g_Model[nCntModel].nType = nType;

			g_Model[nCntModel].size.x = (g_ModelInfo[nType].VtxMaxModel.x - g_ModelInfo[nType].VtxMinModel.x) / 2.0f;
			g_Model[nCntModel].size.y = (g_ModelInfo[nType].VtxMaxModel.y - g_ModelInfo[nType].VtxMinModel.y) ;
			g_Model[nCntModel].size.z = (g_ModelInfo[nType].VtxMaxModel.z - g_ModelInfo[nType].VtxMinModel.z) / 2.0f;

			break;		//(for文を抜ける)
		}		
	}
}
//============================================================
// モデルの配置
//============================================================
void ModelSet(void)
{
	
}

Model*GetModel(void)
{
	return &g_Model[0];
}


