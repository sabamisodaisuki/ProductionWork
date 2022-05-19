//============================================================
//
// 3D����@������[Miti.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "miti.h"
#include "MODEL.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>

//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//�����W��
#define MAX_Miti	(128)					//���̍ő吔
#define NUM_Miti	(2)						//����
//============================================================
//�O���[�o���ϐ�
//============================================================

typedef struct
{
	LPD3DXMESH			 MeshMiti;
	LPD3DXBUFFER		 pBuffMatMiti;
	DWORD				nNumMatMiti;
	D3DXVECTOR3			VtxMinMiti;		//�ŏ��l�@min[MAX_Miti_TYPE]
	D3DXVECTOR3			VtxMaxMiti;		//�ő�l�@max[MAX_Miti_TYPE]

}MitiLinfo;

//��Mitiinfo�\���̂̔z���錾����
D3DXMATRIX g_mtxWorldMiti;
MITI g_Miti[MAX_Miti];
MitiLinfo g_MitiInfo[NUM_Miti];

//============================================================
//�@���̏���������
//============================================================
void lnitMiti(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntMiti;

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/douro.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MitiInfo[0].pBuffMatMiti,
		NULL,
		&g_MitiInfo[0].nNumMatMiti,
		&g_MitiInfo[0].MeshMiti);//block001.x,ie.x

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/boat.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_MitiInfo[1].pBuffMatMiti,
		NULL,
		&g_MitiInfo[1].nNumMatMiti,
		&g_MitiInfo[1].MeshMiti);

	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	for (nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		g_Miti[nCntMiti].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Miti[nCntMiti].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Miti[nCntMiti].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����

		g_Miti[nCntMiti].bUse = false;
	}

	for (int CntMiti = 0; CntMiti < NUM_Miti; CntMiti++)
	{
		g_MitiInfo[CntMiti].VtxMinMiti = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);		//�ŏ��l
		g_MitiInfo[CntMiti].VtxMaxMiti = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l
	}

	//���^�C�v�����J��Ԃ�
	for (nCntMiti = 0; nCntMiti < NUM_Miti; nCntMiti++)
	{
		//���_���̎擾
		nNumVtx = g_MitiInfo[nCntMiti].MeshMiti->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_MitiInfo[nCntMiti].MeshMiti->GetFVF());

		//���_�o�b�t�@�����b�N
		g_MitiInfo[nCntMiti].MeshMiti->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ē��̍ő�l���擾
			if (Vtx.x >g_MitiInfo[nCntMiti].VtxMaxMiti.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_MitiInfo[nCntMiti].VtxMaxMiti.x = Vtx.x;
			}

			if (Vtx.y > g_MitiInfo[nCntMiti].VtxMaxMiti.y)
			{
				g_MitiInfo[nCntMiti].VtxMaxMiti.y = Vtx.y;
			}

			if (Vtx.z > g_MitiInfo[nCntMiti].VtxMaxMiti.z)
			{
				g_MitiInfo[nCntMiti].VtxMaxMiti.z = Vtx.z;
			}

			//���_���W���r���ē��̍ŏ��l���擾

			if (Vtx.x <g_MitiInfo[nCntMiti].VtxMinMiti.x)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.x = Vtx.x;
			}

			if (Vtx.y < g_MitiInfo[nCntMiti].VtxMinMiti.y)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.y = Vtx.y;
			}

			if (Vtx.z <g_MitiInfo[nCntMiti].VtxMinMiti.z)
			{
				g_MitiInfo[nCntMiti].VtxMinMiti.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_MitiInfo[nCntMiti].MeshMiti->UnlockVertexBuffer();
	}
	MitiSet();
}

//============================================================
//�@�I������
//============================================================
void UninitMiti(void)
{
	
	for (int nCntMiti = 0; nCntMiti < NUM_Miti; nCntMiti++)
	{ //�e�N�X�`���̔j��
	  //���b�V���̔j��
		if (g_MitiInfo[nCntMiti].pBuffMatMiti != NULL)
		{
			g_MitiInfo[nCntMiti].pBuffMatMiti->Release();
			g_MitiInfo[nCntMiti].pBuffMatMiti = NULL;
		}
	}
}

//============================================================
// ���̃A�b�v�f�[�g����
//============================================================
void UpdateMiti(void)
{

}

//============================================================
// ���̕`�揈��
//============================================================
void DrawMiti(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p
	D3DMATERIAL9 matDef;//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;//�}�e���A���̕ۊ�

					   //���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	for (int nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		if (g_Miti[nCntMiti].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMiti);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Miti[nCntMiti].rot.x, g_Miti[nCntMiti].rot.y, g_Miti[nCntMiti].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldMiti, &g_mtxWorldMiti, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Miti[nCntMiti].pos.x, g_Miti[nCntMiti].pos.y, g_Miti[nCntMiti].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldMiti, &g_mtxWorldMiti, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMiti);

			MitiLinfo* MitiInfo = &g_MitiInfo[g_Miti[nCntMiti].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)MitiInfo->pBuffMatMiti->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)MitiInfo->nNumMatMiti; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���p�[�c�̕`��
				MitiInfo->MeshMiti->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}

//============================================================
//���̐ݒ菈��
//============================================================
void SetMiti(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)	//type�ǉ�
{
	for (int nCntMiti = 0; nCntMiti < MAX_Miti; nCntMiti++)
	{
		if (g_Miti[nCntMiti].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Miti[nCntMiti].pos = pos;
			g_Miti[nCntMiti].rot = rot;
			g_Miti[nCntMiti].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Miti[nCntMiti].nType = nType;

			g_Miti[nCntMiti].size.x = (g_MitiInfo[nType].VtxMaxMiti.x - g_MitiInfo[nType].VtxMinMiti.x) / 2.0f;
			g_Miti[nCntMiti].size.y = (g_MitiInfo[nType].VtxMaxMiti.y - g_MitiInfo[nType].VtxMinMiti.y);
			g_Miti[nCntMiti].size.z = (g_MitiInfo[nType].VtxMaxMiti.z - g_MitiInfo[nType].VtxMinMiti.z) / 2.0f;

			break;		//(for���𔲂���)
		}
	}
}

//============================================================
//���̔z�u
//============================================================
void MitiSet(void)
{
	SetMiti(D3DXVECTOR3(2320.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
	SetMiti(D3DXVECTOR3(2320.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�

	SetMiti(D3DXVECTOR3(2450.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
	SetMiti(D3DXVECTOR3(2450.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�

	SetMiti(D3DXVECTOR3(2600.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
	SetMiti(D3DXVECTOR3(2740.0f, 200.0f, -470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
	SetMiti(D3DXVECTOR3(2600.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
	SetMiti(D3DXVECTOR3(2740.0f, 200.0f, -570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�

	SetMiti(D3DXVECTOR3(4500.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);//�{�[�g), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);//�ǉ�
}
