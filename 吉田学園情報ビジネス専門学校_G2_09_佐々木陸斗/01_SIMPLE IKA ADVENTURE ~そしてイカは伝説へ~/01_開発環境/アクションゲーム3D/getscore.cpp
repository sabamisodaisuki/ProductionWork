//============================================================
//
// 3D����@�X�R�A�Q�b�g�̏���[getscore.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Score.h"

//============================================================
//�}�N����`
//============================================================
#define TEXTURE_U				(10)	//�e�N�X�`������

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureGetScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGetScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
D3DXVECTOR3 g_posGetScore;								//�X�R�A�̈ʒu
int g_nGetScore;										//�X�R�A�̒l

//============================================================
//�Q�b�g�X�R�A�̏�����
//============================================================
void lnitGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureGetScore);

	g_posGetScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
	g_nGetScore = 0; //�l������������

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Score,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGetScore,
		NULL);

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

							//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f*nCntScore, g_posGetScore.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f + 20.0f*nCntScore, g_posGetScore.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f*nCntScore, g_posGetScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetScore.x + 20.0f + 20.0f*nCntScore, g_posGetScore.y + 30.0f, 0.0f);

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
	g_pVtxBuffGetScore->Unlock();
}

//============================================================
//�Q�b�g�X�R�A�̏I������
//============================================================
void UninitGetScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGetScore != NULL)
	{
		g_pTextureGetScore->Release();
		g_pTextureGetScore = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGetScore != NULL)
	{
		g_pVtxBuffGetScore->Release();
		g_pVtxBuffGetScore = NULL;
	}

}

//============================================================
//�Q�b�g�X�R�A�̍X�V����
//============================================================
void UpdateGetScore(void)
{

}

//============================================================
//�Q�b�g�X�R�A�̕`�揈��
//============================================================
void DrawGetScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGetScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGetScore);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//============================================================
//�Q�b�g�X�R�A�̐ݒ菈��
//============================================================
void SetGetScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntScore;

	g_posGetScore = pos;
	g_nGetScore = nScore;

	VERTEX_2D*pVtx;
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nGetScore % 1000 / 100;
	aPosTexU[1] = g_nGetScore % 100 / 10;
	aPosTexU[2] = g_nGetScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posGetScore.x + fWidth*nCntScore, g_posGetScore.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posGetScore.x + fWidth + fWidth*nCntScore, g_posGetScore.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posGetScore.x + fWidth*nCntScore, g_posGetScore.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posGetScore.x + fWidth + fWidth*nCntScore, g_posGetScore.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntScore] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffGetScore->Unlock();
}
//============================================================
//�Q�b�g�X�R�A�̉��Z����
//============================================================
void AddGetScore(int nValue)
{
	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntScore;

	g_nGetScore += nValue;

	aPosTexU[0] = g_nGetScore % 1000 / 100;
	aPosTexU[1] = g_nGetScore % 100 / 10;
	aPosTexU[2] = g_nGetScore % 10 / 1;

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffGetScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffGetScore->Unlock();
}

int GetgetScore(void)
{
	return g_nGetScore;
}