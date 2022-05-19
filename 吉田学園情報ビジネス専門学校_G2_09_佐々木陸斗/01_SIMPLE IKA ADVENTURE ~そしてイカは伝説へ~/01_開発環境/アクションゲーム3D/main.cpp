//============================================================
//
// 3D制作　メイン処理[main.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "Score.h"
#include "game.h"
#include "fade.h"
#include "title.h"
#include "result.h"
#include "setumei.h"
#include "sound.h"
#include "win.h"
#include "effect.h"
#include "camera.h"
#include "light.h"
#include "polygon.h"
#include "MODEL.h"
#include "shadow.h"
#include "wall.h"
#include "billborad.h"
#include "meshfield.h"
#include"staff.h"
#include"timeover.h"
#include"get.h"
#include"kiken.h"
//============================================================
// マクロ定義
//============================================================
#define CLASS_NAME  "windowClass"				//ウィンドウクラスの名前
#define WINDOW_NAME "ikaGame"					//ウィンドウの名前
#define ID_BUTTON_FINISH (101)					//終了ボタンのID

//============================================================
// グローバル変数
//============================================================
LPDIRECT3D9		  g_pD3D = NULL;		//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;  //Direct3Dデバイスへのポインタ
MODE g_mode = MODE_MAX;					//現在のモード
//============================================================
// メイン関数
//============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			//メモリサイズ
		CS_CLASSDC,					//ウィンドウのスタイル
		WindowProc,					//ウィンドウプロミージャ
		0,							//0にする
		0,							//0にする
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;


	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;		//最後に処理した時間


	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);//★
	//ウィンドウの制作
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//初期化処理
	if (FAILED(lnit(hInstance, hWnd,FALSE)))//FALSE,true
	{//初期化が失敗した場合
		return-1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;						//初期化する
	dwExecLastTime = timeGetTime();			//現在時刻を取得

	//ウインドウ表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取って抜ける
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
		 dwCurrentTime = timeGetTime();	//現在時刻を取得

		if ((dwCurrentTime - dwExecLastTime)>=(1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;				//処理開始の時間
				//更新処理
				Update();
				//描画処理
				Draw();
			}
		}
	}
	//終了処理
	Uninit();
	//分解能を戻す
	timeEndPeriod(1);

	//登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//============================================================
// ウィンドウプロシージャ
//============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;   //返り値格納
	HWND hWndButtonFinish;
	static POINT aPos[6] = { { 100,100 },{300,150 },{400,50},{ 100,100 },{ 300,150 },{ 400,50 } };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	static POINT aMove[6] = { { 2,3  },{ 3, 4 },{ 3, 1},{ 4,6 },{ 6, 8 },{ 6, 2 } };

	switch (uMsg)
	{
	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO|MB_TOPMOST);
		if (nID == IDYES)
		{
			//ウィンドウ破棄
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;   //0を返さないと終
		}
		break;

	case WM_DESTROY://ウィンドウ破棄のメッセージ
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウ破棄(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
			break;

	    case WM_CREATE:  //ウィンドウ制作メッセージ
	     //終了ボタンの作成
		hWndButtonFinish = CreateWindowEx
		(0,
			"BUTTON",
			"",
			(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
			1000, 600, 200, 40,
			hWnd,
			(HMENU)ID_BUTTON_FINISH,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);

			//終了ボタンを作成
			SetWindowText(hWndButtonFinish, "終了");

			break;
			
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//終了
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウ破棄(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
			break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定処理を繰り返す
}
//============================================================
// 初期化処理
//============================================================
HRESULT lnit(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//ディスプレイプレゼンテーションパラメーター設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	InitSound(hWnd);

	lnitFade(g_mode);
	/*Setblock();*/

	//モード設定
	SetMode(MODE_TITLE);

return S_OK;
}
//============================================================
// 終了処理
//============================================================
void Uninit(void)
{
	//キーボードの終了処理
	UninitKeyboard();

	//サウンドの終了処理
	UninitSound();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//============================================================
//更新処理
//============================================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();
	//切替
	if (GetKeyboardPress(DIK_F3))
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetKeyboardPress(DIK_F2))
	{//元に戻す
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}


	
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_SETUMEI:
		UpdateSetumei();
		break;

	case MODE_STAFF:
		UpdateStaff();
		break;

	case MODE_GAME:
	UpdateGAME();
	break;

	case MODE_RESULT:
		UpdateRESULT();
		break;
	case MODE_WIN:
		UpdateWin();
		break;

	case MODE_TIMEOVER:
		UpdateTimeover();
		break;

	case MODE_GET:
		UpdateGet();
		break;

	case MODE_KIKEN:
		UpdateKiken();
		break;
	}
	//フェードの更新処理
	UpdateFade();
}

//============================================================
// 描画処理
//============================================================
void Draw(void)
{
	//画面のクリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_SETUMEI:
			DrawSetumei();
			break;

		case MODE_STAFF:
			DrawStaff();
			break;

		case MODE_GAME:
			DrawGAME();
			break;

		case MODE_RESULT:
			DrawRESULT();
			break;

		case MODE_WIN:
			DrawWin();
			break;

		case MODE_TIMEOVER:
			DrawTimeover();
			break;

		case MODE_GET:
			DrawGet();
			break;

		case MODE_KIKEN:
			DrawKiken();
			break;
		}
		
		//フェードの描画処理
		DrawFade();

		//描画の終了
		g_pD3DDevice->EndScene();

	}
	//バックバッファ
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//============================================================
// モードの設定
//============================================================
void SetMode(MODE mode)
{
	//現在の画面（モードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();//タイトル画面
		break;

	case MODE_SETUMEI:
		UninitSetumei();
		break;

	case MODE_STAFF:
		UninitStaff();
		break;

	case MODE_GAME:
		UninitGAME();//ゲーム画面
		break;

	case MODE_RESULT:
		UninitRESULT();//リザルト画面
		break;

	case MODE_WIN:
		UninitWin();
		break;

	case MODE_TIMEOVER:
		UninitTimeover();
		break;

	case MODE_GET:
		UninitGet();
		break;

	case MODE_KIKEN:
		UninitKiken();
		break;
	}

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		lnitTitle();
		break;

	case MODE_SETUMEI:
		lnitSetumei();
		break;

	case MODE_STAFF:
		lnitStaff();
		break;

	case MODE_GAME:
		lnitGAME();
		break;

	case MODE_RESULT:
		lnitRESULT();
		break;

	case MODE_WIN:
		lnitWin();
		break;

	case MODE_TIMEOVER:
		lnitTimeover();
		break;

	case MODE_GET:
		lnitGet();
		break;

	case MODE_KIKEN:
		lnitKiken();
		break;
	}
	g_mode = mode;	//現在の画面を切り替える

}

//モードの取得
MODE GetMode(void)
{
	return g_mode;
}

//============================================================
// デバイスの取得
//============================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

