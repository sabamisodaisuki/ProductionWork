//============================================================
//
// 3D����@�^�C�g������[title.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"title.h"
#include"game.h"
#include"sound.h"
#include"fade.h"

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;	//���_�o�b�t�@�ւ̂ۂ����


//============================================================
//�^�C�g���̏���������
//============================================================
void lnitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGMTITLE2);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE1.jpg",
		&g_pTextureTitle);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();
}

//============================================================
//�^�C�g���I������
//============================================================
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//============================================================
//�^�C�g���X�V����
//============================================================
void UpdateTitle(void)
{
	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE)
	{
		//���[�h�ݒ�
		SetFade(MODE_KIKEN);
	}
	//����L�[(ENTER�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_K) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_GAME);
	}

	//LSHIFT�L�[(LSHIFT�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_LSHIFT) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_STAFF);
	}

	//RSHIFT�L�[(LSHIFT�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_RSHIFT) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_STAFF);
	}
	//SPACE�L�[(SPACE�L�[�������ꂽ���ǂ���)
	if (GetKeyboardTrigger(DIK_SPACE) == true && fade == FADE_NONE)
	{
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ketei);

		//���[�h�ݒ�
		SetFade(MODE_GET);
	}
}

//============================================================
//�^�C�g���̕`�揈��
//============================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 , 2);
}

