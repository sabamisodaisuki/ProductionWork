//============================================================
//
// 3D����@�n�C�X�R�A����[HighScore.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Score.h"
#include"HighScore.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//============================================================
//�}�N����`
//============================================================
#define TEXTURE_U				(10)	//�e�N�X�`������
#define MAX_WORD	(128)
#define MAX_SELECT  (3)
#define MAX_QUIZ    (10)

//��`
typedef struct
{
	char aQuestion[MAX_WORD];		//��蕶
	char aSelect[MAX_SELECT][64];	//�I����
	int nAnswer;
}Quizlnfo;

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureHigeScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHigeScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^	
D3DXVECTOR3 g_posHigeScore;								//�X�R�A�̈ʒu
int g_nHigeScore;										//�X�R�A�̒l														//�O���[�o���ϐ��錾
Quizlnfo g_aQuizinfo[MAX_QUIZ];							//�N�C�Y���\����
int g_aAnswer[MAX_QUIZ];								//���[�U�[�𓚔ԍ�


//============================================================
//�n�C�X�R�A�̏���������
//============================================================
void lnitHigeScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHigeScore;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureHigeScore);

	g_nHigeScore = 0; //�l������������

	//�n�C�X�R�A��ǂݍ���
	LoadHigeScore();

	g_posHigeScore = D3DXVECTOR3(1020.0f, 50.0f, 0.0f);//�ʒu������������
	
	 //���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Score,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHigeScore,
		NULL);


	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{

		//���_���W�̐ݒ�

		pVtx[0].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f*nCntHigeScore, g_posHigeScore.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f + 20.0f*nCntHigeScore, g_posHigeScore.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f*nCntHigeScore, g_posHigeScore.y + 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHigeScore.x + 20.0f + 20.0f*nCntHigeScore, g_posHigeScore.y + 30.0f, 0.0f);

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
	g_pVtxBuffHigeScore->Unlock();

	SetHigeScore(g_nHigeScore, D3DXVECTOR3(1020.0f, 50.0f, 0.0f), (20.0f), (10.0f));
}

//============================================================
//�n�C�X�R�A�̏I������
//============================================================
void UninitHigeScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureHigeScore != NULL)
	{
		g_pTextureHigeScore->Release();
		g_pTextureHigeScore = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHigeScore != NULL)
	{
		g_pVtxBuffHigeScore->Release();
		g_pVtxBuffHigeScore = NULL;
	}

}
//============================================================
//�n�C�X�R�A�̍X�V����
//============================================================
void UpdateHigeScore(void)
{

}

//============================================================
//�n�C�X�R�A�̕`�揈��
//============================================================
void DrawHigeScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntHigeScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHigeScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureHigeScore);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHigeScore * 4, 2);
	}
}

//============================================================
//�n�C�X�R�A�̐ݒ菈��
//============================================================
void SetHigeScore(int nScore, D3DXVECTOR3 pos, float fWidth, float fHeight)
{

	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntHigeScore;

	g_posHigeScore = pos;
	g_nHigeScore = nScore;

	VERTEX_2D*pVtx;
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	aPosTexU[0] = g_nHigeScore % 10000 / 1000;
	aPosTexU[1] = g_nHigeScore % 1000 / 100;
	aPosTexU[2] = g_nHigeScore % 100 / 10;
	aPosTexU[3] = g_nHigeScore % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);


		//���_���W�̐ݒ�

		pVtx[0].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth*nCntHigeScore, g_posHigeScore.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth + fWidth*nCntHigeScore, g_posHigeScore.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth*nCntHigeScore, g_posHigeScore.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posHigeScore.x + fWidth + fWidth*nCntHigeScore, g_posHigeScore.y + fHeight, 0.0f);

		float f = (float)aPosTexU[nCntHigeScore] + 1.0f / (float)TEXTURE_U;

		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffHigeScore->Unlock();
}
//============================================================
//�n�C�X�R�A�̉��Z����
//============================================================
void AddHigeScore(int nValue)
{
	int aPosTexU[MAX_Score];	//�e���̐������i�[
	int nCntHigeScore;

	g_nHigeScore += nValue;

	aPosTexU[0] = g_nHigeScore % 10000 / 1000;
	aPosTexU[1] = g_nHigeScore % 1000 / 100;
	aPosTexU[2] = g_nHigeScore % 100 / 10;
	aPosTexU[3] = g_nHigeScore % 10 / 1;

	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffHigeScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHigeScore = 0; nCntHigeScore < MAX_Score; nCntHigeScore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U), 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)aPosTexU[nCntHigeScore] * (1.0f / TEXTURE_U) + (1.0f / TEXTURE_U), 1.0f);

		pVtx += 4;//�|�C���^���S���i�߂�
	}

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffHigeScore->Unlock();
}


int GetHigeScore(void)
{
	return g_nHigeScore;
}

//============================================================
//�n�C�X�R�A�̃��[�h����
//============================================================
void LoadHigeScore(void)
{
	FILE*pFile;

	//�t�@�C�����J��
	pFile = fopen("data/Score.txt", "r");

	//�����O���t�@�C������ǂݍ���
	if (pFile != NULL)
	{
		//��������
		fscanf(pFile, "%d", &g_nHigeScore);
	
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n\n");
	}
}

//============================================================
//�n�C�X�R�A�̃Z�[�u����
//============================================================
void SaveHigeScore(void)
{
	FILE*pFile;
	int nScore;
	/*int nDate;*/
	nScore = GetScore();

	LoadHigeScore();//�n�C�X�R�A�ǂݍ���

	if (nScore > g_nHigeScore)
	{
		g_nHigeScore = nScore;
	}

	//�t�@�C�����J��
	pFile = fopen("data/Score.txt", "w");

	//�����O���t�@�C������ǂݍ���
	if (pFile != NULL)
	{
		//��������
		fprintf(pFile,"%d",g_nHigeScore);
		/*scanf("%d",&nDate);*/
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n\n");
	}
}


	