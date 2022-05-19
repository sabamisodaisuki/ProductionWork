//============================================================
//
// 3D����@�g���t�B�[�l�����̏���[Gettrophy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Gettrophy.h"

//============================================================
//�}�N����`
//============================================================
#define TEXTURE_U				(10)	//�e�N�X�`������

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGettrophy = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGettrophy = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
D3DXVECTOR3 g_posGetTrophy;								//�X�R�A�̈ʒu
int g_nGetTrophy;										//�X�R�A�̒l

//============================================================
//�g���t�B�[�Q�b�g�̏�����
//============================================================
void lnitGetTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTrophy;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureGettrophy);

	g_posGetTrophy = D3DXVECTOR3(1020.0f, 70.0f, 0.0f);//�ʒu������������
	g_nGetTrophy= 0; //�l������������

					 //���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_GETTROPHY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGettrophy,
		NULL);

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f*nCntTrophy, g_posGetTrophy.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f + 20.0f*nCntTrophy, g_posGetTrophy.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f*nCntTrophy, g_posGetTrophy.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetTrophy.x + 20.0f + 20.0f*nCntTrophy, g_posGetTrophy.y + 30.0f, 0.0f);

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
	g_pVtxBuffGettrophy->Unlock();
}

//============================================================
//�g���t�B�[�Q�b�g�̏I������
//============================================================
void UninitGetTrophy(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGettrophy != NULL)
	{
		g_pTextureGettrophy->Release();
		g_pTextureGettrophy = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGettrophy != NULL)
	{
		g_pVtxBuffGettrophy->Release();
		g_pVtxBuffGettrophy = NULL;
	}

}
//============================================================
//�g���t�B�[�Q�b�g�̍X�V����
//============================================================
void UpdateGetTrophy(void)
{

}

//============================================================
//�g���t�B�[�Q�b�g�̕`�揈��
//============================================================
void DrawGetTrophy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTrophy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGettrophy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGettrophy);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTrophy * 4, 2);
	}
}

//============================================================
//�g���t�B�[�Q�b�g�̐ݒ菈��
//============================================================
void SetGetTrophy(int nTrophy, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_GETTROPHY];	//�e���̐������i�[
	int nCntTrophy;

	g_posGetTrophy = pos;
	g_nGetTrophy = nTrophy;

	VERTEX_2D*pVtx;
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nGetTrophy % 1000 / 100;
	aPosTexU[1] = g_nGetTrophy % 100 / 10;
	aPosTexU[2] = g_nGetTrophy % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth*nCntTrophy, g_posGetTrophy.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth + fWidth*nCntTrophy, g_posGetTrophy.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth*nCntTrophy, g_posGetTrophy.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetTrophy.x + fWidth + fWidth*nCntTrophy, g_posGetTrophy.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntTrophy] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffGettrophy->Unlock();
}
//============================================================
//�g���t�B�[�Q�b�g�̉��Z����
//============================================================
void AddGetTrophy(int nValue)
{
	int aPosTexU[MAX_GETTROPHY];	//�e���̐������i�[
	int nCntTrophy;

	g_nGetTrophy += nValue;

	aPosTexU[0] = g_nGetTrophy % 1000 / 100;
	aPosTexU[1] = g_nGetTrophy % 100 / 10;
	aPosTexU[2] = g_nGetTrophy % 10 / 1;

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGettrophy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTrophy = 0; nCntTrophy < MAX_GETTROPHY; nCntTrophy++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntTrophy] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffGettrophy->Unlock();
}

int GetgetTrophy(void)
{
	return g_nGetTrophy;
}