//============================================================
//
// 3D����@���f������[model.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>
//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//�����W��
#define MAX_MODEL	(128)					//���f���̍ő吔
#define NUM_MODEL	(23)					//���f����
//============================================================
//�O���[�o���ϐ�
//============================================================

//��modelinfo�\����
typedef struct
{
	LPD3DXMESH			 MeshModel;
	LPD3DXBUFFER		 pBuffMatModel;
	DWORD				nNumMatModel;
	D3DXVECTOR3			VtxMinModel;		//�ŏ��l�@min[MAX_MODEL_TYPE]
	D3DXVECTOR3			VtxMaxModel;		//�ő�l�@max[MAX_MODEL_TYPE]

}ModelLinfo;

//��modelinfo�\���̂̔z���錾����
D3DXMATRIX g_mtxWorldModel;
Model g_Model[MAX_MODEL];
ModelLinfo g_ModelInfo[NUM_MODEL];

//============================================================
//�@���f���̏���������
//============================================================
void lnitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntModel;

	memset(&g_ModelInfo, 0, sizeof(g_ModelInfo));
	memset(&g_Model, 0, sizeof(g_Model));
	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/kabe4.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[0].pBuffMatModel,
		NULL,
		&g_ModelInfo[0].nNumMatModel,
		&g_ModelInfo[0].MeshModel);//block001.x,ie.x

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/kabe3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[1].pBuffMatModel,
		NULL,
		&g_ModelInfo[1].nNumMatModel,
		&g_ModelInfo[1].MeshModel);

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/ie.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[2].pBuffMatModel,
		NULL,
		&g_ModelInfo[2].nNumMatModel,
		&g_ModelInfo[2].MeshModel);
								
	D3DXLoadMeshFromX("data/MODEL/yuka.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[3].pBuffMatModel,
		NULL,
		&g_ModelInfo[3].nNumMatModel,
		&g_ModelInfo[3].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/yuka2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[4].pBuffMatModel,
		NULL,
		&g_ModelInfo[4].nNumMatModel,
		&g_ModelInfo[4].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/yuka3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[5].pBuffMatModel,
		NULL,
		&g_ModelInfo[5].nNumMatModel,
		&g_ModelInfo[5].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kago2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[6].pBuffMatModel,
		NULL,
		&g_ModelInfo[6].nNumMatModel,
		&g_ModelInfo[6].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[7].pBuffMatModel,
		NULL,
		&g_ModelInfo[7].nNumMatModel,
		&g_ModelInfo[7].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/Object.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[8].pBuffMatModel,
		NULL,
		&g_ModelInfo[8].nNumMatModel,
		&g_ModelInfo[8].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue4.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[9].pBuffMatModel,
		NULL,
		&g_ModelInfo[9].nNumMatModel,
		&g_ModelInfo[9].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/ikakago.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[10].pBuffMatModel,
		NULL,
		&g_ModelInfo[10].nNumMatModel,
		&g_ModelInfo[10].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tukue5.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[11].pBuffMatModel,
		NULL,
		&g_ModelInfo[11].nNumMatModel,
		&g_ModelInfo[11].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/saku.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[12].pBuffMatModel,
		NULL,
		&g_ModelInfo[12].nNumMatModel,
		&g_ModelInfo[12].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/hako.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[13].pBuffMatModel,
		NULL,
		&g_ModelInfo[13].nNumMatModel,
		&g_ModelInfo[13].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/hako1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[14].pBuffMatModel,
		NULL,
		&g_ModelInfo[14].nNumMatModel,
		&g_ModelInfo[14].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[15].pBuffMatModel,
		NULL,
		&g_ModelInfo[15].nNumMatModel,
		&g_ModelInfo[15].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kanban.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[16].pBuffMatModel,
		NULL,
		&g_ModelInfo[16].nNumMatModel,
		&g_ModelInfo[16].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[17].pBuffMatModel,
		NULL,
		&g_ModelInfo[17].nNumMatModel,
		&g_ModelInfo[17].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[18].pBuffMatModel,
		NULL,
		&g_ModelInfo[18].nNumMatModel,
		&g_ModelInfo[18].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/paipu3.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[19].pBuffMatModel,
		NULL,
		&g_ModelInfo[19].nNumMatModel,
		&g_ModelInfo[19].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/miti.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[20].pBuffMatModel,
		NULL,
		&g_ModelInfo[20].nNumMatModel,
		&g_ModelInfo[20].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/kadan.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[21].pBuffMatModel,
		NULL,
		&g_ModelInfo[21].nNumMatModel,
		&g_ModelInfo[21].MeshModel);

	D3DXLoadMeshFromX("data/MODEL/tonneru.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ModelInfo[22].pBuffMatModel,
		NULL,
		&g_ModelInfo[22].nNumMatModel,
		&g_ModelInfo[22].MeshModel);

	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_Model[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Model[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Model[nCntModel].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����
	
		g_Model[nCntModel].bUse = false;
	}

	//���^�C�v�����J��Ԃ�
	for (nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
	{
		g_ModelInfo[nCntModel].VtxMinModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);		//�ŏ��l
		g_ModelInfo[nCntModel].VtxMaxModel= D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l

		//���_���̎擾
		nNumVtx = g_ModelInfo[nCntModel].MeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_ModelInfo[nCntModel].MeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_ModelInfo[nCntModel].MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ő�l���擾
			if (Vtx.x >g_ModelInfo[nCntModel].VtxMaxModel.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_ModelInfo[nCntModel].VtxMaxModel.x = Vtx.x;
			}

			if (Vtx.y > g_ModelInfo[nCntModel].VtxMaxModel.y)
			{
				g_ModelInfo[nCntModel].VtxMaxModel.y = Vtx.y;
			}

			if (Vtx.z > g_ModelInfo[nCntModel].VtxMaxModel.z)
			{
				g_ModelInfo[nCntModel].VtxMaxModel.z = Vtx.z;
			}

			//���_���W���r���ă��f���̍ŏ��l���擾

			if (Vtx.x <g_ModelInfo[nCntModel].VtxMinModel.x)
			{
				g_ModelInfo[nCntModel].VtxMinModel.x = Vtx.x;
			}

			if (Vtx.y < g_ModelInfo[nCntModel].VtxMinModel.y)
			{
				g_ModelInfo[nCntModel].VtxMinModel.y = Vtx.y;
			}

			if (Vtx.z <g_ModelInfo[nCntModel].VtxMinModel.z)
			{
				g_ModelInfo[nCntModel].VtxMinModel.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_ModelInfo[nCntModel].MeshModel->UnlockVertexBuffer();
	}

//	ModelSet();
	
	FILE*pFile = fopen("data/Simple.txt", "r");

	//�����O���t�@�C������ǂݍ���
	if (pFile != NULL)
	{
		float posX;
		float posY;
		float posZ;
		float rotX;
		float rotY;
		float rotZ;
		int type;
		char comment[1024];
		
		while (true)
		{
			int ret = fscanf(pFile, "%f %f %f %f %f %f %d %s", &posX, &posY, &posZ, &rotX, &rotY, &rotZ, &type, comment);
			if (ret == EOF)
			{
				break;
			}
			SetModel(D3DXVECTOR3(posX, posY, posZ), D3DXVECTOR3(rotX, rotY, rotZ), type);
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n\n");
	}
}

//============================================================
//�@�I������
//============================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
	{ //�e�N�X�`���̔j��
	//���b�V���̔j��
		if (g_ModelInfo[nCntModel].pBuffMatModel != NULL)
		{
			g_ModelInfo[nCntModel].pBuffMatModel->Release();
			g_ModelInfo[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//============================================================
// ���f���̃A�b�v�f�[�g����
//============================================================
void UpdateModel(void)
{

}

//============================================================
// ���f���̕`�揈��
//============================================================
void DrawModel(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p
	D3DMATERIAL9 matDef;		//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;			//�}�e���A���̕ۊ�

	//���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldModel);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCntModel].rot.x, g_Model[nCntModel].rot.y, g_Model[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Model[nCntModel].pos.x, g_Model[nCntModel].pos.y, g_Model[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

			ModelLinfo* modelInfo = &g_ModelInfo[g_Model[nCntModel].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)modelInfo->pBuffMatModel->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)modelInfo->nNumMatModel; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				modelInfo->MeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}
//============================================================
// ���f���̓����蔻��
//============================================================
bool CollisionModel(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)				//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for(int nCntModel=0;nCntModel<MAX_MODEL;nCntModel++)
	{ 
		if (g_Model[nCntModel].bUse == true)//�g�p���Ă���ꍇ
		{
			
			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z >g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPos->y - pSize->y <g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y &&
				pPos->y + pSize->y >g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y &&

				pPosOld->x >= g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x &&
				pPos->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPos->y - pSize->y < g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y &&
				pPos->y + pSize->y > g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y &&

				pPosOld->x <= g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x &&
				pPos->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x &&
				pPos->x + pSize->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x &&

				pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPosOld->y <= g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y &&
				pPos->y > g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				pPos->y = g_Model[nCntModel].pos.y - g_Model[nCntModel].size.y - pSize->y;
				pMove->y = 0.0f;
			}
		
			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Model[nCntModel].pos.x + g_Model[nCntModel].size.x &&
				pPos->x + pSize->x > g_Model[nCntModel].pos.x - g_Model[nCntModel].size.x &&

				pPos->z - pSize->z < g_Model[nCntModel].pos.z + g_Model[nCntModel].size.z &&
				pPos->z + pSize->z > g_Model[nCntModel].pos.z - g_Model[nCntModel].size.z &&

				pPosOld->y >= g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y &&
				pPos->y < g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				bIsLanding = true;
				pPos->y = g_Model[nCntModel].pos.y + g_Model[nCntModel].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}		
	}

	return bIsLanding;
}
//============================================================
// ���f���̐ݒ菈��
//============================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)	//type�ǉ�
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Model[nCntModel].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Model[nCntModel].pos = pos;
			g_Model[nCntModel].rot = rot;
			g_Model[nCntModel].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Model[nCntModel].nType = nType;

			g_Model[nCntModel].size.x = (g_ModelInfo[nType].VtxMaxModel.x - g_ModelInfo[nType].VtxMinModel.x) / 2.0f;
			g_Model[nCntModel].size.y = (g_ModelInfo[nType].VtxMaxModel.y - g_ModelInfo[nType].VtxMinModel.y) ;
			g_Model[nCntModel].size.z = (g_ModelInfo[nType].VtxMaxModel.z - g_ModelInfo[nType].VtxMinModel.z) / 2.0f;

			break;		//(for���𔲂���)
		}		
	}
}
//============================================================
// ���f���̔z�u
//============================================================
void ModelSet(void)
{
	
}

Model*GetModel(void)
{
	return &g_Model[0];
}


