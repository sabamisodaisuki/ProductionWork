//===========================================================
//
// 3D制作　モデル処理[Player.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "Player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include"meshfield.h"
#include"wall.h"
#include"effect.h"
#include"MODEL.h"
#include"sound.h"
#include"goal.h"
#include"enemy.h"
#include"bird.h"
#include"trophy.h"
#include"tika.h"
#include"Score.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);//減衰係数
#define PLAYER_G	(1.0f)//重力
#define SPEED		(4.5f)//速さ	

//============================================================
//グローバル変数
//============================================================
LPD3DXMESH g_MeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
D3DXVECTOR3 g_rotDestPlayer;
D3DXMATRIX g_mtxWorldPlayer;
DWORD g_nNumMatPlayer = 0;
Player g_Player;
int g_nIdxShadow;
int CntGet;

//プレイヤーの取得
Player*GetPlayer(void)
{
	return &g_Player;
}

//============================================================
//　プレイヤーの初期化処理
//============================================================
void lnitPlayer(void)
{
	Model*pModel;
	pModel = GetModel();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//Xファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/ikao2.x",//使うモデル：MODEL.x,ika.x,Suraimu.x
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_MeshPlayer);

	g_Player.pos = D3DXVECTOR3(30.0f, 420.0f, -590.0f);//位置の初期化...エリア1(30.0f, 420.0f, -590.0f)2,2000.0f, 260.0f, -590.0f,エリア3(3050.0f, 200.0f, -590.0f)
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
	g_rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動値を初期化
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot);
	g_Player.VtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//最小値
	g_Player.VtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値
	
	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	//頂点数の取得
	nNumVtx = g_MeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_MeshPlayer->GetFVF());

	//頂点バッファをロック
	g_MeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標を比較してモデルの最大値を取得
		if (Vtx.x > g_Player.VtxMax.x)
		{
			g_Player.VtxMax.x = Vtx.x;
		}

		if (Vtx.y > g_Player.VtxMax.y)
		{
			g_Player.VtxMax.y = Vtx.y;
		}

		if (Vtx.z > g_Player.VtxMax.z)
		{
			g_Player.VtxMax.z = Vtx.z;
		}

		//頂点座標を比較してモデルの最小値を取得

		if (Vtx.x < g_Player.VtxMin.x)
		{
			g_Player.VtxMin.x = Vtx.x;
		}

		if (Vtx.y < g_Player.VtxMin.y)
		{
			g_Player.VtxMin.y = Vtx.y;
		}

		if (Vtx.z < g_Player.VtxMin.z)
		{
			g_Player.VtxMin.z = Vtx.z;
		}
		//頂点フォーマットのサイズ分ポインタを進めるccc
		pVtxBuff += sizeFVF;
	}
	
	//頂点バッファのアンロック
	g_MeshPlayer->UnlockVertexBuffer();
	//	プレイヤーサイズ
	g_Player.size.x = (g_Player.VtxMax.x - g_Player.VtxMin.x) / 2.0f;
	g_Player.size.y = (g_Player.VtxMax.y - g_Player.VtxMin.y) / 2.0f;
	g_Player.size.z = (g_Player.VtxMax.z - g_Player.VtxMin.z) / 2.0f;
}
//============================================================
//　終了処理
//============================================================
void UninitPlayer(void)
{
	//サウンドの停止
	StopSound();
	//メッシュの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//============================================================
// プレイヤーのアップデート処理
//============================================================
void UpdatePlayer(void)
{
	Camera*pCamera = GetCamera();
	MESHFIELD*pMeshfield=GetMeshfield();	//メッシュの当たり判定用
	//Wall*pWall = GetWall();				//壁の当たり判定用
	Model*pModel;
	pModel = GetModel();
	
	//モデルを初期位置に
	if (GetKeyboardPress(DIK_F1))
	{//F1キーを押した

		g_Player.pos = D3DXVECTOR3(30.0f, 420.0f, -590.0f);
	}

	//モデルを２ステージの位置に
	if (GetKeyboardPress(DIK_P))
	{//F1キーを押した

		g_Player.pos = D3DXVECTOR3(2000.0f, 260.0f, -590.0f);
	}

	//プレイヤーを３ステージの位置に
	if (GetKeyboardPress(DIK_M))
	{//F1キーを押した

		g_Player.pos = D3DXVECTOR3(4400.0f, 300.0f, -590.0f);
	}

	//モデルの右移動
	else if (GetKeyboardPress(DIK_D))
	{//右方向
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f)*SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f)*SPEED;
		g_rotDestPlayer.y = pCamera->rot.y + D3DX_PI *-0.0f;
	}
	
	//モデルの左移動
	else if (GetKeyboardPress(DIK_A))
	{//左方向
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f)*SPEED;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f)*SPEED;
		g_rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 1.0f;
	}
	
	//モデル加速
	 if (GetKeyboardPress(DIK_W))
	{//ジャンプ
		 if (g_Player.bIsJumping == false)
		 {
			 //サウンドの再生
			 PlaySound(SOUND_LABEL_SE_jump);
			g_Player.bIsJumping = true;
			g_Player.move.y = 12.5f;
			SetEffect(g_Player.pos,g_Player.rot, D3DXVECTOR3(20.0f, 20.0f, 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40);
		 }
	}
	 //モデル加速
	 if (GetKeyboardPress(DIK_RETURN))
	 {//ジャンプ
		 if (g_Player.bIsJumping == false)
		 {
			 //サウンドの再生
			 PlaySound(SOUND_LABEL_SE_jump);
			 g_Player.bIsJumping = true;
			 g_Player.move.y = 12.5f;
			 SetEffect(g_Player.pos, g_Player.rot, D3DXVECTOR3(20.0f, 20.0f, 0.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40);
		 }
	 }
	 //制作者権限
	 if (GetKeyboardTrigger(DIK_I))
	 {//隠しトロフィー
		 //サウンドの再生
		 PlaySound(SOUND_LABEL_SE_fanfare);
		 SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 2);
		 AddScore(50);
		 AddGetTrophy(1);
	 }
	float fDest = g_rotDestPlayer.y -g_Player.rot.y;

	if (fDest> D3DX_PI)
	{
		fDest -= D3DX_PI * 2;
	}
	else if (fDest < -D3DX_PI)
	{
		fDest += D3DX_PI * 2;
	}

	g_Player.rot.y += fDest*ANGLE_DAMPING_COEFFICIENT;

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//前回の位置を保存
	g_Player.posOld = g_Player.pos;

	//移動値
	g_Player.pos.x += g_Player.move.x / 2;
	g_Player.pos.y += g_Player.move.y / 2;
	g_Player.pos.z += g_Player.move.z / 2;
	g_Player.move.x = (-g_Player.move.x)*0.1f / 2;
	g_Player.move.y -= PLAYER_G / 2;
	g_Player.move.z = (-g_Player.move.z)*0.1f / 2;
	
	 if (g_Player.pos.y <pMeshfield->g_posMeshfield.y)
	{//メッシュの下に当たった
		g_Player.pos.y = pMeshfield->g_posMeshfield.y;
		g_Player.bIsJumping = false;
		DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
		AddGetTrophy(1);
		if (CntGet <1)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_fanfare);
			SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 4);
			CntGet++;
			AddGetScore(13);
		}
	}
	
	 //モデルとの当たり判定
	 bool blsLanding = CollisionModel
		(&g_Player.pos,			//pPos
		 &g_Player.posOld,		//pPosOld
		 &g_Player.move,		//pMove
		 &g_Player.size);		//psize
	 if (blsLanding == true)
	 {
		 SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x,g_Player.pos.y, g_Player.pos.z));
	 }
	 else
	 {
		 SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z));
	 }
	//モデルとの当たり判定
	  CollisionGoal
	 (&g_Player.pos,		//pPos
		 &g_Player.posOld,	//pPosOld
		 &g_Player.move,	//pMove
		 &g_Player.size);	//psize

	//鳥との当たり判定
	  CollisionEnemy
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	  //鳥との当たり判定
	  CollisionBird
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	//地下との当たり判定
	  CollisionTika
	  (&g_Player.pos,		//pPos
		  &g_Player.posOld,	//pPosOld
		  &g_Player.move,	//pMove
		  &g_Player.size);	//psize

	//ブロックの上でジャンプ
	 if (blsLanding == true)
	 {
		 g_Player.bIsJumping = false;
	 }
}

//============================================================
// プレイヤーの描画処理
//============================================================
void DrawPlayer(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用
	D3DMATERIAL9 matDef;//マテリアルの保存
	D3DXMATERIAL *pMat;//マテリアルの保管

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);
	//マトリックスの設定

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアル
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポイント取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		g_MeshPlayer->DrawSubset(nCntMat);
	}
	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}

void DeathPlayer(D3DXVECTOR3 pos)
{
	g_Player.pos = pos;
	int Death;

}