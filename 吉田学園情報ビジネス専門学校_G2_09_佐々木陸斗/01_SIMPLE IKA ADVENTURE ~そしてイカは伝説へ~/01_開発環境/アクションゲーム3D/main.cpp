//============================================================
//
// 3D����@���C������[main.cpp]
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
// �}�N����`
//============================================================
#define CLASS_NAME  "windowClass"				//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "ikaGame"					//�E�B���h�E�̖��O
#define ID_BUTTON_FINISH (101)					//�I���{�^����ID

//============================================================
// �O���[�o���ϐ�
//============================================================
LPDIRECT3D9		  g_pD3D = NULL;		//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;  //Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_MAX;					//���݂̃��[�h
//============================================================
// ���C���֐�
//============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),			//�������T�C�Y
		CS_CLASSDC,					//�E�B���h�E�̃X�^�C��
		WindowProc,					//�E�B���h�E�v���~�[�W��
		0,							//0�ɂ���
		0,							//0�ɂ���
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


	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������


	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);//��
	//�E�B���h�E�̐���
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

	//����������
	if (FAILED(lnit(hInstance, hWnd,FALSE)))//FALSE,true
	{//�����������s�����ꍇ
		return-1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;						//����������
	dwExecLastTime = timeGetTime();			//���ݎ������擾

	//�E�C���h�E�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎���Ĕ�����
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
		 dwCurrentTime = timeGetTime();	//���ݎ������擾

		if ((dwCurrentTime - dwExecLastTime)>=(1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;				//�����J�n�̎���
				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}
	//�I������
	Uninit();
	//����\��߂�
	timeEndPeriod(1);

	//�o�^����
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
//============================================================
// �E�B���h�E�v���V�[�W��
//============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;   //�Ԃ�l�i�[
	HWND hWndButtonFinish;
	static POINT aPos[6] = { { 100,100 },{300,150 },{400,50},{ 100,100 },{ 300,150 },{ 400,50 } };
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	static POINT aMove[6] = { { 2,3  },{ 3, 4 },{ 3, 1},{ 4,6 },{ 6, 8 },{ 6, 2 } };

	switch (uMsg)
	{
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO|MB_TOPMOST);
		if (nID == IDYES)
		{
			//�E�B���h�E�j��
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;   //0��Ԃ��Ȃ��ƏI
		}
		break;

	case WM_DESTROY://�E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E�j��(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
			break;

	    case WM_CREATE:  //�E�B���h�E���상�b�Z�[�W
	     //�I���{�^���̍쐬
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

			//�I���{�^�����쐬
			SetWindowText(hWndButtonFinish, "�I��");

			break;
			
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//�I��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E�j��(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
			break;
    }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//���菈�����J��Ԃ�
}
//============================================================
// ����������
//============================================================
HRESULT lnit(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�B�X�v���C�v���[���e�[�V�����p�����[�^�[�ݒ�
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

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���
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
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	InitSound(hWnd);

	lnitFade(g_mode);
	/*Setblock();*/

	//���[�h�ݒ�
	SetMode(MODE_TITLE);

return S_OK;
}
//============================================================
// �I������
//============================================================
void Uninit(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�T�E���h�̏I������
	UninitSound();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//============================================================
//�X�V����
//============================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();
	//�ؑ�
	if (GetKeyboardPress(DIK_F3))
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetKeyboardPress(DIK_F2))
	{//���ɖ߂�
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
	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//============================================================
// �`�揈��
//============================================================
void Draw(void)
{
	//��ʂ̃N���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

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
		
		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��̏I��
		g_pD3DDevice->EndScene();

	}
	//�o�b�N�o�b�t�@
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//============================================================
// ���[�h�̐ݒ�
//============================================================
void SetMode(MODE mode)
{
	//���݂̉�ʁi���[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();//�^�C�g�����
		break;

	case MODE_SETUMEI:
		UninitSetumei();
		break;

	case MODE_STAFF:
		UninitStaff();
		break;

	case MODE_GAME:
		UninitGAME();//�Q�[�����
		break;

	case MODE_RESULT:
		UninitRESULT();//���U���g���
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

	//�V������ʂ̏���������
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
	g_mode = mode;	//���݂̉�ʂ�؂�ւ���

}

//���[�h�̎擾
MODE GetMode(void)
{
	return g_mode;
}

//============================================================
// �f�o�C�X�̎擾
//============================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

