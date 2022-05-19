//====================
//プレイヤーの処理
//AUTHOR:佐々木陸斗
//
//===================

#include "main.h"
#include "Arrow.h"
#include"input.h"
#include"time.h"
#include"bullet.h"
#include"fade.h"
#include"sound.h"
#include"Enemy.h"
#include"HighScore.h"


#define Arrow_Z			(4.0f)

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;				//テクスチャへのポインタ			
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;		//頂点バッファへのポインタ
int g_nCounterAnimArrow;								//アニメーションカウンター
int g_nPatternAnimArrow;								//アニメーションパターン
int nDirectionMove;
D3DXVECTOR3 g_posArrow;								//位置
D3DXVECTOR3 g_moveArrow;								//移動量
D3DXVECTOR3 g_scaleArrow;								//プレイヤーの大きさ
D3DXVECTOR3 g_posOldArrow;								//前回の位置
Arrow g_Arrow;										//プレイヤー情報


														//プレイヤーの初期化処理
D3DXVECTOR3 g_rotArrow;								//向き
float g_fLengthArrow;									//対角線の長さ
float g_fAngleArrow;									//対角線の角度


														//プレイヤーの取得
Arrow*GetArrow(void)
{
	return &g_Arrow;
}

int sum(int a, int b)
{
	//	return a + b;
	int c = a + b;
	return c;
}


void lnitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int C;
	C = sum(4, 5);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/yazirusi.png",					//daiba.png sura2.png
		&g_pTextureArrow);

	g_nCounterAnimArrow = 0;							//カウンター初期化
	g_nPatternAnimArrow = 0;							//パターンNoを初期化
	g_posArrow = D3DXVECTOR3(70.0f, 480.0f, 0.0f);		//位置を初期化
	g_moveArrow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動値を初期化
	g_scaleArrow = D3DXVECTOR3(100.0f, 100.0f, 0.0f);	//プレイヤーの初期化処理
	g_Arrow.bDisp = true;
	g_Arrow.nLife = 20;
	g_Arrow.nCounterState = 60;
	g_Arrow.state = ArrowSTATE_NORMAL;



	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

						//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);



	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの描画
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//プレイヤー座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.33f*g_Arrow.nPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.33f + (0.33f*g_Arrow.nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.33f*g_Arrow.nPatternAnim), 0.25f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (0.33f*g_Arrow.nPatternAnim), 0.25f);

	//頂点バッファアンロック
	g_pVtxBuffArrow->Unlock();

}
//ポリゴンの終了処理
void UninitArrow(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}

}

//プレイヤーの更新処理
void UpdateArrow(void)
{
	// フェード情報の取得
	FADE fade = GetFade();

	VERTEX_2D*pVtx;



	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーを押した[左]

		g_Arrow.nDirectionMove = 1;


		g_moveArrow.x -= 5.0f;//プレイヤーの位置に移動量を足す

	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//Wキーを押した[上］
		if (g_Arrow.bIsJumping == false)
		{
			g_Arrow.bIsJumping = true;

			g_moveArrow.y = -40.0f;//プレイヤーのジャンプ

		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーを押した[右]
		g_Arrow.nDirectionMove = 2;
		g_moveArrow.x += 5.0f;//プレイヤーの位置に移動量を足す
	}
	
	if (g_moveArrow.x >= 1.0f || g_moveArrow.x <= -1.0f)
	{
		//パターン更新
		g_Arrow.nCounterAnim++; //カウンター加算

		if ((g_Arrow.nCounterAnim % 5) == 0)
		{

			g_Arrow.nPatternAnim++; //カウンター加算

			if (g_Arrow.nPatternAnim >= 4)//総パターンを超えた
			{
				g_Arrow.nPatternAnim = 0;//カウントを0に戻す
			}

			//頂点バッファをロックし、頂点情報へポインタ取得
			g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*g_Arrow.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.33f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*g_Arrow.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*(g_Arrow.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.33f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*(g_Arrow.nDirectionMove + 1));
			//頂点バッファアンロック
			g_pVtxBuffArrow->Unlock();
		}
		else
		{//停止中
			if (g_Arrow.nCounterAnim)
			{

			}



		}

	}
	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_posArrow.x - Arrow_SIZE_X / 2, g_posArrow.y - Arrow_SIZE_Y, g_posArrow.z);
	pVtx[1].pos = D3DXVECTOR3(g_posArrow.x + Arrow_SIZE_X / 2, g_posArrow.y - Arrow_SIZE_Y, g_posArrow.z);
	pVtx[2].pos = D3DXVECTOR3(g_posArrow.x - Arrow_SIZE_X / 2, g_posArrow.y, g_posArrow.z);
	pVtx[3].pos = D3DXVECTOR3(g_posArrow.x + Arrow_SIZE_X / 2, g_posArrow.y, g_posArrow.z);


	//頂点バッファアンロック
	g_pVtxBuffArrow->Unlock();
}



//ポリゴンの描画処理
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureArrow);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

