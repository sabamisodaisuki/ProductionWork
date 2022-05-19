//============================================================
//
// 3D����@�S�[������[Goal.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "Goal.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include"fade.h"
#include"HighScore.h"
#include <stdio.h>

//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//�����W��
#define MAX_MODEL	(128)					//���f���̍ő吔
#define NUM_MODEL	(2)						//���f����
//============================================================
//�O���[�o���ϐ�
//============================================================

typedef struct
{
	LPD3DXMESH			 MeshGoal;
	LPD3DXBUFFER		 pBuffMatGoal;
	DWORD				nNumMatGoal;
	D3DXVECTOR3			VtxMinGoal;		//�ŏ��l�@min[MAX_MODEL_TYPE]
	D3DXVECTOR3			VtxMaxGoal;		//�ő�l�@max[MAX_MODEL_TYPE]

}GoalLinfo;

D3DXMATRIX g_mtxWorldGoal;
Goal g_Goal[MAX_MODEL];
GoalLinfo g_GoalInfo[NUM_MODEL];

//============================================================
//�S�[���̏���������
//============================================================
void lnitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntGoal;

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/kabe2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GoalInfo[0].pBuffMatGoal,
		NULL,
		&g_GoalInfo[0].nNumMatGoal,
		&g_GoalInfo[0].MeshGoal);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/GOAL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GoalInfo[1].pBuffMatGoal,
		NULL,
		&g_GoalInfo[1].nNumMatGoal,
		&g_GoalInfo[1].MeshGoal);

	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	for (nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		g_Goal[nCntGoal].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Goal[nCntGoal].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Goal[nCntGoal].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����

		g_Goal[nCntGoal].bUse = false;
	}

	for (int CntGoal = 0; CntGoal < NUM_MODEL; CntGoal++)
	{
		g_GoalInfo[nCntGoal].VtxMinGoal = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//�ŏ��l
		g_GoalInfo[nCntGoal].VtxMaxGoal = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l
	}

	//���^�C�v�����J��Ԃ�
	for (nCntGoal = 0; nCntGoal < NUM_MODEL; nCntGoal++)
	{
		//���_���̎擾
		nNumVtx = g_GoalInfo[nCntGoal].MeshGoal->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_GoalInfo[nCntGoal].MeshGoal->GetFVF());

		//���_�o�b�t�@�����b�N
		g_GoalInfo[nCntGoal].MeshGoal->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ő�l���擾
			if (Vtx.x >g_GoalInfo[nCntGoal].VtxMaxGoal.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_GoalInfo[nCntGoal].VtxMaxGoal.x = Vtx.x;
			}

			if (Vtx.y > g_GoalInfo[nCntGoal].VtxMaxGoal.y)
			{
				g_GoalInfo[nCntGoal].VtxMaxGoal.y = Vtx.y;
			}

			if (Vtx.z > g_GoalInfo[nCntGoal].VtxMaxGoal.z)
			{
				g_GoalInfo[nCntGoal].VtxMaxGoal.z = Vtx.z;
			}

			//���_���W���r���ă��f���̍ŏ��l���擾

			if (Vtx.x <g_GoalInfo[nCntGoal].VtxMinGoal.x)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.x = Vtx.x;
			}

			if (Vtx.y < g_GoalInfo[nCntGoal].VtxMinGoal.y)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.y = Vtx.y;
			}

			if (Vtx.z <g_GoalInfo[nCntGoal].VtxMinGoal.z)
			{
				g_GoalInfo[nCntGoal].VtxMinGoal.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_GoalInfo[nCntGoal].MeshGoal->UnlockVertexBuffer();
	}
	GoalSet();
}

//============================================================
//�@�I������
//============================================================
void UninitGoal(void)
{
	for (int nCntGoal = 0; nCntGoal < NUM_MODEL; nCntGoal++)
	{
		 //���b�V���̔j��
		if (g_GoalInfo[nCntGoal].pBuffMatGoal != NULL)
		{
			g_GoalInfo[nCntGoal].pBuffMatGoal->Release();
			g_GoalInfo[nCntGoal].pBuffMatGoal = NULL;
		}
	}
}

//============================================================
// �S�[���̃A�b�v�f�[�g����
//============================================================
void UpdateGoal(void)
{

}

//============================================================
// �S�[���̕`�揈��
//============================================================
void DrawGoal(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���̕ۊ�

	 //���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	for (int nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldGoal);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Goal[nCntGoal].rot.x, g_Goal[nCntGoal].rot.y, g_Goal[nCntGoal].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldGoal, &g_mtxWorldGoal, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Goal[nCntGoal].pos.x, g_Goal[nCntGoal].pos.y, g_Goal[nCntGoal].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldGoal, &g_mtxWorldGoal, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGoal);

			GoalLinfo* GoalInfo = &g_GoalInfo[g_Goal[nCntGoal].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)GoalInfo->pBuffMatGoal->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)GoalInfo->nNumMatGoal; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				GoalInfo->MeshGoal->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}
//============================================================
// �S�[���̓����蔻��
//============================================================
bool CollisionGoal(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)				//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	for (int nCntGoal = 0; nCntGoal<MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == true)//�g�p���Ă���ꍇ
		{

			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z >g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPos->y - pSize->y <g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y &&
				pPos->y + pSize->y >g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y &&

				pPosOld->x >= g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x &&
				pPos->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPos->y - pSize->y < g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y &&
				pPos->y + pSize->y > g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y &&

				pPosOld->x <= g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x &&
				pPos->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x - pSize->x;
				pMove->x = 0.0f;
			}


			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x &&
				pPos->x + pSize->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x &&

				pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPosOld->y <= g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y &&
				pPos->y > g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				pPos->y = g_Goal[nCntGoal].pos.y - g_Goal[nCntGoal].size.y - pSize->y;
				pMove->y = 0.0f;
			}

			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Goal[nCntGoal].pos.x + g_Goal[nCntGoal].size.x &&
				pPos->x + pSize->x > g_Goal[nCntGoal].pos.x - g_Goal[nCntGoal].size.x &&

				pPos->z - pSize->z < g_Goal[nCntGoal].pos.z + g_Goal[nCntGoal].size.z &&
				pPos->z + pSize->z > g_Goal[nCntGoal].pos.z - g_Goal[nCntGoal].size.z &&

				pPosOld->y >= g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y &&
				pPos->y < g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y&& fade == FADE_NONE)
				//�u���b�N�ɂ߂荞��
			{
				bIsLanding = true;
				SaveHigeScore();//�X�R�A�ۑ�
				pPos->y = g_Goal[nCntGoal].pos.y + g_Goal[nCntGoal].size.y + pSize->y;
				pMove->y = 0.0f;
				//���[�h�ݒ�(�Q�[����ʂɈڍs)
				SetFade(MODE_RESULT);
			}
		}
	}

	return bIsLanding;
}

//============================================================
//�S�[���̐ݒ菈��
//============================================================
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)	
{
	for (int nCntGoal = 0; nCntGoal < MAX_MODEL; nCntGoal++)
	{
		if (g_Goal[nCntGoal].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Goal[nCntGoal].pos = pos;
			g_Goal[nCntGoal].rot = rot;
			g_Goal[nCntGoal].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Goal[nCntGoal].nType = nType;

			g_Goal[nCntGoal].size.x = (g_GoalInfo[nType].VtxMaxGoal.x - g_GoalInfo[nType].VtxMinGoal.x) / 2.0f;
			g_Goal[nCntGoal].size.y = (g_GoalInfo[nType].VtxMaxGoal.y - g_GoalInfo[nType].VtxMinGoal.y);
			g_Goal[nCntGoal].size.z = (g_GoalInfo[nType].VtxMaxGoal.z - g_GoalInfo[nType].VtxMinGoal.z) / 2.0f;

			break;		//(for���𔲂���)
		}
	}
}

void GoalSet(void)
{
	SetGoal(D3DXVECTOR3(500.0f, 10.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�

	SetGoal(D3DXVECTOR3(4700.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);//��3
}

