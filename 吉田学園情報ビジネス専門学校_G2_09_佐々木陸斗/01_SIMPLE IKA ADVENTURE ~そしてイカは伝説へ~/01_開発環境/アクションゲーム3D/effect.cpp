//============================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "effect.h"
#include "main.h"
#include "MODEL.h"
#include"billborad.h"

//============================================================
//�}�N����`
//============================================================
#define EFFECT_SIZE_X		(60)	//�G�t�F�N�g�̃T�C�YX
#define EFFECT_SIZE_Y 		(60)	//�G�t�F�N�g�̃T�C�YY
//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];							//�G�t�F�N�g

//============================================================
// �G�t�F�N�g�̏�����
//============================================================
void lnitEffect(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntPlayer;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/0.jpg",
		&g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCntPlayer = 0; nCntPlayer<MAX_EFFECT; nCntPlayer++)
	{
		g_aEffect[nCntPlayer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntPlayer].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntPlayer].nLife = 0;
		g_aEffect[nCntPlayer].bUse = false;
	}
	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_���փ|�C���^
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer <MAX_EFFECT; nCntPlayer++)
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
	g_pVtxBuffEffect->Unlock();

}

//============================================================
// �G�t�F�N�g�̏I������
//============================================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//============================================================
// �G�t�F�N�g�̍X�V����
//============================================================
void UpdateEffect(void)
{
	int nCntPlayer;

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer < MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == true)
		{
			//�����̃J�E���g�_�E��
			g_aEffect[nCntPlayer].nLife--;

			//a�l��������
			g_aEffect[nCntPlayer].col.a -= 0.04f;

			//���C�t��0�̎�
			if (g_aEffect[nCntPlayer].nLife <= 0)
			{
				g_aEffect[nCntPlayer].bUse = false;
			}

		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//============================================================
// �G�t�F�N�g�̕`�揈��
//============================================================
void DrawEffect(void)
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;

	////���Z����
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//z�v���f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int nCntPlayer = 0; nCntPlayer < MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntPlayer].mtxWorld);

			//���C�g�̖���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//�r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����t���ݒ�
			g_aEffect[nCntPlayer].mtxWorld._11 = mtxView._11;
			g_aEffect[nCntPlayer].mtxWorld._12 = mtxView._21;
			g_aEffect[nCntPlayer].mtxWorld._13 = mtxView._31;
			g_aEffect[nCntPlayer].mtxWorld._21 = mtxView._12;
			g_aEffect[nCntPlayer].mtxWorld._22 = mtxView._22;
			g_aEffect[nCntPlayer].mtxWorld._23 = mtxView._32;
			g_aEffect[nCntPlayer].mtxWorld._31 = mtxView._13;
			g_aEffect[nCntPlayer].mtxWorld._32 = mtxView._23;
			g_aEffect[nCntPlayer].mtxWorld._33 = mtxView._33;

			
			//�ʒu�𔽉f.
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntPlayer].pos.x, g_aEffect[nCntPlayer].pos.y, g_aEffect[nCntPlayer].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntPlayer].mtxWorld, &g_aEffect[nCntPlayer].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntPlayer].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPlayer * 4, 2);

			//�e�N�X�`���̖���
			pDevice->SetTexture(0, NULL);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		}
	}
	//a�v���f�B���O�����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//z�v���f�B���O�����ɖ߂��ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
//============================================================
// �G�t�F�N�g�̐ݒ�
//============================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int life)
{
	int nCntPlayer;
	VERTEX_3D*pVtx;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPlayer = 0; nCntPlayer <MAX_EFFECT; nCntPlayer++)
	{
		if (g_aEffect[nCntPlayer].bUse == false)
		{//�G�t�F�N�g���g�p����ĂȂ��ꍇ
			g_aEffect[nCntPlayer].pos = pos;			//�ʒu
			g_aEffect[nCntPlayer].size = size;			//��
			g_aEffect[nCntPlayer].col = col;			//�J���[
			g_aEffect[nCntPlayer].rot = rot;			//����
			g_aEffect[nCntPlayer].nLife = life;			//���C�t
			g_aEffect[nCntPlayer].bUse = true;			//�g�p���Ă����Ԃɂ���

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, size.z);

			//���_�J���[�̏�����
			pVtx[0].col = g_aEffect[nCntPlayer].col;
			pVtx[1].col = g_aEffect[nCntPlayer].col;
			pVtx[2].col = g_aEffect[nCntPlayer].col;
			pVtx[3].col = g_aEffect[nCntPlayer].col;

			break;		//(for���𔲂���)
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtxBuffEffect->Unlock();
}

//============================================================
// �G�t�F�N�g�̂܂Ƃߏ���
//============================================================
void ZZEffect(void)
{
	
}