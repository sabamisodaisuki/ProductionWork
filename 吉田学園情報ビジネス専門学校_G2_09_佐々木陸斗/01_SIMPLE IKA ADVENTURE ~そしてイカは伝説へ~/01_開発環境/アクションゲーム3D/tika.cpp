//============================================================
//
// 3D����@�n�����f������[Tika.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "tika.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include <stdio.h>

//============================================================
//�}�N����`
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);	//�����W��
#define MAX_TIKA	(128)					//���f���̍ő吔
#define NUM_TIKA	(2)						//���f����
//============================================================
//�O���[�o���ϐ�
//============================================================
typedef struct
{
	LPD3DXMESH			 MeshTika;
	LPD3DXBUFFER		 pBuffMatTika;
	DWORD				nNumMatTika;
	D3DXVECTOR3			VtxMinTika;		//�ŏ��l
	D3DXVECTOR3			VtxMaxTika;		//�ő�l

}TikaLinfo;

////��Tikainfo�\���̂̔z���錾����
D3DXMATRIX g_mtxWorldTika;
Tika g_Tika[MAX_TIKA];
TikaLinfo g_TikaInfo[NUM_TIKA];

//============================================================
//�@�n�����f���̏���������
//============================================================
void lnitTika(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTika;

	memset(&g_TikaInfo, 0, sizeof(g_TikaInfo));
	memset(&g_Tika, 0, sizeof(g_Tika));

	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/tikakabe.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_TikaInfo[0].pBuffMatTika,
		NULL,
		&g_TikaInfo[0].nNumMatTika,
		&g_TikaInfo[0].MeshTika);
	//X�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/tikayuka.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_TikaInfo[1].pBuffMatTika,
		NULL,
		&g_TikaInfo[1].nNumMatTika,
		&g_TikaInfo[1].MeshTika);

	int nNumVtx;									//���_��
	DWORD sizeFVF;									//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE*pVtxBuff;									//���_�o�b�t�@�̃|�C���^

	for (nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		g_Tika[nCntTika].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_Tika[nCntTika].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
		g_Tika[nCntTika].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړI�p�x�̏�����

		g_Tika[nCntTika].bUse = false;
	}

	//���^�C�v�����J��Ԃ�
	for (nCntTika = 0; nCntTika < NUM_TIKA; nCntTika++)
	{
		g_TikaInfo[nCntTika].VtxMinTika = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//�ŏ��l
		g_TikaInfo[nCntTika].VtxMaxTika = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//�ő�l

																						//���_���̎擾
		nNumVtx = g_TikaInfo[nCntTika].MeshTika->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_TikaInfo[nCntTika].MeshTika->GetFVF());

		//���_�o�b�t�@�����b�N
		g_TikaInfo[nCntTika].MeshTika->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//���_���W���r���ă��f���̍ő�l���擾
			if (Vtx.x >g_TikaInfo[nCntTika].VtxMaxTika.x)
			{
				//���O���[�o���ϐ���min,max�ɂ�����
				g_TikaInfo[nCntTika].VtxMaxTika.x = Vtx.x;
			}

			if (Vtx.y > g_TikaInfo[nCntTika].VtxMaxTika.y)
			{
				g_TikaInfo[nCntTika].VtxMaxTika.y = Vtx.y;
			}

			if (Vtx.z > g_TikaInfo[nCntTika].VtxMaxTika.z)
			{
				g_TikaInfo[nCntTika].VtxMaxTika.z = Vtx.z;
			}

			//���_���W���r���ă��f���̍ŏ��l���擾

			if (Vtx.x <g_TikaInfo[nCntTika].VtxMinTika.x)
			{
				g_TikaInfo[nCntTika].VtxMinTika.x = Vtx.x;
			}

			if (Vtx.y < g_TikaInfo[nCntTika].VtxMinTika.y)
			{
				g_TikaInfo[nCntTika].VtxMinTika.y = Vtx.y;
			}

			if (Vtx.z <g_TikaInfo[nCntTika].VtxMinTika.z)
			{
				g_TikaInfo[nCntTika].VtxMinTika.z = Vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�ccc
			pVtxBuff += sizeFVF;
		}

		//���_�o�b�t�@�̃A�����b�N
		g_TikaInfo[nCntTika].MeshTika->UnlockVertexBuffer();
	}

	//	TikaSet();

	FILE*pFile = fopen("data/tika.txt", "r");

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
			SetTika(D3DXVECTOR3(posX, posY, posZ), D3DXVECTOR3(rotX, rotY, rotZ), type);
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
void UninitTika(void)
{
	for (int nCntTika = 0; nCntTika < NUM_TIKA; nCntTika++)
	{ //�e�N�X�`���̔j��
	  //���b�V���̔j��
		if (g_TikaInfo[nCntTika].pBuffMatTika != NULL)
		{
			g_TikaInfo[nCntTika].pBuffMatTika->Release();
			g_TikaInfo[nCntTika].pBuffMatTika = NULL;
		}
	}
}

//============================================================
// �n�����f���̃A�b�v�f�[�g����
//============================================================
void UpdateTika(void)
{

}

//============================================================
// �n�����f���̕`�揈��
//============================================================
void DrawTika(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//�}�e���A���̕ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���̕ۊ�

	 //���݂̃}�e���A��
	pDevice->GetMaterial(&matDef);

	for (int nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldTika);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Tika[nCntTika].rot.x, g_Tika[nCntTika].rot.y, g_Tika[nCntTika].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldTika, &g_mtxWorldTika, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Tika[nCntTika].pos.x, g_Tika[nCntTika].pos.y, g_Tika[nCntTika].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldTika, &g_mtxWorldTika, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTika);

			TikaLinfo* TikaInfo = &g_TikaInfo[g_Tika[nCntTika].nType];

			//�}�e���A���f�[�^�ւ̃|�C���g�擾
			pMat = (D3DXMATERIAL*)TikaInfo->pBuffMatTika->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)TikaInfo->nNumMatTika; nCntMat++)
			{
				//�}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				TikaInfo->MeshTika->DrawSubset(nCntMat);
			}
		}
	}

	//�ۑ������}�e���A��
	pDevice->SetMaterial(&matDef);
}
//============================================================
// �n�����f���̓����蔻��
//============================================================
bool CollisionTika(
	D3DXVECTOR3* pPos,				//���݂̈ʒu
	D3DXVECTOR3* pPosOld,			//�O��̍���
	D3DXVECTOR3* pMove,				//�ړ���
	D3DXVECTOR3* pSize)				//�T�C�Y
{
	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (int nCntTika = 0; nCntTika<MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == true)//�g�p���Ă���ꍇ
		{

			//�E�̓����蔻��
			if (pPos->z - pSize->z <g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z >g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPos->y - pSize->y <g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y &&
				pPos->y + pSize->y >g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y &&

				pPosOld->x >= g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x &&
				pPos->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//���̓����蔻��
			if (pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPos->y - pSize->y < g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y &&
				pPos->y + pSize->y > g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y &&

				pPosOld->x <= g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x &&
				pPos->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x)

				//�u���b�N�ɂ߂荞��
			{
				pPos->x = g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//���ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x &&
				pPos->x + pSize->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x &&

				pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPosOld->y <= g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y &&
				pPos->y > g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				pPos->y = g_Tika[nCntTika].pos.y - g_Tika[nCntTika].size.y - pSize->y;
				pMove->y = 0.0f;
			}

			//��ʂ̓����蔻��
			if (pPos->x - pSize->x < g_Tika[nCntTika].pos.x + g_Tika[nCntTika].size.x &&
				pPos->x + pSize->x > g_Tika[nCntTika].pos.x - g_Tika[nCntTika].size.x &&

				pPos->z - pSize->z < g_Tika[nCntTika].pos.z + g_Tika[nCntTika].size.z &&
				pPos->z + pSize->z > g_Tika[nCntTika].pos.z - g_Tika[nCntTika].size.z &&

				pPosOld->y >= g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y &&
				pPos->y < g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y)
				//�u���b�N�ɂ߂荞��
			{
				bIsLanding = true;
				pPos->y = g_Tika[nCntTika].pos.y + g_Tika[nCntTika].size.y + pSize->y;
				pMove->y = 0.0f;
			}
		}
	}

	return bIsLanding;
}
//============================================================
// �n�����f���̐ݒ菈��
//============================================================
void SetTika(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	for (int nCntTika = 0; nCntTika < MAX_TIKA; nCntTika++)
	{
		if (g_Tika[nCntTika].bUse == false)
		{//�u���b�N���g�p����ĂȂ��ꍇ
			g_Tika[nCntTika].pos = pos;
			g_Tika[nCntTika].rot = rot;
			g_Tika[nCntTika].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_Tika[nCntTika].nType = nType;

			g_Tika[nCntTika].size.x = (g_TikaInfo[nType].VtxMaxTika.x - g_TikaInfo[nType].VtxMinTika.x) / 2.0f;
			g_Tika[nCntTika].size.y = (g_TikaInfo[nType].VtxMaxTika.y - g_TikaInfo[nType].VtxMinTika.y);
			g_Tika[nCntTika].size.z = (g_TikaInfo[nType].VtxMaxTika.z - g_TikaInfo[nType].VtxMinTika.z) / 2.0f;

			break;		//(for���𔲂���)
		}
	}
}
//============================================================
// ���f���̔z�u
//============================================================
void TikaSet(void)
{

}
Tika*GetTika(void)
{
	return &g_Tika[0];
}

