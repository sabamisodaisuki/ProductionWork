//============================================================
//
// 3D����	�X�R�A[Score.cpp]
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
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
D3DXVECTOR3 g_posScore;								//�X�R�A�̈ʒu
int g_nScore;										//�X�R�A�̒l

//============================================================
//�X�R�A�̏���������
//============================================================
void lnitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",					
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(1020.0f,10.0f,0.0f);//�ʒu������������
	g_nScore = 0; //�l������������

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Score,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{	
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + 20.0f*nCntScore, g_posScore.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 20.0f + 20.0f*nCntScore, g_posScore.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + 20.0f*nCntScore, g_posScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 20.0f + 20.0f*nCntScore, g_posScore.y + 30.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f/ TEXTURE_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f/ TEXTURE_U, 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffScore->Unlock();
}

//============================================================
//�X�R�A�̏I������
//============================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}
//============================================================
//�X�R�A�̍X�V����
//============================================================
void UpdateScore(void)
{
	
}

//============================================================
//�X�R�A�̕`�揈��
//============================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//============================================================
//�X�R�A�̐ݒ菈��
//============================================================
void SetScore(int nScore , D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntScore;
	g_posScore = pos;
	g_nScore = nScore ;

	VERTEX_2D*pVtx;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nScore % 10000 / 1000;
	aPosTexU[1] = g_nScore % 1000 / 100;
	aPosTexU[2] = g_nScore % 100 / 10;
	aPosTexU[3] = g_nScore % 10 / 1;
	
	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_Score; nCntScore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + fWidth*nCntScore, g_posScore.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + fWidth + fWidth*nCntScore, g_posScore.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + fWidth*nCntScore, g_posScore.y +fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + fWidth + fWidth*nCntScore, g_posScore.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntScore] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffScore->Unlock();
}
//============================================================
//�X�R�A�̉��Z����
//============================================================
void AddScore(int nValue)
{
	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntScore;

	g_nScore += nValue;

	aPosTexU[0] = g_nScore % 10000 / 1000;
	aPosTexU[1] = g_nScore % 1000 / 100;
	aPosTexU[2] = g_nScore % 100 / 10;
	aPosTexU[3] = g_nScore % 10 / 1;

	VERTEX_2D*pVtx;;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	
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
	g_pVtxBuffScore->Unlock();
}
int GetScore(void)
{
	return g_nScore;
}