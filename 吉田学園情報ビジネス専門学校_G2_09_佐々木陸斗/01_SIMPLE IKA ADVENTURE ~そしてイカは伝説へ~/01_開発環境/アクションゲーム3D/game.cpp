//============================================================
//
// 3D制作　ゲームの処理[game.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"title.h"
#include"game.h"
#include"sound.h"
#include"Score.h"
#include"Time.h"
#include"HighScore.h"
#include "light.h"
#include "meshfield.h"
#include "shadow.h"
#include "billborad.h"
#include "model.h"
#include "wall.h"
#include "effect.h"
#include "camera.h"
#include "fade.h"
#include"goal.h"
#include"miti.h"
#include"enemy.h"
#include"trophy.h"
#include"bird.h"
#include"tika.h"
#include"Gettrophy.h"
#include"UI.h"
//============================================================
//ゲーム画面初期化
//============================================================
void lnitGAME(void)
{
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGMGameBGM);

	//カメラの初期化
	lnitCamera();

	//ライトの初期化
	lnitLight();


	//ポリゴンの初期化
	//lnitPolygon();

	//メッシュの初期化
	lnitMeshfield();

	//影の初期化
	lnitShadow();

	//プレイヤーの初期化
	lnitPlayer();

	//モデル
	lnitModel();

	//ゴールの初期化
	lnitGoal();

	//鳥の初期化
	lnitEnemy();

	//鳥の初期化
	lnitBird();

	////道の初期化
	lnitMiti();

	//地下の初期化
	lnitTika();

	//ビルボード
	lnitBillborad();

	//壁初期化
	lnitWall();

	//エフェクト初期化
	lnitEffect();

	//タイムの初期化
	lnitTime();
	
	//スコアの初期化処理
	lnitScore();

	//ハイスコアの初期化
	lnitHigeScore();

	//トロフィー獲得の初期化
	lnitGetTrophy();

	//UIの初期化
	lnitUi();

	//トロフィーの初期化処理
	lnitTrophy();
}



//============================================================
//ゲームの終了処理
//============================================================
void UninitGAME(void)
{
	//サウンドの停止
	StopSound();

	//カメラ終了
	UninitCamera();

	//ポリゴンの終了
	//UninitPolygon();

	//ライトの終了
	UninitLight();

	//メッシュの終了
	UninitMeshfield();

	//影の終了
	UninitShadow();
	
	//プレイヤーの終了
	UninitPlayer();

	//モデルの終了
	UninitModel();

	//鳥の終了
	UninitEnemy();

	//ゴールの終了処理
	UninitGoal();

	//鳥の終了
	UninitBird();

	//道の終了
	UninitMiti();

	//地下の終了
	UninitTika();

	//ビルボードの初期化
	UninitBillborad();

	//エフェクトの初期化
	UninitEffect();

	//壁終了
	UninitWall();

	//スコアの終了処理
	UninitScore();

	//タイムの終了処理
	UninitTime();

	//ハイスコアの終了
	UninitHigeScore();

	//トロフィーの終了処理
	UninitTrophy();

	//UIの終了処理
	UninitUi();

	//トロフィーの獲得処理
	UninitGetTrophy();
}

//============================================================
//ゲームの描画処理
//============================================================
void DrawGAME(void)
{
	//カメラのセット
	SetCamera();

	//ポリゴンの描画
	//DrawPolygon();

	//メッシュの描画
	//DrawMeshfield();

	//プレイヤーの描画
	DrawPlayer();

	//モデルの描画
	DrawModel();

	//鳥の描画
	DrawEnemy();

	//鳥の描画
	DrawBird();

	//ゴールの描画処理
	DrawGoal();

	//道の描画
	DrawMiti();

	//影の描画
	DrawShadow();

	//地下の描画
	DrawTika();

	//エフェクトの描画
	DrawEffect();

	//ビルボードの描画処理
	DrawBillborad();

	//スコアの描画処理
	DrawScore();

	//タイムの描画処理
	DrawTime();

	//ハイスコアの描画処理
	DrawHigeScore();

	//トロフィーの描画処理
	DrawTrophy();

	//Uiの描画処理
	DrawUi();

	//トロフィー獲得の描画処理
	DrawGetTrophy();
}

//============================================================
//ゲーム画面の更新処理
//============================================================
void UpdateGAME(void)
{
	//フェードの更新処理
	UpdateFade();

	//カメラ更新
	UpdateCamera();

	//ライトの更新
	UpdateLight();

	//影の更新
	UpdateShadow();

	//プレイヤーの更新
	UpdatePlayer();

	//モデルの更新
	UpdateModel();

	//鳥の更新
	UpdateEnemy();

	//鳥の更新
	UpdateBird();

	//ゴールの更新
	UpdateGoal();

	//道の更新処理
	UpdateMiti();

	//地下の更新処理
	UpdateTika();

	//ビルボードの更新
	UpdateBillborad();

	//エフェクトの更新
	UpdateEffect();

	//壁の更新
	UpdateWall();

	//スコアの更新処理
	UpdateScore();

	//タイムの更新
	UpdateTime();

	//ハイスコアの更新処理
	UpdateHigeScore();

	//トロフィーの更新処理
	UpdateTrophy();

	//UIの更新処理
	UpdateUi();

	//トロフィー獲得の更新処理
	UpdateGetTrophy();
}