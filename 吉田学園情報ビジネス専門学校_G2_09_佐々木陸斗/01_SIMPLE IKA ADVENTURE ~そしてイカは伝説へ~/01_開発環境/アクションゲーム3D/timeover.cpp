//============================================================
//
// 3D����@�^�C���I�[�o�[���U���g����[timeover.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Timeover.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"Score.h"
#include"HighScore.h"
#include"trophy.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureTimeover = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimeover = NULL;//���_�o�b�t�@�ւ̂ۂ����
int g_nTimeoverScore;

//============================================================
//�^�C���I�[�o�[�̏���������
//============================================================
void lnitTimeover(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nTimeoverScore = GetScore();

	//�X�R�A
	lnitScore();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Timeover.jpg",
		&g_pTextureTimeover);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimeover,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTimeover->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTimeover->Unlock();

	//�X�R�A�ʒu
	SetScore(g_nTimeoverScore, D3DXVECTOR3(550.0f, 355.0f, 0.0f), (50.0f), (30.0f));
}

//============================================================
//�^�C���I�[�o�[�̏I��
//============================================================
void UninitTimeover(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�X�R�A
	UninitScore();

	//�e�N�X�`���̔j��
	if (g_pTextureTimeover != NULL)
	{
		g_pTextureTimeover->Release();
		g_pTextureTimeover = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimeover != NULL)
	{
		g_pVtxBuffTimeover->Release();
		g_pVtxBuffTimeover = NULL;
	}
}

//============================================================
//�^�C���I�[�o�[�̍X�V����
//============================================================
void UpdateTimeover(void)
{
	//�X�R�A
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
//�^�C���I�[�o�[�̕`�揈��
//============================================================
void DrawTimeover(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimeover, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimeover);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�R�A�Ăяo��
	DrawScore();

}
