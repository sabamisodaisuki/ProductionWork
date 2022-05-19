//============================================================
//
// 3D����@UI[UI.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"Ui.h"
#include"Score.h"
#include"sound.h"
#include"fade.h"
#include"HighScore.h"

//============================================================
//�}�N����`
//============================================================
#define MAX_Ui				(128)			//UI�̍ő吔
#define Ui_SIZE_X			(100.0f)		//UI�T�C�Y
#define Ui_SIZE_Y			(100.0f)		//UI�T�C�Y

//============================================================
//�O���[�o���ϐ�
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureUi = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtexBuffUi = NULL;
Ui g_aUi[MAX_Ui];
int g_CounterUi;
// �t�F�[�h���̎擾
FADE fade = GetFade();


//============================================================
//UI�̏���������
//============================================================
void lnitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ScoreUI.png",
		&g_pTextureUi);

	//UI�̏��̏�����
	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		g_aUi[nCntUi].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].bUse = false;
	}

	g_CounterUi = 0;

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Ui,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtexBuffUi,
		NULL);


	VERTEX_2D*pVtx;		//���_���փ|�C���^

	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtexBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̕`��
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�A�����b�N
	g_pVtexBuffUi->Unlock();

	//UI�ʒu
	SetUi(D3DXVECTOR3(970.0f, 35.0f, 0.0f), (300.0f), (300.0f));
}
//============================================================
//UI�̏I������
//============================================================
void UninitUi(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureUi != NULL)
	{
		g_pTextureUi->Release();
		g_pTextureUi = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtexBuffUi != NULL)
	{
		g_pVtexBuffUi->Release();
		g_pVtexBuffUi = NULL;
	}
}
//============================================================
//UI�̍X�V����
//============================================================
void UpdateUi(void)
{

}
//============================================================
//UI�̕`�揈��
//============================================================
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntUi;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtexBuffUi, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureUi);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUi * 4, 2);
		}
	}
}
//============================================================
//UI�̐ݒ菈��
//============================================================
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntUi;
	VERTEX_2D*pVtx;
	g_pVtexBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == false)
		{//UI���g�p����ĂȂ��ꍇ
			g_aUi[nCntUi].pos = pos;
			g_aUi[nCntUi].fWidth = fWidth;	//��
			g_aUi[nCntUi].fHeight = fHeight;//����

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);

			g_aUi[nCntUi].bUse = true;	//�g�p���Ă����Ԃɂ���

			break;		//(for���𔲂���)
		}
		pVtx += 4;//�|�C���^���S���i�߂�
	}
	g_pVtexBuffUi->Unlock();
}
//============================================================
//�O���[�o���ϐ�
//============================================================
void DeleteUi(int nCntUi)
{

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_SE_bakuha);

	g_CounterUi++;
	//�g�p���Ă��Ȃ���Ԃ�
	g_aUi[nCntUi].bUse = false;

	for (nCntUi = 0; nCntUi < MAX_Ui; nCntUi++)
	{
		if (g_CounterUi == 4)//�A�C�e�������ׂĎ�胊�U���g��ʂ�
		{
			SaveHigeScore();
			SetFade(MODE_WIN);
			return;
		}
	}

}
//�A�C�e���̎擾
Ui*GetUi(void)
{
	return &g_aUi[0];
}
