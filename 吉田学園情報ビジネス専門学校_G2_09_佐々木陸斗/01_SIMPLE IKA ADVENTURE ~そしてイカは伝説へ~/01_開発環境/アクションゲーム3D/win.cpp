//============================================================
//
// 3D����@CLEAR���[win.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"RESULT.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"win.h"
#include"Score.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureWin = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWin = NULL;	//���_�o�b�t�@�ւ̂ۂ����
int g_nWinScore;

//============================================================
//CLEAR��ʂ̏�����
//============================================================
void lnitWin(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	g_nWinScore = GetScore();
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�R�A������
	lnitScore();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ika08.png",
		&g_pTextureWin);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWin,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffWin->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̕`��
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffWin->Unlock();
	//�X�R�A�ʒu
	SetScore(g_nWinScore, D3DXVECTOR3(600.0f, 315.0f, 0.0f), (50.0f), (30.0f));
}

//============================================================
//CLEAR��ʂ̏I��
//============================================================
void UninitWin(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�X�R�A�I��
	UninitScore();

	//�e�N�X�`���̔j��
	if (g_pTextureWin != NULL)
	{
		g_pTextureWin->Release();
		g_pTextureWin = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWin != NULL)
	{
		g_pVtxBuffWin->Release();
		g_pVtxBuffWin = NULL;
	}
}

//============================================================
//CLEAR��ʂ̍X�V
//============================================================
void UpdateWin(void)
{
	//�X�R�A�̍X�V
	UpdateScore();

	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}

	//�V�t�g�L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_SPACE) == true && fade == FADE_NONE)
	{
		//���[�h�ݒ�
		SetFade(MODE_GAME);
	}

}

//============================================================
//CLEAR��ʂ̕`�揈��
//============================================================
void DrawWin(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWin, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureWin);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�R�A�̕`��
	DrawScore();

	
}
