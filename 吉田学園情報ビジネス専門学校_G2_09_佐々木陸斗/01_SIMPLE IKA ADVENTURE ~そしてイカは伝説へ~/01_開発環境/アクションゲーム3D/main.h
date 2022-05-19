//============================================================
//
// 3D制作　メイン処理[main.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x800)
#include "dinput.h"
#include "xaudio2.h"

//============================================================
// ライブラリのリンク
//============================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//============================================================
// マクロ定義
//============================================================
#define SCREEN_WIDTH     (1280)//幅(←）
#define SCREEN_WIDTH_X	　(0)//(→)
#define SCREEN_HEIGHT	 (720)//高さ
#define SCREEN_HEIGHT_Y	  (0)
#define FVF_VERTEX_2D    (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//============================================================
// 画面（モードの種類
//============================================================
typedef enum
{
	MODE_TITLEB = 0,
	MODE_TITLE,	//タイトル画面
	MODE_SETUMEI,	//ゲーム説明
	MODE_STAFF,
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX,
	MODE_WIN,
	MODE_TIMEOVER,
	MODE_GET,
	MODE_KIKEN
}MODE;

//============================================================
// 頂点情報の構造体を宣言
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
	
}VERTEX_3D;

//頂点情報の構造体を宣言
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//============================================================
// プロトタイプ宣言
//============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT lnit(HINSTANCE hlnsance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif