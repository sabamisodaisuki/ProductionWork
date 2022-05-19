//============================================================
//
// 3D�|���S������ [polygon.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "polygon.h"
#include "main.h"
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPolygon;							// �ʒu
D3DXVECTOR3 g_rotPolygon;							// ����
D3DXMATRIX g_mtxWorldPolygon;						// ���[���h�}�g���b�N�X
//============================================================
// �|���S���̏�����
//============================================================
void lnitPolygon(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -50.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̕`��
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffPolygon->Unlock();
}


//============================================================
// �|���S���̏I������
//============================================================
void UninitPolygon(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//============================================================
// �|���S���̍X�V����
//============================================================
void UpdatePolygon(void)
{

}

//============================================================
// �|���S���̕`�揈��
//============================================================
void DrawPolygon(void)
{
	////�f�o�C�X���擾
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//							//���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldPolygon);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	//D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	////�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	//D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	////���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	////���_�t�H�[�}�b�g�ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}