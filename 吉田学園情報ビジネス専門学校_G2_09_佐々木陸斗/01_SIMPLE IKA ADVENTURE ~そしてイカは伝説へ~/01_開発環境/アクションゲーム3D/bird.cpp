//============================================================
//
// 3D制作　敵（鳥）の処理[bird.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "bird.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include"MODEL.h"
#include <stdio.h>
#include"player.h"
#include"trophy.h"
#include"sound.h"
#include"Score.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//減衰係数
#define MAX_BIRD	(1235)					//鳥（エネミー）の最大数
#define NUM_BIRD	(2)						//鳥（エネミー）数
#define Bird_G		(0.25f)
//============================================================
//グローバル変数
//============================================================
int g_nBirdCounter;//敵のカウント

typedef struct
{
	//↓構造体にしたい,MAX_BIRD ⇒ MAX_BIRD_TYPE 2
	LPD3DXMESH			 MeshBird;
	LPD3DXBUFFER		 pBuffMatBird;
	DWORD				nNumMatBird;
	D3DXVECTOR3			VtxMinBird;		//最小値　min[MAX_BIRD_TYPE]
	D3DXVECTOR3			VtxMaxBird;		//最大値　max[MAX_BIRD_TYPE]

}BirdLinfo;

////↓Birdinfo構造体の配列を宣言する
D3DXMATRIX g_mtxWorldBird;
Bird g_Bird[MAX_BIRD];
BirdLinfo g_BirdInfo[NUM_BIRD];
int GetCounter;
//============================================================
//　鳥（エネミー）の初期化処理
//============================================================
void lnitBird(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBird;
	g_nBirdCounter = 0;

	D3DXLoadMeshFromX("data/MODEL/bard1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BirdInfo[0].pBuffMatBird,
		NULL,
		&g_BirdInfo[0].nNumMatBird,
		&g_BirdInfo[0].MeshBird);

	D3DXLoadMeshFromX("data/MODEL/bard2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BirdInfo[1].pBuffMatBird,
		NULL,
		&g_BirdInfo[1].nNumMatBird,
		&g_BirdInfo[1].MeshBird);

	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE*pVtxBuff;	//頂点バッファのポインタ

	for (nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		g_Bird[nCntBird].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_Bird[nCntBird].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Bird[nCntBird].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bird[nCntBird].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化

		g_Bird[nCntBird].bUse = false;
	}

	for (int CntBird = 0; CntBird < NUM_BIRD; CntBird++)
	{
		g_BirdInfo[nCntBird].VtxMinBird = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//最小値
		g_BirdInfo[nCntBird].VtxMaxBird = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値
	}

	//↓タイプ数分繰り返す
	for (nCntBird = 0; nCntBird < NUM_BIRD; nCntBird++)
	{
		//頂点数の取得
		nNumVtx = g_BirdInfo[nCntBird].MeshBird->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_BirdInfo[nCntBird].MeshBird->GetFVF());

		//頂点バッファをロック
		g_BirdInfo[nCntBird].MeshBird->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較して鳥（エネミー）の最大値を取得
			if (Vtx.x >g_BirdInfo[nCntBird].VtxMaxBird.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_BirdInfo[nCntBird].VtxMaxBird.x = Vtx.x;
			}

			if (Vtx.y > g_BirdInfo[nCntBird].VtxMaxBird.y)
			{
				g_BirdInfo[nCntBird].VtxMaxBird.y = Vtx.y;
			}

			if (Vtx.z > g_BirdInfo[nCntBird].VtxMaxBird.z)
			{
				g_BirdInfo[nCntBird].VtxMaxBird.z = Vtx.z;
			}

			//頂点座標を比較して鳥（エネミー）の最小値を取得

			if (Vtx.x <g_BirdInfo[nCntBird].VtxMinBird.x)
			{
				g_BirdInfo[nCntBird].VtxMinBird.x = Vtx.x;
			}

			if (Vtx.y < g_BirdInfo[nCntBird].VtxMinBird.y)
			{
				g_BirdInfo[nCntBird].VtxMinBird.y = Vtx.y;
			}

			if (Vtx.z <g_BirdInfo[nCntBird].VtxMinBird.z)
			{
				g_BirdInfo[nCntBird].VtxMinBird.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_BirdInfo[nCntBird].MeshBird->UnlockVertexBuffer();
	}
}

//============================================================
//鳥（エネミー）の終了処理
//============================================================
void UninitBird(void)
{
	for (int nCntBird = 0; nCntBird < NUM_BIRD; nCntBird++)
	{ 
		 //メッシュの破棄
		if (g_BirdInfo[nCntBird].pBuffMatBird != NULL)
		{
			g_BirdInfo[nCntBird].pBuffMatBird->Release();
			g_BirdInfo[nCntBird].pBuffMatBird = NULL;
		}
	}
}

