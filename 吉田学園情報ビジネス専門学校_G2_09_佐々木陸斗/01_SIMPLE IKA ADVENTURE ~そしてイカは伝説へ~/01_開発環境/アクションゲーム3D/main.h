//============================================================
//
// 3D����@���C������[main.h]
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
// ���C�u�����̃����N
//============================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//============================================================
// �}�N����`
//============================================================
#define SCREEN_WIDTH     (1280)//��(���j
#define SCREEN_WIDTH_X	�@(0)//(��)
#define SCREEN_HEIGHT	 (720)//����
#define SCREEN_HEIGHT_Y	  (0)
#define FVF_VERTEX_2D    (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//============================================================
// ��ʁi���[�h�̎��
//============================================================
typedef enum
{
	MODE_TITLEB = 0,
	MODE_TITLE,	//�^�C�g�����
	MODE_SETUMEI,	//�Q�[������
	MODE_STAFF,
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX,
	MODE_WIN,
	MODE_TIMEOVER,
	MODE_GET,
	MODE_KIKEN
}MODE;

//============================================================
// ���_���̍\���̂�錾
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
	
}VERTEX_3D;

//���_���̍\���̂�錾
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//============================================================
// �v���g�^�C�v�錾
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