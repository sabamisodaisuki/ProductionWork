//============================================================
//
// 3D����@�g���t�B�[�Q�b�g���@�̏���[get.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"get.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"getscore.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGet = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGet = NULL;	//���_�o�b�t�@�ւ̂ۂ����
int g_nGetgetScore;

//============================================================
//�Q�b�g�̏�����
//============================================================
void lnitGet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nGetgetScore = GetgetScore();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGMTITLE2);

	//�Q�b�g�X�R�A�̏�����
	lnitGetScore();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy.jpg",//TITOL.png"
		&g_pTextureGet);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGet,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGet->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffGet->Unlock();

	//�X�R�A�ʒu
	SetGetScore(g_nGetgetScore, D3DXVECTOR3(1050.0f, 90.0f, 0.0f), (40.0f), (30.0f));
}

//============================================================
//�Q�b�g�̏I������
//============================================================
void UninitGet(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�Q�b�g�X�R�A�̏I��
	UninitGetScore();

	//�e�N�X�`���̔j��
	if (g_pTextureGet != NULL)
	{
		g_pTextureGet->Release();
		g_pTextureGet = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGet != NULL)
	{
		g_pVtxBuffGet->Release();
		g_pVtxBuffGet = NULL;
	}
}

//============================================================
//�Q�b�g�̍X�V����
//============================================================
void UpdateGet(void)
{
	//�Q�b�g�X�R�A�̍X�V����
	UpdateGetScore();

	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	//����L�[(RETURN�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}
	//����L�[(K�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_K) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_GAME);
	}
}

//============================================================
//�Q�b�g�̕`�揈��
//============================================================
void DrawGet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGet);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�Q�b�g�X�R�A�Ăяo��
	DrawGetScore();
}

