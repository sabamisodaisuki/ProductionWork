//============================================================
//
// 3D�ǂ̏��� [wall.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "wall.h"
#include "main.h"

//============================================================
//�}�N����`
//============================================================
#define MAX_WALL		(256)	//�ǂ̍ő吔
#define WALL_SIZE_X		(60)	//�ǂ̃T�C�Y
#define WALL_SIZE_Y 	(60)	//�ǂ̃T�C�Y
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Wall g_aWall[MAX_WALL];							//�e

 //�ǂ̎擾
Wall*GetWall(void)
{
	return &g_aWall[0];
}
//============================================================
// �ǂ̏�����
//============================================================
void lnitWall(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntWall;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/9.png",			
		&g_pTextureWall);

	//�e�̏��̏�����
	for (nCntWall = 0; nCntWall< MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�e���_�̖@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̕`��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffWall->Unlock();

	
	ZZWall();
}


//============================================================
// �ǂ̏I������
//============================================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//============================================================
// �e�̍X�V����
//============================================================
void UpdateWall(void)
{

}

//============================================================
// �ǂ̐ݒ�
//============================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fcol)
{
	int nCntWall;
	VERTEX_3D*pVtx;
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{//�ǂ��g�p����ĂȂ��ꍇ
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].fWidth = fWidth;//��
			g_aWall[nCntWall].fHeight = fHeight;//����
			g_aWall[nCntWall].rot = rot;		//����
			

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth / 2.0f,	g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aWall[nCntWall].fWidth / 2.0f, g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aWall[nCntWall].fWidth / 2.0f, -g_aWall[nCntWall].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aWall[nCntWall].fWidth / 2.0f,	-g_aWall[nCntWall].fHeight / 2.0f, 0.0f);

			//���_�J���[�̏�����
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol);

			g_aWall[nCntWall].bUse = true;	//�g�p���Ă����Ԃɂ���

			break;		//(for���𔲂���)
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtxBuffWall->Unlock();
}

//============================================================
// �e�̕`�揈��
//============================================================
void DrawWall(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f.
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
	
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//============================================================
// �ǂ̂܂Ƃߏ���
//============================================================
void ZZWall(void)
{
	//�ǈʒu
	SetWall(D3DXVECTOR3(60.0f, 50.0f, 60.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (240.0f), (100.0f), (1.0f));

	//�ǈʒu
	SetWall(D3DXVECTOR3(60.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), (240.0f), (100.0f), (1.0f));

	//�ǈʒu
	SetWall(D3DXVECTOR3(-60.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.5f, 0.0f), (240.0f), (100.0f), (1.0f));

	//�ǈʒu
	SetWall(D3DXVECTOR3(180.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), (240.0f), (100.0f), (1.0f));


	//�ǈʒu
	SetWall(D3DXVECTOR3(60.0f, 50.0f, 60.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), (240.0f), (100.0f), (0.2f));//��

	//�ǈʒu
	SetWall(D3DXVECTOR3(60.0f, 50.0f, -180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (240.0f), (100.0f), (0.2f));//��

	 //�ǈʒu
	SetWall(D3DXVECTOR3(-60.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), (240.0f), (100.0f), (0.2f));//��

	//�ǈʒu
	SetWall(D3DXVECTOR3(180.0f, 50.0f, -60.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.5f, 0.0f), (240.0f), (100.0f), (0.2f));//�E
}