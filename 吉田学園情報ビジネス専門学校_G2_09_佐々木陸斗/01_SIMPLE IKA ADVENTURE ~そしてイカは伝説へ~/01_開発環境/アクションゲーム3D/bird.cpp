//============================================================
//
// 3D����@�G�i���j�̏���[bird.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "bird.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include"MODEL.h"
#include <stdio.h>
#include"player.h"
#include"trophy.h"
#include"sound.h"
#include"Score.h"
#include"Gettrophy.h"
#include"getscore.h"
//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//�����W��
#define MAX_BIRD	(1235)					//���i�G�l�~�[�j�̍ő吔
#define NUM_BIRD	(2)						//���i�G�l�~�[�j��
#define Bird_G		(0.25f)
//============================================================
//�O���[�o���ϐ�
//============================================================
int g_nBirdCounter;//�G�̃J�E���g

typedef struct
{
	//���\���̂ɂ�����,MAX_BIRD �� MAX_BIRD_TYPE 2
	LPD3DXMESH			 MeshBird;
	LPD3DXBUFFER		 pBuffMatBird;
	DWORD				nNumMatBird;
	D3DXVECTOR3			VtxMinBird;		//�ŏ��l�@min[MAX_BIRD_TYPE]
	D3DXVECTOR3			VtxMaxBird;		//�ő�l�@max[MAX_BIRD_TYPE]

}BirdLinfo;