//============================================================
// 鳥（エネミー）のアップデート処理
//============================================================
void UpdateBird(void)
{
	g_nBirdCounter++; //敵の間隔

	if (g_nBirdCounter % 320 == 0)
	{
		SetBird(D3DXVECTOR3(3320.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //車1
		SetBird(D3DXVECTOR3(1850.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //車1
		SetBird(D3DXVECTOR3(3600.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1);//壁奥
		SetBird(D3DXVECTOR3(2200.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1);//壁奥
	}
	else if (g_nBirdCounter % 220 == 0)
	{
		SetBird(D3DXVECTOR3(520.0f, 1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //車1
		SetBird(D3DXVECTOR3(150.0f, 1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //車1
		SetBird(D3DXVECTOR3(1500.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 1);//壁奥
		SetBird(D3DXVECTOR3(1040.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 1);//壁奥
	}
	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		//移動値
		g_Bird[nCntBird].move.y -= Bird_G / 2;
		g_Bird[nCntBird].pos.x += g_Bird[nCntBird].move.x / 2;
		g_Bird[nCntBird].pos.y += g_Bird[nCntBird].move.y / 2;
		g_Bird[nCntBird].pos.z += g_Bird[nCntBird].move.z / 2;
		if (g_Bird[nCntBird].pos.y <= 0.0f)

		{//画面外に鳥が出た時
			g_Bird[nCntBird].bUse = false;
		}
	}
}

//============================================================
// 鳥（エネミー）の描画処理
//============================================================
void DrawBird(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			//計算用
	D3DMATERIAL9 matDef;					//マテリアルの保存
	D3DXMATERIAL *pMat;						//マテリアルの保管

	
	pDevice->GetMaterial(&matDef);			//現在のマテリアル

	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBird);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bird[nCntBird].rot.x, g_Bird[nCntBird].rot.y, g_Bird[nCntBird].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldBird, &g_mtxWorldBird, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bird[nCntBird].pos.x, g_Bird[nCntBird].pos.y, g_Bird[nCntBird].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBird, &g_mtxWorldBird, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBird);

			BirdLinfo* BirdInfo = &g_BirdInfo[g_Bird[nCntBird].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)BirdInfo->pBuffMatBird->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)BirdInfo->nNumMatBird; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//鳥（エネミー）パーツの描画
				BirdInfo->MeshBird->DrawSubset(nCntMat);
			}
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}
//============================================================
// 鳥（エネミー）の当たり判定
//============================================================
bool CollisionBird(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)				//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか

	for (int nCntBird = 0; nCntBird<MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == true)//使用している場合
		{
			Player*pPlayer;
			pPlayer = GetPlayer();

			//右の当たり判定
			if (pPos->z - pSize->z <g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z >g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPos->y - pSize->y <g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y >g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->x >= g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x &&
				pPos->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x;
				pMove->x = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				AddScore(-1);
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddScore(6);
					AddGetTrophy(1);
					AddGetScore(13);
				}
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPos->y - pSize->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->x <= g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x &&
				pPos->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x;
				pMove->x = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddGetTrophy(1);
					AddGetScore(13);
				}

			}

			//下面の当たり判定
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPosOld->y <= g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y &&
				pPos->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y)
				//ブロックにめり込んだ
			{
				pPos->y = g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y;
				pMove->y = 0.0f;

			}
			//正面当たり判定
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->y - pSize->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->z <= g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z - pSize->z &&
				pPos->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z - pSize->z)

				//ブロックにめり込んだ
			{
				pPos->z = g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z - pSize->z;
				pMove->z = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				AddScore(-1);
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddScore(6);
					AddGetTrophy(1);
					AddGetScore(13);
				}

			}

			//上面の当たり判定
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPosOld->y >= g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y &&
				pPos->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y)
				//ブロックにめり込んだ
			{
				bIsLanding = true;
				pPos->y = g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}
	}
	return bIsLanding;
}
//============================================================
// 鳥（エネミー）の設定処理
//============================================================
void SetBird(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)
{
	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == false)
		{//ブロックが使用されてない場合
			g_Bird[nCntBird].pos = pos;		//位置
			g_Bird[nCntBird].rot = rot;		//向き
			g_Bird[nCntBird].move = move;	//移動量
			g_Bird[nCntBird].bUse = true;	//使用している状態にする
			g_Bird[nCntBird].nType = nType;//タイプ分け

			g_Bird[nCntBird].size.x = (g_BirdInfo[nType].VtxMaxBird.x - g_BirdInfo[nType].VtxMinBird.x) / 2.0f;
			g_Bird[nCntBird].size.y = (g_BirdInfo[nType].VtxMaxBird.y - g_BirdInfo[nType].VtxMinBird.y);
			g_Bird[nCntBird].size.z = (g_BirdInfo[nType].VtxMaxBird.z - g_BirdInfo[nType].VtxMinBird.z) / 2.0f;

			break;		//(for文を抜ける)
		}
	}
}
