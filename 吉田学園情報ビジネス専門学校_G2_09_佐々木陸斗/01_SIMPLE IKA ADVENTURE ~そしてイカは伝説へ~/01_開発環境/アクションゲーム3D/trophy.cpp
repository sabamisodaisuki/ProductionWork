//============================================================
//
// 3D����@�g���t�B�[[trophy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"trophy.h"
#include"Score.h"
#include"sound.h"
#include"result.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_apTextureTROPHY[NUM_TROPHY] = { NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTROPHY = NULL;				//���_�o�b�t�@�|�C���^
TROPHY g_aTROPHY[MAX_TROPHY];									//�G�̏��
int g_nTROPHYCouter;											//�G�̃J�E���g

//���̎擾
TROPHY*GetTROPHY(void)
{
	return &g_aTROPHY[0];
}

//============================================================
//�g���t�B�[�̏���������
//============================================================
void lnitTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTROPHY;

	//�J�E���^�[�̏�����
	nCntTROPHY = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy11.png",
		&g_apTextureTROPHY[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy1.png",
		&g_apTextureTROPHY[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy2.png",
		&g_apTextureTROPHY[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy3.png",
		&g_apTextureTROPHY[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy4.png",
		&g_apTextureTROPHY[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy6.png",
		&g_apTextureTROPHY[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy.png",
		&g_apTextureTROPHY[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/trophy5.png",
		&g_apTextureTROPHY[7]);

	//���̏�����
	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		g_aTROPHY[nCntTROPHY].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTROPHY[nCntTROPHY].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTROPHY[nCntTROPHY].nType = 0;
		g_aTROPHY[nCntTROPHY].bUse = false;
	}

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TROPHY * NUM_TROPHY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTROPHY,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTROPHY->Unlock();
	lnitGetScore();
}

//============================================================
//�g���t�B�[�̏�������
//============================================================
void UninitTrophy(void)
{
	int nCntTROPHY;
	UninitGetScore();

	for (nCntTROPHY = 0; nCntTROPHY < NUM_TROPHY; nCntTROPHY++)
	{ //�e�N�X�`���̔j��
		if (g_apTextureTROPHY[nCntTROPHY] != NULL)
		{
			g_apTextureTROPHY[nCntTROPHY]->Release();
			g_apTextureTROPHY[nCntTROPHY] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTROPHY != NULL)
	{
		g_pVtxBuffTROPHY->Release();
		g_pVtxBuffTROPHY = NULL;
	}

}
//============================================================
//�g���t�B�[�̍X�V����
//============================================================
void UpdateTrophy(void)
{
	UpdateGetScore();
	int nCntTROPHY;
	VERTEX_2D*pVtx;
	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	g_nTROPHYCouter++;			//�G�̊Ԋu

	if (g_nTROPHYCouter == 60)
	{
		SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 60.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 6);
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_fanfare);
		AddScore(100);
		AddGetTrophy(1);
		AddGetScore(13);
	}

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == true)
		{//�����o�������

		 //���̈ʒu�̍X�V

			g_aTROPHY[nCntTROPHY].pos += g_aTROPHY[nCntTROPHY].move;

			//���_���W�̍X�V(���̑傫���j
			pVtx[0].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y - TROPHY_SIZE / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y - TROPHY_SIZE / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y + TROPHY_SIZE / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + TROPHY_SIZE / 2, g_aTROPHY[nCntTROPHY].pos.y + TROPHY_SIZE / 2, 0.0f);

			if (g_aTROPHY[nCntTROPHY].pos.x <= 6)

			{//��ʊO�ɒ����o����
				g_aTROPHY[nCntTROPHY].bUse = false;
			}
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTROPHY->Unlock();
}

//============================================================
//�g���t�B�[�`�揈��
//============================================================
void DrawTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTROPHY;
	DrawGetScore();
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTROPHY, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == true)
		{//�G���g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTROPHY[g_aTROPHY[nCntTROPHY].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTROPHY * 4, 2);
		}
	}
}

//============================================================
//�g���t�B�[�̐ݒ菈��
//============================================================
void SetTrophy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntTROPHY;

	VERTEX_2D*pVtx;

	//���_�o�b�t�@���b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTROPHY = 0; nCntTROPHY < MAX_TROPHY; nCntTROPHY++)
	{
		if (g_aTROPHY[nCntTROPHY].bUse == false)
		{//�G���g�p����ĂȂ��ꍇ

		 //�G�̏��̐ݒ�
			g_aTROPHY[nCntTROPHY].pos = pos;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - 6.0f, g_aTROPHY[nCntTROPHY].pos.y - 6.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + 6.0f, g_aTROPHY[nCntTROPHY].pos.y - 6.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x - 6.0f, g_aTROPHY[nCntTROPHY].pos.y + 6.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTROPHY[nCntTROPHY].pos.x + 6.0f, g_aTROPHY[nCntTROPHY].pos.y + 6.0f, 0.0f);


			//���_�J���[�̕`��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aTROPHY[nCntTROPHY].move = move;
			g_aTROPHY[nCntTROPHY].nLife = 10;
			g_aTROPHY[nCntTROPHY].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_aTROPHY[nCntTROPHY].nType = nType;
			
			break;
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtxBuffTROPHY->Unlock();
}
//�g���t�B�[�̏���
void HitTrophy(int nCntTROPHY, int nDamage)
{
	g_aTROPHY[nCntTROPHY].nLife -= nDamage;

	if (g_aTROPHY[nCntTROPHY].nLife <= 0)
	{

		g_aTROPHY[nCntTROPHY].bUse = false;
	}
	else
	{
		g_aTROPHY[nCntTROPHY].state = TROPHYSTA_DAMAGE;
		g_aTROPHY[nCntTROPHY].nCounterState = 15;

		VERTEX_2D*pVtx;

		//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
		g_pVtxBuffTROPHY->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntTROPHY;//�|�C���^���S���i�߂�

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//���_�o�b�t�@�A�����b�N
		g_pVtxBuffTROPHY->Unlock();
	}
}
