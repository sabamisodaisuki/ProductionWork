//====================
//�v���C���[�̏���
//AUTHOR:���X�ؗ��l
//
//===================

#include "main.h"
#include "Arrow.h"
#include"input.h"
#include"time.h"
#include"bullet.h"
#include"fade.h"
#include"sound.h"
#include"Enemy.h"
#include"HighScore.h"


#define Arrow_Z			(4.0f)

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;				//�e�N�X�`���ւ̃|�C���^			
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnimArrow;								//�A�j���[�V�����J�E���^�[
int g_nPatternAnimArrow;								//�A�j���[�V�����p�^�[��
int nDirectionMove;
D3DXVECTOR3 g_posArrow;								//�ʒu
D3DXVECTOR3 g_moveArrow;								//�ړ���
D3DXVECTOR3 g_scaleArrow;								//�v���C���[�̑傫��
D3DXVECTOR3 g_posOldArrow;								//�O��̈ʒu
Arrow g_Arrow;										//�v���C���[���


														//�v���C���[�̏���������
D3DXVECTOR3 g_rotArrow;								//����
float g_fLengthArrow;									//�Ίp���̒���
float g_fAngleArrow;									//�Ίp���̊p�x


														//�v���C���[�̎擾
Arrow*GetArrow(void)
{
	return &g_Arrow;
}

int sum(int a, int b)
{
	//	return a + b;
	int c = a + b;
	return c;
}


void lnitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int C;
	C = sum(4, 5);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/yazirusi.png",					//daiba.png sura2.png
		&g_pTextureArrow);

	g_nCounterAnimArrow = 0;							//�J�E���^�[������
	g_nPatternAnimArrow = 0;							//�p�^�[��No��������
	g_posArrow = D3DXVECTOR3(70.0f, 480.0f, 0.0f);		//�ʒu��������
	g_moveArrow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��l��������
	g_scaleArrow = D3DXVECTOR3(100.0f, 100.0f, 0.0f);	//�v���C���[�̏���������
	g_Arrow.bDisp = true;
	g_Arrow.nLife = 20;
	g_Arrow.nCounterState = 60;
	g_Arrow.state = ArrowSTATE_NORMAL;



	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	VERTEX_2D*pVtx;		//���_���փ|�C���^

						//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);



	//���_���W
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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�v���C���[���W
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.33f*g_Arrow.nPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.33f + (0.33f*g_Arrow.nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.33f*g_Arrow.nPatternAnim), 0.25f);
	pVtx[3].tex = D3DXVECTOR2(0.33f + (0.33f*g_Arrow.nPatternAnim), 0.25f);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffArrow->Unlock();

}
//�|���S���̏I������
void UninitArrow(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}

}

//�v���C���[�̍X�V����
void UpdateArrow(void)
{
	// �t�F�[�h���̎擾
	FADE fade = GetFade();

	VERTEX_2D*pVtx;



	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[��������[��]

		g_Arrow.nDirectionMove = 1;


		g_moveArrow.x -= 5.0f;//�v���C���[�̈ʒu�Ɉړ��ʂ𑫂�

	}

	if (GetKeyboardTrigger(DIK_W) == true)
	{//W�L�[��������[��n
		if (g_Arrow.bIsJumping == false)
		{
			g_Arrow.bIsJumping = true;

			g_moveArrow.y = -40.0f;//�v���C���[�̃W�����v

		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[��������[�E]
		g_Arrow.nDirectionMove = 2;
		g_moveArrow.x += 5.0f;//�v���C���[�̈ʒu�Ɉړ��ʂ𑫂�
	}
	
	if (g_moveArrow.x >= 1.0f || g_moveArrow.x <= -1.0f)
	{
		//�p�^�[���X�V
		g_Arrow.nCounterAnim++; //�J�E���^�[���Z

		if ((g_Arrow.nCounterAnim % 5) == 0)
		{

			g_Arrow.nPatternAnim++; //�J�E���^�[���Z

			if (g_Arrow.nPatternAnim >= 4)//���p�^�[���𒴂���
			{
				g_Arrow.nPatternAnim = 0;//�J�E���g��0�ɖ߂�
			}

			//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
			g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*g_Arrow.nDirectionMove);
			pVtx[1].tex = D3DXVECTOR2(0.33f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*g_Arrow.nDirectionMove);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*(g_Arrow.nDirectionMove + 1));
			pVtx[3].tex = D3DXVECTOR2(0.33f + (0.33f*(g_Arrow.nPatternAnim)), 0.25f*(g_Arrow.nDirectionMove + 1));
			//���_�o�b�t�@�A�����b�N
			g_pVtxBuffArrow->Unlock();
		}
		else
		{//��~��
			if (g_Arrow.nCounterAnim)
			{

			}



		}

	}
	//���_�o�b�t�@�����b�N���A���_���փ|�C���^�擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_posArrow.x - Arrow_SIZE_X / 2, g_posArrow.y - Arrow_SIZE_Y, g_posArrow.z);
	pVtx[1].pos = D3DXVECTOR3(g_posArrow.x + Arrow_SIZE_X / 2, g_posArrow.y - Arrow_SIZE_Y, g_posArrow.z);
	pVtx[2].pos = D3DXVECTOR3(g_posArrow.x - Arrow_SIZE_X / 2, g_posArrow.y, g_posArrow.z);
	pVtx[3].pos = D3DXVECTOR3(g_posArrow.x + Arrow_SIZE_X / 2, g_posArrow.y, g_posArrow.z);


	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffArrow->Unlock();
}



//�|���S���̕`�揈��
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureArrow);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