////��Birdinfo�\���̂̔z���錾����
D3DXMATRIX g_mtxWorldBird;
Bird g_Bird[MAX_BIRD];
BirdLinfo g_BirdInfo[NUM_BIRD];
int GetCounter;
//============================================================
//�@���i�G�l�~�[�j�̏���������
//============================================================
void lnitBird(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBird;
	g_nBirdCounter = 0;

	D3DXLoadMeshFromX("data/MODEL/bard1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BirdInfo[0].pBuffMatBird,
		NULL,
		&g_BirdInfo[0].nNumMatBird,
		&g_BirdInfo[0].MeshBird);

	D3DXLoadMeshFromX("data/MODEL/bard2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_BirdInfo[1].pBuffMatBird,
		NULL,
		&g_BirdInfo[1].nNumMatBird,
		&g_BirdInfo[1].MeshBird);

	int nNumVtx;	//���_��
	DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;	//���_�o�b�t�@�̃|�C���^

	for (nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		g_Bird[nCntBird].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Bird[nCntBird].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Bird[nCntBird].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bird[nCntBird].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����

		g_Bird[nCntBird].bUse = false;
	}

	for (int CntBird = 0; CntBird < NUM_BIRD; CntBird++)
	{
		g_BirdInfo[nCntBird].VtxMinBird = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//�ŏ��l
		g_BirdInfo[nCntBird].VtxMaxBird = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l
	}

	//���^�C�v�����J��Ԃ�
	for (nCntBird = 0; nCntBird < NUM_BIRD; nCntBird++)
	{
		//���_���̎擾
		nNumVtx = g_BirdInfo[nCntBird].MeshBird->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_BirdInfo[nCntBird].MeshBird->GetFVF());

		//���_�o�b�t�@�����b�N
		g_BirdInfo[nCntBird].MeshBird->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���Ē��i�G�l�~�[�j�̍ő�l���擾
			if (Vtx.x >g_BirdInfo[nCntBird].VtxMaxBird.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_BirdInfo[nCntBird].VtxMaxBird.x = Vtx.x;
			}

			if (Vtx.y > g_BirdInfo[nCntBird].VtxMaxBird.y)
			{
				g_BirdInfo[nCntBird].VtxMaxBird.y = Vtx.y;
			}

			if (Vtx.z > g_BirdInfo[nCntBird].VtxMaxBird.z)
			{
				g_BirdInfo[nCntBird].VtxMaxBird.z = Vtx.z;
			}

			//���_���W���r���Ē��i�G�l�~�[�j�̍ŏ��l���擾

			if (Vtx.x <g_BirdInfo[nCntBird].VtxMinBird.x)
			{
				g_BirdInfo[nCntBird].VtxMinBird.x = Vtx.x;
			}

			if (Vtx.y < g_BirdInfo[nCntBird].VtxMinBird.y)
			{
				g_BirdInfo[nCntBird].VtxMinBird.y = Vtx.y;
			}

			if (Vtx.z <g_BirdInfo[nCntBird].VtxMinBird.z)
			{
				g_BirdInfo[nCntBird].VtxMinBird.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_BirdInfo[nCntBird].MeshBird->UnlockVertexBuffer();
	}
}

//============================================================
//���i�G�l�~�[�j�̏I������
//============================================================
void UninitBird(void)
{
	for (int nCntBird = 0; nCntBird < NUM_BIRD; nCntBird++)
	{ 
		 //���b�V���̔j��
		if (g_BirdInfo[nCntBird].pBuffMatBird != NULL)
		{
			g_BirdInfo[nCntBird].pBuffMatBird->Release();
			g_BirdInfo[nCntBird].pBuffMatBird = NULL;
		}
	}
}

//============================================================
// ���i�G�l�~�[�j�̃A�b�v�f�[�g����
//============================================================
void UpdateBird(void)
{
	g_nBirdCounter++; //�G�̊Ԋu

	if (g_nBirdCounter % 320 == 0)
	{
		SetBird(D3DXVECTOR3(3320.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //��1
		SetBird(D3DXVECTOR3(1850.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //��1
		SetBird(D3DXVECTOR3(3600.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1);//�ǉ�
		SetBird(D3DXVECTOR3(2200.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1);//�ǉ�
	}
	else if (g_nBirdCounter % 220 == 0)
	{
		SetBird(D3DXVECTOR3(520.0f, 1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //��1
		SetBird(D3DXVECTOR3(150.0f, 1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 1); //��1
		SetBird(D3DXVECTOR3(1500.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 1);//�ǉ�
		SetBird(D3DXVECTOR3(1040.0f,1500.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 1);//�ǉ�
	}
	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		//�ړ��l
		g_Bird[nCntBird].move.y -= Bird_G / 2;
		g_Bird[nCntBird].pos.x += g_Bird[nCntBird].move.x / 2;
		g_Bird[nCntBird].pos.y += g_Bird[nCntBird].move.y / 2;
		g_Bird[nCntBird].pos.z += g_Bird[nCntBird].move.z / 2;
		if (g_Bird[nCntBird].pos.y <= 0.0f)

		{//��ʊO�ɒ����o����
			g_Bird[nCntBird].bUse = false;
		}
	}
}

//============================================================
// ���i�G�l�~�[�j�̕`�揈��
//============================================================
void DrawBird(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p
	D3DMATERIAL9 matDef;					//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;						//�}�e���A���̕ۊ�

	
	pDevice->GetMaterial(&matDef);			//���݂̃}�e���A��

	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBird);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Bird[nCntBird].rot.x, g_Bird[nCntBird].rot.y, g_Bird[nCntBird].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldBird, &g_mtxWorldBird, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bird[nCntBird].pos.x, g_Bird[nCntBird].pos.y, g_Bird[nCntBird].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBird, &g_mtxWorldBird, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBird);

			BirdLinfo* BirdInfo = &g_BirdInfo[g_Bird[nCntBird].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)BirdInfo->pBuffMatBird->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)BirdInfo->nNumMatBird; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���i�G�l�~�[�j�p�[�c�̕`��
				BirdInfo->MeshBird->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}
//============================================================
// ���i�G�l�~�[�j�̓����蔻��
//============================================================
bool CollisionBird(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)				//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (int nCntBird = 0; nCntBird<MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == true)//�g�p���Ă���ꍇ
		{
			Player*pPlayer;
			pPlayer = GetPlayer();

			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z >g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPos->y - pSize->y <g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y >g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->x >= g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x &&
				pPos->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x + pSize->x;
				pMove->x = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				AddScore(-1);
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddScore(6);
					AddGetTrophy(1);
					AddGetScore(13);
				}
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPos->y - pSize->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->x <= g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x &&
				pPos->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x - pSize->x;
				pMove->x = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddGetTrophy(1);
					AddGetScore(13);
				}

			}

			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPosOld->y <= g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y &&
				pPos->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				pPos->y = g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y - pSize->y;
				pMove->y = 0.0f;

			}
			//���ʓ����蔻��
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->y - pSize->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y &&
				pPos->y + pSize->y > g_Bird[nCntBird].pos.y - g_Bird[nCntBird].size.y &&

				pPosOld->z <= g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z - pSize->z &&
				pPos->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z - pSize->z)

				//�u���b�N�ɂ߂荞��
			{
				pPos->z = g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z - pSize->z;
				pMove->z = 0.0f;
				DeathPlayer(D3DXVECTOR3(30.0f, 420.0f, -590.0f));
				AddScore(-1);
				PlaySound(SOUND_LABEL_SE_HIT);
				if (GetCounter <1)
				{
					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_fanfare);
					SetTrophy(D3DXVECTOR3(SCREEN_WIDTH, 140.0f, 0.0f), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 3);
					GetCounter++;
					AddScore(6);
					AddGetTrophy(1);
					AddGetScore(13);
				}

			}

			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Bird[nCntBird].pos.x + g_Bird[nCntBird].size.x &&
				pPos->x + pSize->x > g_Bird[nCntBird].pos.x - g_Bird[nCntBird].size.x &&

				pPos->z - pSize->z < g_Bird[nCntBird].pos.z + g_Bird[nCntBird].size.z &&
				pPos->z + pSize->z > g_Bird[nCntBird].pos.z - g_Bird[nCntBird].size.z &&

				pPosOld->y >= g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y &&
				pPos->y < g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				bIsLanding = true;
				pPos->y = g_Bird[nCntBird].pos.y + g_Bird[nCntBird].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}
	}
	return bIsLanding;
}
//============================================================
// ���i�G�l�~�[�j�̐ݒ菈��
//============================================================
void SetBird(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)
{
	for (int nCntBird = 0; nCntBird < MAX_BIRD; nCntBird++)
	{
		if (g_Bird[nCntBird].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Bird[nCntBird].pos = pos;		//�ʒu
			g_Bird[nCntBird].rot = rot;		//����
			g_Bird[nCntBird].move = move;	//�ړ���
			g_Bird[nCntBird].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Bird[nCntBird].nType = nType;//�^�C�v����

			g_Bird[nCntBird].size.x = (g_BirdInfo[nType].VtxMaxBird.x - g_BirdInfo[nType].VtxMinBird.x) / 2.0f;
			g_Bird[nCntBird].size.y = (g_BirdInfo[nType].VtxMaxBird.y - g_BirdInfo[nType].VtxMinBird.y);
			g_Bird[nCntBird].size.z = (g_BirdInfo[nType].VtxMaxBird.z - g_BirdInfo[nType].VtxMinBird.z) / 2.0f;

			break;		//(for���𔲂���)
		}
	}
}
