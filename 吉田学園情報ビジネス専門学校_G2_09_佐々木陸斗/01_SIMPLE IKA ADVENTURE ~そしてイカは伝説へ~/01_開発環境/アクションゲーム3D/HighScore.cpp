//============================================================
//
// 3D制作　ハイスコア処理[HighScore.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Score.h"
#include"HighScore.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//============================================================
//マクロ定義
//============================================================
#define TEXTURE_U				(10)	//テクスチャ等分
#define MAX_WORD	(128)
#define MAX_SELECT  (3)
#define MAX_QUIZ    (10)

//定義
typedef struct
{
	char aQuestion[MAX_WORD];		//問題文
	char aSelect[MAX_SELECT][64];	//選択肢
	int nAnswer;
}Quizlnfo;

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureHigeScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHigeScore = NULL;		//頂点バッファへのポインタ	
D3DXVECTOR3 g_posHigeScore;								//スコアの位置
int g_nHigeScore;										//スコアの値														//グローバル変数宣言
Quizlnfo g_aQuizinfo[MAX_QUIZ];							//クイズ情報構造体
int g_aAnswer[MAX_QUIZ];								//ユーザー解答番号


//============================================================
//ハイスコアの初期化処理
//============================================================
void lnitHigeScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHigeScore;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureHigeScore);

	g_nHigeScore = 0; //値を初期化する

	//ハイスコアを読み込む
	LoadHigeScore();

	g_posHigeScore = D3DXVECTOR3(1020.0f, 50.0f, 0.0f);//位置を初期化する
	
	 //頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Score,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHigeScore,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{

		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f*nCntHigeScore, g_posHigeScore.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f + 20.0f*nCntHigeScore, g_posHigeScore.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f*nCntHigeScore, g_posHigeScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f + 20.0f*nCntHigeScore, g_posHigeScore.y + 30.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの描画
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffHigeScore->Unlock();

	SetHigeScore(g_nHigeScore, D3DXVECTOR3(1020.0f, 50.0f, 0.0f), (20.0f), (10.0f));
}

//============================================================
//ハイスコアの終了処理
//============================================================
void UninitHigeScore(void)
{
	//テクスチャの破棄
	if (g_pTextureHigeScore != NULL)
	{
		g_pTextureHigeScore->Release();
		g_pTextureHigeScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffHigeScore != NULL)
	{
		g_pVtxBuffHigeScore->Release();
		g_pVtxBuffHigeScore = NULL;
	}

}
//============================================================
//ハイスコアの更新処理
//============================================================
void UpdateHigeScore(void)
{

}

//============================================================
//ハイスコアの描画処理
//============================================================
void DrawHigeScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHigeScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHigeScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureHigeScore);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHigeScore * 4, 2);
	}
}

//============================================================
//ハイスコアの設定処理
//============================================================
void SetHigeScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_Score];	//各桁の数字を格納
	int nCntHigeScore;

	g_posHigeScore = pos;
	g_nHigeScore = nScore;

	VERTEX_2D*pVtx;
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nHigeScore % 10000 / 1000;
	aPosTexU[1] = g_nHigeScore % 1000 / 100;
	aPosTexU[2] = g_nHigeScore % 100 / 10;
	aPosTexU[3] = g_nHigeScore % 10 / 1;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);


		//頂点座標の設定

		pVtx[0].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth*nCntHigeScore, g_posHigeScore.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth + fWidth*nCntHigeScore, g_posHigeScore.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth*nCntHigeScore, g_posHigeScore.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth + fWidth*nCntHigeScore, g_posHigeScore.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntHigeScore] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffHigeScore->Unlock();
}
//============================================================
//ハイスコアの加算処理
//============================================================
void AddHigeScore(int nValue)
{
	int aPosTexU[MAX_Score];	//各桁の数字を格納
	int nCntHigeScore;

	g_nHigeScore += nValue;

	aPosTexU[0] = g_nHigeScore % 10000 / 1000;
	aPosTexU[1] = g_nHigeScore % 1000 / 100;
	aPosTexU[2] = g_nHigeScore % 100 / 10;
	aPosTexU[3] = g_nHigeScore % 10 / 1;

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//ポインタを４つ分進める
	}

	//頂点バッファアンロック
	g_pVtxBuffHigeScore->Unlock();
}


int GetHigeScore(void)
{
	return g_nHigeScore;
}

//============================================================
//ハイスコアのロード処理
//============================================================
void LoadHigeScore(void)
{
	FILE*pFile;

	//ファイルを開く
	pFile = fopen("data/Score.txt", "r");

	//情報を外部ファイルから読み込む
	if (pFile != NULL)
	{
		//書き込み
		fscanf(pFile, "%d", &g_nHigeScore);
	
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("***ファイルが開けませんでした***\n\n");
	}
}

//============================================================
//ハイスコアのセーブ処理
//============================================================
void SaveHigeScore(void)
{
	FILE*pFile;
	int nScore;
	/*int nDate;*/
	nScore = GetScore();

	LoadHigeScore();//ハイスコア読み込み

	if (nScore > g_nHigeScore)
	{
		g_nHigeScore = nScore;
	}

	//ファイルを開く
	pFile = fopen("data/Score.txt", "w");

	//情報を外部ファイルから読み込む
	if (pFile != NULL)
	{
		//書き込み
		fprintf(pFile,"%d",g_nHigeScore);
		/*scanf("%d",&nDate);*/
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("***ファイルが開けませんでした***\n\n");
	}
}


	