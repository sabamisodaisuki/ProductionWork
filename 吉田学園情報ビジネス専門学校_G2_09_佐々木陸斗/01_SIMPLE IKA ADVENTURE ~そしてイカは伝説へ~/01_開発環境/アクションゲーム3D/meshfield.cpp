//============================================================
//
// 3D���b�V������ [Meshfield.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "Meshfield.h"
#include "main.h"
#include "input.h"
#define MESHFIELD_X_BLOCK	(55)		//x�����̃u���b�N
#define MESHFIELD_Z_BLOCK	(55)		//Z�����̃u���b�N	
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))
#define MESHFIELD_INDEX_NUM	((MESHFIELD_X_BLOCK+1)*2*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)
#define MESHFIELD_PRIMITVE_NUM	(MESHFIELD_X_BLOCK*MESHFIELD_Z_BLOCK*2+(MESHFIELD_Z_BLOCK-1)*4)
#define MESHFIELD_FWIDTH	(60.0f)		//��
#define MESHFIELD_FHEIGHT	(60.0f)		//���s
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		//���b�V���̃e�N�X�`��
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshfield = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;							// �ʒu
D3DXVECTOR3 g_rotMeshfield;							// ����
D3DXMATRIX g_mtxWorldMeshfield;						// ���[���h�}�g���b�N�X
MESHFIELD g_Meshfield;
//���b�V���̎擾
MESHFIELD*GetMeshfield(void)
{
	return &g_Meshfield;
}
//============================================================
// ���b�V���̏�����
//============================================================
void lnitMeshfield(void)
{
	int nCntZ;
	int nCntX;
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/1.png",
		&g_pTextureMeshfield);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK+1; nCntZ++)
	{
		for ( nCntX = 0; nCntX < MESHFIELD_X_BLOCK+1; nCntX++)
		{
			//���_���W
			pVtx[0].pos = D3DXVECTOR3((MESHFIELD_FWIDTH*nCntX- MESHFIELD_FHEIGHT), 0.0f, (-MESHFIELD_FHEIGHT* nCntZ+MESHFIELD_FWIDTH));

			pVtx[0].tex = D3DXVECTOR2((1.0f/MESHFIELD_X_BLOCK)*nCntX,(1.0f / MESHFIELD_Z_BLOCK)* nCntZ );

			//�e���_�̖@���̐ݒ�
		
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			//���_�J���[�̕`��
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f,1.0f);

			pVtx++;
		}
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffMeshfield->Unlock();
	//�C���f�b�N�X�o�b�t�@���|�C���^
	WORD*pldx;

	//�C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pldxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pldxBuffMeshfield->Lock(0, 0, (void**)&pldx, 0);

	for (nCntZ = 0; nCntZ < MESHFIELD_Z_BLOCK; nCntZ++)
	{
		for (nCntX = 0; nCntX <= MESHFIELD_X_BLOCK ; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�

			//X�񉺒i
			pldx[0] = (WORD)nCntX + (MESHFIELD_X_BLOCK + 1) * (nCntZ + 1);
			pldx[1] = (WORD)nCntX + (MESHFIELD_X_BLOCK + 1) * nCntZ;
			pldx += 2;

		}
		if (nCntZ<MESHFIELD_Z_BLOCK-1)
		{
			//X��̏�i
			pldx[0] = pldx[-1];
			pldx[1] = (WORD)((MESHFIELD_X_BLOCK+1)*(nCntZ+2));
			pldx+=2;
		}
	}
		//�C���f�b�N�X���A�����b�N
		g_pldxBuffMeshfield->Unlock();
	
}

//============================================================
// ���b�V���̏I������
//============================================================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@���J��
	if (g_pldxBuffMeshfield != NULL)
	{
		g_pldxBuffMeshfield->Release();
		g_pldxBuffMeshfield = NULL;
	}

}

//============================================================
// ���b�V���̍X�V����
//============================================================
void UpdateMeshfield(void)
{
	
}

//============================================================
// ���b�V���̕`�揈��
//============================================================
void DrawMeshfield(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pldxBuffMeshfield);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���b�V���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̊֌W
		0,												//�`�悷��ŏ��̒��_
		0,												//�C���f�b�N�X�̍ŏ��l
		MESHFIELD_VERTEX_NUM,							//���_��
		0,												//�C���f�b�N�X�̍ŏ��̐�
		MESHFIELD_PRIMITVE_NUM);						//�v���~�e�B�u��
}