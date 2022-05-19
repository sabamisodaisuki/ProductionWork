//============================================================
//
// 3D����@�^�C������[time.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"time.h"
#include"fade.h"
#include"HighScore.h"
//============================================================
//�}�N����`
//============================================================
#define TEXTURE_U				(10)	//�e�N�X�`������

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
D3DXVECTOR3 g_posTime;								//�X�R�A�̈ʒu
int g_nTime;										//�X�R�A�̒l
int g_nTimetime;

//============================================================
//�^�C���̏���������
//============================================================
void lnitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime);

	g_posTime = D3DXVECTOR3(620.0f, 10.0f, 0.0f);//�ʒu������������
	g_nTime = 0;								//�l������������
	g_nTimetime = 0;
	
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);


	VERTEX_2D*pVtx;		//���_���փ|�C���^

						//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{

		//���_���W�̐ݒ�

		pVtx[0].pos = D3DXVECTOR3(g_posTime.x + 30.0f*nCntTime, g_posTime.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 30.0f + 30.0f*nCntTime, g_posTime.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x + 30.0f*nCntTime, g_posTime.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 30.0f + 30.0f*nCntTime, g_posTime.y + 30.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_U, 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTime->Unlock();
	
	//�Q�[�����Ԑݒ�
	SetTime(300);
}

//============================================================
//�^�C���̏I������
//============================================================
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}

}

//============================================================
//�^�C���̍X�V����
//============================================================
void UpdateTime(void)
{// �t�F�[�h���̎擾
	FADE fade = GetFade();

	g_nTimetime++;
	if (g_nTimetime%60==0)
	{
		AddTime(-1);
	}
	if (g_nTime <= 0 && fade == FADE_NONE)
	{
		SaveHigeScore();

		SetFade(MODE_TIMEOVER);
		return;
	}

}

//============================================================
//�^�C���̕`�揈��
//============================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//============================================================
//�^�C���̐ݒ菈��
//============================================================
void SetTime(int nTime)
{
	int aPosTexU[MAX_TIME];	//�e���̐������i�[

	int nCntTime;

	g_nTime = nTime;

	aPosTexU[0] = g_nTime % 1000 / 100;
	aPosTexU[1] = g_nTime % 100 / 10;
	aPosTexU[2] = g_nTime % 10 / 1;


	VERTEX_2D*pVtx;		//���_���փ|�C���^

						//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTime->Unlock();

}
//============================================================
//�^�C���̉��Z����
//============================================================
void AddTime(int nValue)
{
	int aPosTexU[MAX_TIME];	//�e���̐������i�[

	int nCntTime;

	g_nTime += nValue;

	aPosTexU[0] = g_nTime % 1000 / 100;
	aPosTexU[1] = g_nTime % 100 / 10;
	aPosTexU[2] = g_nTime % 10 / 1;


	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTime] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTime->Unlock();

}