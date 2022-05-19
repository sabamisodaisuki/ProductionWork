//============================================================
//
// 3D����@���U���g����[result.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"result.h"
#include"game.h"
#include"sound.h"
#include"fade.h"
#include"Score.h"
#include"HighScore.h"
#include"trophy.h"
#include"Gettrophy.h"
#include"getscore.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureRESULT = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRESULT = NULL;	//���_�o�b�t�@�ւ̂ۂ����
int g_nRESULTScore;
int g_Counter;
int g_GetTrophy;

//============================================================
//���U���g�̏���������
//============================================================
void lnitRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nRESULTScore = GetScore();
	g_GetTrophy = GetgetTrophy();

	//�X�R�A
	lnitScore();

	//�g���t�B�[��
	lnitGetTrophy();

	lnitTrophy();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result.jpg",
		&g_pTextureRESULT);


	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRESULT,
		NULL);


	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffRESULT->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRESULT->Unlock();

	//�X�R�A�ʒu
 	SetScore(g_nRESULTScore, D3DXVECTOR3(550.0f, 355.0f, 0.0f), (50.0f), (30.0f));

	//�g���t�B�[��
	SetGetTrophy(g_GetTrophy, D3DXVECTOR3(950.0f,470.0f, 0.0f), (50.0f), (30.0f));
}

//============================================================
//���U���g�̏I������
//============================================================
void UninitRESULT(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�X�R�A
	UninitScore();

	//�g���t�B�[��
	UninitGetTrophy();

	UninitTrophy();

	//�e�N�X�`���̔j��
	if (g_pTextureRESULT != NULL)
	{
		g_pTextureRESULT->Release();
		g_pTextureRESULT = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRESULT != NULL)
	{
		g_pVtxBuffRESULT->Release();
		g_pVtxBuffRESULT = NULL;
	}
}

//============================================================
//���U���g�̍X�V����
//============================================================
void UpdateRESULT(void)
{
	g_Counter++;
	//�X�R�A
	UpdateScore();
	
	UpdateGetTrophy();

	UpdateTrophy();

	if (g_Counter == 10)
	{
		SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 0);
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_fanfare);
		AddScore(100);
		AddGetTrophy(1);
		AddGetScore(13);
	}
	
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
//���U���g��ʂ̕`�揈��
//============================================================
void DrawRESULT(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRESULT, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRESULT);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�R�A�Ăяo��
	DrawScore();

	//�l���g���t�B�[�\��
	DrawGetTrophy();

	//�o��g���t�B�[�\��
	DrawTrophy();
}

		

