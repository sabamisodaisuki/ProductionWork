//============================================================
//
//  �r���{�[�h[billborad.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "billborad.h"
#include "main.h"

//============================================================
//�}�N����`
//============================================================
#define MAX_Billborad		(256)		//�r���{�[�h�̍ő吔
#define Billborad_SIZE_X	(60)	//�r���{�[�h�̃T�C�Y
#define Billborad_SIZE_Y 	(60)		//�r���{�[�h�̃T�C�Y
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureBillborad = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillborad = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Billborad g_aEffect[MAX_Billborad];						//�G�t�F�N�g��

//============================================================
// �r���{�[�h�̏�����
//============================================================
void lnitBillborad(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBillborad;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETUMEI.jpg",
		&g_pTextureBillborad);

	//�r���{�[�h�̏��̏�����
	for (nCntBillborad = 0; nCntBillborad< MAX_Billborad; nCntBillborad++)
	{
		g_aEffect[nCntBillborad].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntBillborad].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntBillborad].bUse = false;
	}
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Billborad,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillborad,
		NULL);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
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
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̕`��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffBillborad->Unlock();

	//�r���{�[�h�ʒu
	SetBillborad(D3DXVECTOR3(30.0f, 400.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (100.0f), (100.0f));
}

//============================================================
// �r���{�[�h�̏I������
//============================================================
void UninitBillborad(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBillborad != NULL)
	{
		g_pTextureBillborad->Release();
		g_pTextureBillborad = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillborad != NULL)
	{
		g_pVtxBuffBillborad->Release();
		g_pVtxBuffBillborad = NULL;
	}
}

//============================================================
// �r���{�[�h�̍X�V����
//============================================================
void UpdateBillborad(void)
{
	//�g�p����
}

//============================================================
// �r���{�[�h�̐ݒ�
//============================================================
void SetBillborad(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	int nCntBillborad;

	VERTEX_3D*pVtx;

	g_pVtxBuffBillborad->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
	{
		if (g_aEffect[nCntBillborad].bUse == false)
		{//�r���{�[�h���g�p����ĂȂ��ꍇ
			g_aEffect[nCntBillborad].pos = pos;				//�ʒu
			g_aEffect[nCntBillborad].fWidth = fWidth;		//��
			g_aEffect[nCntBillborad].fHeight = fHeight;		//����
			g_aEffect[nCntBillborad].rot = rot;				//����

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntBillborad].fWidth / 2.0f, g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntBillborad].fWidth / 2.0f, g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntBillborad].fWidth / 2.0f, -g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntBillborad].fWidth / 2.0f, -g_aEffect[nCntBillborad].fHeight / 2.0f, 0.0f);

			g_aEffect[nCntBillborad].bUse = true;	//�g�p���Ă����Ԃɂ���

			break;		//(for���𔲂���)
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtxBuffBillborad->Unlock();
}

//============================================================
// �r���{�[�h�̕`�揈��
//============================================================
void DrawBillborad(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);//�r���[�}�g���b�N�X�̎擾

	for (int nCntBillborad = 0; nCntBillborad < MAX_Billborad; nCntBillborad++)
	{
		if (g_aEffect[nCntBillborad].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntBillborad].mtxWorld);
			pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//�J�����t���ݒ�
			g_aEffect[nCntBillborad].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntBillborad].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntBillborad].mtxWorld._13 = mtxView._31;
			/*g_aEffect[nCntBillborad].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntBillborad].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntBillborad].mtxWorld._23 = mtxView._32;*/
			g_aEffect[nCntBillborad].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntBillborad].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntBillborad].mtxWorld._33 = mtxView._33;

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntBillborad].rot.y, g_aEffect[nCntBillborad].rot.x, g_aEffect[nCntBillborad].rot.z);
			D3DXMatrixMultiply(&g_aEffect[nCntBillborad].mtxWorld, &g_aEffect[nCntBillborad].mtxWorld, &mtxRot);

			//�ʒu�𔽉f.
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntBillborad].pos.x, g_aEffect[nCntBillborad].pos.y, g_aEffect[nCntBillborad].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntBillborad].mtxWorld, &g_aEffect[nCntBillborad].mtxWorld, &mtxTrans);

			//���C�g�̖���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntBillborad].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillborad, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillborad);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillborad * 4, 2);

			//���ɖ߂�
			pDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//���C�g�̗L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}